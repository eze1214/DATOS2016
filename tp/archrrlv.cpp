#include "archrrlv.h"
#include "registro.h"
#include <cstdio>

ArchRRLV::ArchRRLV(std::string filename, std::string formato){
	this->filename = filename;
	this->formato = formato;
	this->puntero = 0;
	if (existeArchivo(filename)){
		std::cout<<"El archivo ya existe será sobreescribido"<<std::endl;
	}
	crearArchivo(filename,"wb+");
}

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
	bool esRegistro = false;
	fwrite((char*)esRegistro,sizeof(bool),1,archivo);
	unsigned size = descriptor.descriptorSize();
	char * buffer = new char[size];
	
	descriptor.proximo = formato.size() + size + sizeof(char) + sizeof(bool);
	descriptor.RegSize = 0;
	descriptor.serializar(buffer,size);
	
	fwrite((char *)buffer,size,1,archivo);
	delete [] buffer;
	fclose (archivo);
}

void ArchRRLV::addRegistro(Registro & registro){
	std::string serializado;
	registro.serializar(serializado);	
	grabarRegistro(serializado);
}

void ArchRRLV::readDescriptor(){
	
	fseek(archivo,formato.size+1);
	
}
void ArchRRLV::buscarEspacioLibre(FILE * archivo){
	readDescriptor();	
}
void ArchRRLV::grabarRegistro(const std::string & registro){
	FILE *archivo;
	archivo = fopen (filename.data(),"r+b");
	buscarEspacioLibre(archivo);
	int size = registro.size();
	fwrite((char*)&size,1,sizeof(int),archivo);
	fwrite (registro.c_str(),1,registro.size(),archivo);
	fclose(archivo);
}


Registro ArchRRLV::readRegistro(){
		//TODO Poner la logica para no leer el bloque de espacios libre
	FILE *archivo;
	archivo = fopen (filename.data(),"rb");	
	fseek(archivo,puntero,SEEK_CUR);
	int size=0;
	puntero += fread((char*)&size,sizeof(int),1,archivo);
	char * buffer = new char[size];
	//TODO falta controlar el fin de archivo;
	puntero += fread((char*)buffer,size,1,archivo);
	Registro registro(this->formato);
	registro.serializar(buffer,size);
	delete buffer[];
	fclose(archivo);
	return registro;
}