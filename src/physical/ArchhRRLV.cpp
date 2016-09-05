/*
 * ArchhRRLV.cpp
 *
 *  Created on: 12/10/2015
 *      Author: ezequiel
 */

#include "./headers/ArchRRLV.h"

#include <iostream>
#include <cstring>
using namespace std;
#define POSBYTMAP 0

typedef unsigned short int TSize; //tipo para el prefijo de la longitud del registro
typedef short int TEndBlock;	  //tipo para la marca de fin de bloque
const short int ENDBLOCK = -1;

/*
 * corre desde el inicio del buffer hacia la izquierda tantos bytes indicados por length
 */
void ArchRRLV::lshift(char*buffer,unsigned length,unsigned cant){
	char buffAux [length];memset(buffAux,0,length);
	cout<<"length "<<length<<endl;cout<<"cant "<<cant<<endl;
	memcpy(buffAux,buffer+cant,length-cant);
	memcpy(buffer,buffAux,length-cant);
	memset(buffer+length-cant,0,cant);
}

/*
 * Edit: devuelve -1 en caso de falla. Devuelve el numero de bloque donde quedo
 * el elemento editado.
 */
int ArchRRLV::edit(Registro& reg){
	unsigned i = 0;
	bool edito = false;
	int blockDest;
	do { i++;
		if ((blockDest = edit(reg,i))!=-1) edito = true;

	}while(!edito and i< byteMap->getTamanio());
	if (edito) return blockDest;
	else return -1;
}
/*Edit: devuelve -1 en caso de falla. Devuelve el numero de bloque donde quedo
 * el elemento editado.
 * Recibe como parámetro un registro el cual va a sobrescribir al registro a otro
 * que tenga la misma clave
 * Si el la longitud del registro actual es mayor  se intenta colocar al final del bloque si hay
 * espacio o sino al final del archivo.
 * Resulta menor se deja en el mismo lugar para se hace un corrimiento para evitar espacio en blanco
 * entre registros
 */
int ArchRRLV::edit(Registro & reg,unsigned numBlock){
	save();
	Registro * regHid = & reg.clone();
	*regHid = reg;
	int offset = 0;
	int blockDest = numBlock;
	if((offset = search(*regHid,numBlock))!= -1){
		char buffer[tmnBlock];memset(buffer,0,tmnBlock);
		char block[tmnBlock];memset(block,0,tmnBlock);
		archBlocks->leerBloque(block,numBlock);
		TSize espAnt = parser.serializar(*regHid,buffer)+sizeof(TSize);//Espacio del registro en el archivo
		TSize espAct = parser.serializar(reg,buffer)+sizeof(TSize);//Espacio del registro nuevo
		if (espAct <=espAnt){//Si hay espacio en la posicion actual //Falta actualiza byteMap
			int endBlock = this->getPosWriteBlock(block,tmnBlock)+sizeof(TEndBlock);
			unsigned cantShift = espAnt-espAct;
			unsigned prefijo = espAct -sizeof(TSize);
			memcpy(block+offset,&prefijo,sizeof(TSize));//copio el prefijo
			memcpy(block+offset+sizeof(TSize),buffer,espAct);//copio el registro
			lshift(block+offset+espAct,endBlock-offset-espAct,cantShift);//muevo el espaciosobrante
			byteMap->upDateGap(numBlock,espAct-espAnt);
		}
		else if ((espAct-espAnt) <= byteMap->getCantBytes(numBlock)){//Si tiene espacio en este bloque
			int endBlock = getPosWriteBlock(block,tmnBlock)+sizeof(TEndBlock);
			lshift(block+offset,endBlock-offset,espAnt);
			int posWrite = this->getPosWriteBlock(block,tmnBlock);
			cout<<"posWrite "<<posWrite<<endl;
			unsigned prefijo = espAct -sizeof(TSize);
			memcpy(block+posWrite,&prefijo,sizeof(TSize));
			memcpy(block+posWrite+sizeof(TSize),buffer,espAct);
			this->addEndBlock(block,posWrite+espAct);
			byteMap->upDateGap(numBlock,espAct-espAnt);
		}
		else if((espAct-espAnt) > byteMap->getCantBytes(numBlock)) {//ya no hay espacio en el bloque
			int endBlock = getPosWriteBlock(block,tmnBlock)+sizeof(TEndBlock);
			lshift(block+offset,endBlock-offset,espAnt);
			blockDest = insert(reg);
			byteMap->upDateGap(numBlock,-espAnt);

		}
		archBlocks->grabarBloque(block,numBlock);
		save();
		saveByteMap();
		delete regHid;
		return blockDest;
	}
	else
	{
		delete regHid;
		return -1;
	}
}

