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

std::string ArchRRLV::getFormato(){
	return formato;
}

void ArchRRLV::crearArchivo(std::string nombreArchivo,std::string configuracion){
	archivo = fopen(nombreArchivo.data(),configuracion.c_str());
	if (archivo != NULL) std::cout<<"archivo creado correctamente"<<std::endl;
	
	grabarFormato();	
	fclose (archivo);
}
//TODO revizar
/*Ahora esta todo encapsulado en la clase desriptores
 * Falta crear el comportamiento de cuando se agrega
 * un registro que busque en la lista de espacio libre cual es la 
 * mas conveniente.
 */
ArchRRLV::ArchRRLV(std::string filename){
	this->filename = filename;
	
	archivo = fopen(filename.data(),"rb+");
	
	leerFormato();

	puntero = ftell(archivo);
	fclose(archivo);
}
bool ArchRRLV::existeArchivo(std::string nombreArchivo){
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

void ArchRRLV::leerFormato(){
	char * buffer;
	size_t size = 0;
	int outRead;
	outRead = fread(&size,sizeof(size_t),1,archivo);
	buffer = new char[size];
	outRead = fread(buffer,size,1,archivo);
	if (outRead<=0) std::cout<<"Error de lectura en leerFormato"<<std::endl;
	formato.clear();
	formato.append(buffer,size);
	delete[] buffer;
}

void ArchRRLV::grabarFormato(){
	size_t formato_size = formato.size();
	fwrite((char *) & formato_size, sizeof(size_t),1,archivo);
	fwrite((char*) formato.c_str(),formato.size(),1,archivo);
}

void ArchRRLV::grabarDescriptor(){
	std::string serializado;
	descriptor.serializar(serializado);
	puntero = descriptor.getNext();
	unsigned char size = descriptor.getSize();
	fwrite(&size, sizeof(char),1,archivo);
	fwrite(serializado.c_str(),serializado.size(),1,archivo);
}

void ArchRRLV::leerDescriptor(unsigned offset){
	unsigned char size;
	fread(&size, sizeof(char), 1, archivo);
	char * buffer = new char[size];
	fread(buffer, size, 1, archivo);
	std::string serializado(buffer,size);
	descriptor.serializar(serializado);
	delete [] buffer;
}

void ArchRRLV::add(Registro & registro){
	std::string serializado;
	registro.serializar(serializado);
	this->grabarRegistro(serializado);
}

void ArchRRLV::buscarEspacioLibre(){
	fseek(archivo,0,SEEK_END); //TODO colocar la lógica	
}

void ArchRRLV::grabarRegistro( std::string registro){
	archivo = fopen (filename.data(),"r+b");
	buscarEspacioLibre();
	size_t size = registro.size();
	int salida = fwrite((char * ) & size, sizeof(size_t) ,1,archivo);
	salida = fwrite(registro.c_str(),size,1,archivo);
	if (salida <= 0) std::cout<<"error"<<std::endl;
	fclose (archivo);
}


void ArchRRLV::gotoPuntero(){
	fseek(archivo,puntero,SEEK_SET);
}

unsigned ArchRRLV::read(Registro & registro){
	size_t size;
	archivo = fopen (filename.data(),"rb");
	gotoPuntero();
	do{
		fread((char * ) &size, sizeof(size_t), 1, archivo);
		if (size==0 and !feof(archivo)){
			fseek(archivo,-(sizeof(unsigned)-1),SEEK_CUR);
		}
	} while(size==0 and !feof(archivo));

	if (size!=0) {
		char * buffer = new char [size];
		fread(buffer,size,1,archivo);
		registro.hidratar(buffer,size);
		delete [] buffer;
	}
	fclose(archivo);
	return size;
}