#include "archrrlv.h"
#include "registro.h"


ArchRRLV::ArchRRLV(std::string filename, std::string formato){
	this->filename = filename;
	this->formato = formato;
	this->puntero = 0;
	if (existeArchivo(filename)){
		std::cout<<"El archivo ya existe será sobreescribido"<<std::endl;
	}
	crearArchivo(filename,"wb+");
}


bool ArchRRLV::existeArchivo(string nombreArchivo){
	bool existencia;
	FILE *archivo;
	archivo =fopen(nombreArchivo.data(),"r+b");
	if (archivo != NULL) {
		existencia = true;
		fclose(archivo);
	}
	else existencia = false;
	return existencia;
}

void ArchRRLV::crearArchivo(std::string nombreArchivo,std::string configuracion){
	FILE * archivo;
	archivo = fopen(nombreArchivo.data(),configuracion.c_str());
	if (archivo != NULL) std::cout<<"archivo creado correctamente"<<std::endl;
	fclose (archivo);

}

void ArchRRLV::addRegistro(Registro & registro){
	std::string serializado;
	registro.serializar(serializado);	
}

//Sobrescribe el numero de bloque especificado
void ArchRRLV::grabarRegistro(const std::string & registro){
	FILE *archivo;
	archivo = fopen (filename.data(),"r+b");
	fseek(archivo,0,SEEK_);//Calcularla
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

Registro ArchRRLV::delRegistro(){
		
}