/*
 * Elimina un registro y devuelve el numero de bloque en donde resulto
 * la operación
 */
int ArchRRLV::del(Registro &reg){
	bool found = false;
	unsigned i = 0;
	do{	i++;
		found = del(reg,i);
	}while((!found and i < byteMap->getTamanio()));
	if (found) return i;
	else return -1;
}
/*Delete:elimina un registro segun un registro patrón que tiene
 * cargado la clave de identificación devuelve verdadero
 * si la baja fue exitosa
 * reg1 se uriliza para almacenar el valor del registro encontrado
 * reg2 es un registro que contiene la clave cargada del registro a eliminar
 */
bool ArchRRLV::del(Registro & reg,unsigned numBlock){
	save();
	int offset=0;

	if((offset = search(reg,numBlock))!= -1){
		unsigned length;
		int posEnd;
		char buffAux1[tmnBlock];//Lo uso para bufferizar un registro;
		char buffAux2[tmnBlock];//Lo uso para determinar la long del reg mediante el parser
		memset(buffAux1,0,tmnBlock);
		memset(buffAux2,0,tmnBlock);
		archBlocks->leerBloque(buffAux1,numBlock);

		length = parser.serializar(reg,buffAux2);
		length += sizeof(TSize);//le sumo lo que vale el prefijo
		cout<<"length"<<length<<endl;
		char * posWrite = buffAux1+offset;
		char * posRead = buffAux1+offset+length;
		posEnd = getPosWriteBlock(buffAux1,tmnBlock)+sizeof(TEndBlock);
		char * posFree = buffAux1 + (posEnd-length);
		unsigned tmnMove = posEnd +sizeof(TEndBlock)- (offset + length);
		char bufferCopia[tmnMove]; memcpy(bufferCopia,posRead,tmnMove);
		memcpy(posWrite,bufferCopia,tmnMove);
		//memcpy(posWrite,posRead,tmnMove); //Muevo los registros para ocupar el espacio
		memset(posFree,0,length);//pongo en 0 el final sobrante del bloque
		byteMap->upDateGap(numBlock,-length);
		this->saveByteMap();
		archBlocks->grabarBloque(buffAux1,numBlock);
		cout<<"pos end block"<<posEnd<<endl;
		cout<<"posWrite "<<offset<<endl;
		cout<<"posRead "<< offset + length<<endl;
		cout<<"pos free "<<posEnd-length<<endl;
		cout<<"tmn move"<<posEnd-(offset+length);
		return true;
	}
	else return false;
}
/*Search:guarda en regD el registro encontrado
 * 		 comparando con la clave de regB
 * 		 busca en el archivo completo
 * 		 devuelve false en el caso de que no se encuentre
 * 		 	      true en el caso de que se encuentre
*/
bool ArchRRLV::search(Registro & reg){
	save();
	bool found = false;
	int pos = 0;
	unsigned int i  = 1;
	while (!found and (i <= byteMap->getTamanio())){
		pos = search(reg,i);
		found = (pos!=-1);
		i++;
	}
	return found;
}

/*Search: guarda en regHid el resgistro encontrado
 * 		  comparando con la clave de regB
 *        toda la busqueda se hace en el bloque indicado por numBlock
 *        devuelve -1 si no se encuentra
 *        		   y si se encuentra devuelve el offset del registro
 */
