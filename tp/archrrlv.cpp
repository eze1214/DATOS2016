#include "archrrlv.h"
#include "registro.h"
#include <cstdio>
#include <cstdlib>

ArchRRLV::ArchRRLV(std::string filename, std::string formato){
	this->filename = filename;
	this->formato = formato;
	this->puntero = 0;
	if (existeArchivo(filename)){
		std::cout<<"El archivo ya existe será sobreescribido"<<std::endl;
	}
	crearArchivo(filename,"wb+");
}

//TODO revizar
/*Ahora esta todo encapsulado en la clase desriptores
 * Falta crear el comportamiento de cuando se agrega
 * un registro que busque en la lista de espacio libre cual es la 
 * mas conveniente.
 */
ArchRRLV::ArchRRLV(std::string filename){
	this->filename = filename;
	this->puntero = 0;
	
	FILE * archivo;
	archivo = fopen(filename.data(),"rb");
	formato.clear();
	char leido=0;
	do{
		fread(&leido,sizeof(char),1,archivo);
		formato+=leido;
	}while(leido!='\n');
	
	char * buffer = new char [descriptor.descriptorSize()];
		fread(buffer,descriptor.descriptorSize,1,archivo);
		descriptor.hidratar(buffer,descriptor.descriptorSize());
	delete [] buffer;
	
}
bool ArchRRLV::existeArchivo(string nombreArchivo){
	bool existencia;
	FILE *archivo;
	archivo = fopen(nombreArchivo.data(),"r+b");
	if (archivo != NULL) {
		existencia = true;
		fclose(archivo);
	}
	else existencia = false;
	return existencia;
}

void ArchRRLV::crearArchivo(std::string nombreArchivo,std::string configuracion){
	FILE * archivo;
	char fin = '\n';
	archivo = fopen(nombreArchivo.data(),configuracion.c_str());
	if (archivo != NULL) std::cout<<"archivo creado correctamente"<<std::endl;
	fwrite((char*)&formato.c_str(),formato.size(),1,archivo);
	fwrite(&fin,sizeof(char),1,archivo);
	
	std::string serializado;
	descriptor.serializar(serializado);
	
	fwrite(serializado.c_str(),serializado.size(),1,archivo);
	
	fclose (archivo);
}

void ArchRRLV::addRegistro(Registro & registro){
	std::string serializado;
	DescriptorRegistro descriptor(registro);
	descriptor.serializar(serializado);
	this->grabarRegistro(serializado);
}

void ArchRRLV::readDescriptor(){
	
	fseek(archivo,formato.size+1);
	
}

/*Mueve el cursor hasta el espacio libre
 * 
 */
void ArchRRLV::buscarEspacioLibre(FILE * archivo){
	readDescriptor();	
}

/*TODO hay que programar correctamente el comportamiento 
 *de la busqueda de nodos libres.
 * Chequear por todos lados los size ahora estan encapsulados
 * en los descriptores.
 * 
 * Falta en ambas clases en esta y en la de registros en bloque 
 * que se agregue un campo ID en esta se maneja mediante el 
 * offset y en la otra clave automática.
 */
void ArchRRLV::grabarRegistro(const std::string & registro){
	FILE *archivo;
	archivo = fopen (filename.data(),"r+b");
	buscarEspacioLibre(archivo);//TODO terminar capas conviene utilizar un fseek ftell
	fwrite(registro.c_str(),registro.size(),1,archivo);
}


/*Presupongo que bufferizo el descriptor de espacio libre
 */
Registro ArchRRLV::readRegistro(){
	//TODO Poner la logica para no leer el bloque de espacios libre
	FILE *archivo;
	archivo = fopen (filename.data(),"rb");	
	bool esRegistro;
	bool terminar = false;
	Registro registro(formato);
	while(!terminar){
		fread((char*)&esRegistro,sizeof(bool),1,archivo);
		if (esRegistro) {
			terminar = true;
			std::string serializado;
			char leido;
			fread(&leido,sizeof(leido),1,archivo);
			while(leido!='\n'){
					serializado.append(&leido,sizeof(char));
					fread(&leido,sizeof(leido),1,archivo);
			}
			registro.hidratar(serializado.c_str(),serializado.size());
		} else{
			fseek(archivo,descriptor.descriptorSize(),SEEK_CUR);
		}
	}
	fclose(archivo);
	return registro;
}