int ArchRRLV::search(Registro & reg, unsigned numBlock){
	save();
	TSize size;
	Registro *regHid = &reg.clone();
	char block[tmnBlock];
	unsigned offset = 0;
	bool found = false;
	TEndBlock marca;
	memset(block,0,tmnBlock);
	archBlocks->leerBloque(block,numBlock);
	do{
		memcpy(&size,block+offset,sizeof(size));
		this->read(*regHid,numBlock,offset);
		if (reg.keycmp(*regHid)==0) found = true;
		if (!found) offset +=  sizeof(size)+size;//si no lo encuentra
		                                       //me mueve el tamaño en bytes de size y el tamaño del registro
		memcpy(&marca,block+offset,sizeof(marca));//por las dudas leo si llegue al final del bloque
	}while(!found and marca != ENDBLOCK);
	if  (!found) {
		delete regHid;
		return -1;
	}
	else {
		reg = *regHid;
		delete regHid;
		return offset;
	}
}
/*Se presupone que si el archivo no contiene ningun bloque está
 *Vacio es decir que fue recien creado
 */
bool ArchRRLV::archivoVacio(){
	return (archBlocks->getCantidadBloques()==0);
}

/*
 * Le doy formato de bloque al byte map y lo guardo como un bloque más
 *
 */
void ArchRRLV::saveByteMap(){
	char * block = new char[tmnBlock];
	memset(block,0,tmnBlock);
	byteMap->serializar(block,tmnBlock);
	archBlocks->grabarBloque(block,POSBYTMAP);
	delete [] block;
}

/*
 * Libero el actual bitmap y cargo el bytmap desde el archivo
 */
void ArchRRLV::openByteMap(){
	char * block = new char[tmnBlock];
	memset(block,0,tmnBlock);
	archBlocks->leerBloque(block,POSBYTMAP);
	if (byteMap!= NULL) delete byteMap;
	byteMap = new ByteMap();
	byteMap->hidratar(block);
	delete [] block;
}

//Funcion que devuelve si existe un bloque libre
bool blockFree(int result){
	#define BLOCKINEX -1
	return(result!= BLOCKINEX);
}

/*
 * Inserta el registro teniendo en cuenta la unicidad, si el registro ya existe devuelve -1
 */
int ArchRRLV::insertU(const Registro & registro){
	int blockDest=0;
	bool found = false;
	Registro * regHid = &registro.clone();
	found = search(*regHid);
	if (!found){
		blockDest = insert(registro);
		delete regHid;
		return blockDest;
	}else {
		delete regHid;
		return -1;
	}
}
int ArchRRLV::insert(const Registro & registro){
#define tam tmnBlock
#define LONGSIZE 2 //los registros pueden ocupar un máximo de 2^16 bytes
	char buff[tam];
	char dest[tam];
	memset(dest,0,tam);
	unsigned offset = 0;
	TSize size;
	size = parser.serializar(registro,buff);
	memcpy(dest,&size,sizeof(size));
	offset = offset + sizeof(size);
	memcpy(dest+offset,buff,size);
	return this->insert(dest,size+sizeof(size));
}
/*
 * Inserta un bloque de datos en un buffer interno
 * Si se acabó el espació graba el buffer y crea uno nuevo
 * para seguir insertando
 */

void ArchRRLV::addEndBlock(){
	memcpy(buffer+buffOffset,&ENDBLOCK,sizeof(TEndBlock));
	buffOffset = buffOffset + 2;
}

void ArchRRLV::addEndBlock(char *buffer,unsigned offset){
	memcpy(buffer+offset,&ENDBLOCK,sizeof(TEndBlock));
}

//Ojo no tiene en cuenta que pasa si tiene un registro vacio que comience con la marca de fin
//creo que igualmente el caso no se podría dar fijarse.
/*
 * Devuelve la posicion de la marca de finde bloque
 */
int ArchRRLV::getPosWriteBlock(char * block,unsigned length){
	TSize size;
	TEndBlock endBlock;
	unsigned offset = 0;
	bool found = false;
	while((offset < length) and !found){
		memcpy(&size,block+offset,sizeof(size));//Leo el el prefijo de longitud
		offset+=sizeof(size)+size;//actualizo el offset teniendo en cuenta el tamaño del prefijo y del registro
		memcpy(&endBlock,block+offset,sizeof(endBlock));//por las dudas leo capas que tengo un fin de block
		if(endBlock==ENDBLOCK) found = true;
	}
	if (!found) return -1;
	else return offset;
}
void ArchRRLV::insertInMiddle(char * data,int blockDest,TSize size){
	char bufferAux [tmnBlock];
	memset(bufferAux,0,tmnBlock);
	archBlocks->leerBloque(bufferAux,blockDest);
	unsigned posWrite = getPosWriteBlock(bufferAux,tmnBlock);
	memcpy(bufferAux+posWrite,data,size);
	addEndBlock(bufferAux,posWrite+size);
	archBlocks->grabarBloque(bufferAux,blockDest);
	byteMap->upDateGap(blockDest,size);
	saveByteMap();
}
int ArchRRLV::insert(char* data,unsigned int size){
	#define FINBLOQUE 2
	int blockDest = byteMap->getGap(size);
	if(blockFree(blockDest)){// verifica que exista un bloque con huecos si existe hidrato el bloque y guardo
		insertInMiddle(data,blockDest,size);
		return blockDest;
	}
	else{
		if(((tmnBlock-buffOffset)-FINBLOQUE)<(size)){//calculo el desborde teniendo en cuenta el espacio que ocupa la marca
			save();
		}
	//copio los datos al buffer en caso de que no exista un bloque con huecos
	memcpy(buffer+buffOffset,data,size);
	buffOffset = buffOffset+size;
	return this->pBlock;
	}
}

//fuerza que se guarde el buffer a disco en el estado en el que está
void ArchRRLV::save(){
	if(buffOffset!=0){ //Guarda si el buffer no está vacio
		addEndBlock();
		byteMap->addGap(pBlock,tmnBlock);
		byteMap->upDateGap(pBlock,buffOffset);
		saveByteMap();
		archBlocks->grabarBloque(buffer,pBlock);
		memset(buffer,0,tmnBlock);
		buffOffset = 0;
		pBlock++;
	}
}

/*
 * read: lee un registro del ArchRRLV, la función conoce que todo registro
 * 		 tiene un prefijo de longitud por este motivo a la hora de leer el registro
 * 		 se mueve en el bloque tanto como la cantidad de bytes que ocupe el prefijo.
 * 		 Precondición: que haya un registro en el bloque con un prefijo que indique su tamaño.
 */
void ArchRRLV::read(Registro & registro,unsigned numBlock,unsigned offset){
	this->save();//guardo el buffer por las dudas que el registro que esté buscando aun no esté guardado
	char buff[tmnBlock];
    TSize size;
	memset(buff,0,tmnBlock);
	archBlocks->leerBloque(buff,numBlock);
	memcpy(&size,buff+offset,sizeof(size));
	offset = offset + sizeof(size);
	parser.hidratar(registro,buff+offset);
}
ArchRRLV::ArchRRLV(string fileName, int tmnBlock){
	this->tmnBlock = tmnBlock;
	buffer = new char[tmnBlock];
	memset(buffer,0,tmnBlock);
	this->archBlocks = new ArchBlocks(fileName,tmnBlock);
	byteMap = NULL;
	buffOffset=0;
	if(archivoVacio()){
		this->byteMap = new ByteMap;
		saveByteMap();
		pBlock = 1;
	}
	else{
		openByteMap();
		pBlock = byteMap->getTamanio()+1;
	}

}

ArchRRLV::~ArchRRLV() {
	this->save();
	delete this->archBlocks;
	delete this->byteMap;
	delete [] buffer;
}




