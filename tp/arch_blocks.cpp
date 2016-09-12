/*
 * ArchBlocks.cpp
 *
 *  Created on: 27/6/2015
 *      Author: ezequiel
 */

#include "arch_blocks.h"

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <cstring>
using namespace std;

int ArchBlocks::obtenerCantidadBloquesTotales(){
	FILE *archivo;
	archivo =fopen(nombreArchivo.data(),"r+b");
	fseek(archivo, 0, SEEK_END);
	float cuenta = ftell(archivo)/(float)this->tamanioBloque;
	int aux = (int) ceil(cuenta);
	unsigned int  numeroDeBloquesTotales = aux;
	fclose(archivo);
	return (numeroDeBloquesTotales);
}
bool ArchBlocks::existeArchivo(string nombreArchivo){
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

void ArchBlocks::crearArchivo(string nombreArchivo,std::string configuracion){
	FILE * archivo;
	archivo = fopen(nombreArchivo.data(),configuracion.c_str());
	if (archivo != NULL) cout<<"archivo creado correctamente"<<endl;
	fclose (archivo);

}
/*Constructor verifica si existe el archivo
 * en el caso de que exista obtiene la cantidad de bloques
 * sino crea el archivo
 */
ArchBlocks::ArchBlocks(string nombreArchivo,int tamanioBloque){
	this->nombreArchivo = nombreArchivo;
	this->tamanioBloque = tamanioBloque;
	if (existeArchivo(nombreArchivo)){
		this->cantidadDeBloques = this->obtenerCantidadBloquesTotales();
	}
	else {
		this->cantidadDeBloques = 0;
		crearArchivo(nombreArchivo,"wb+");
	}
}

void ArchBlocks::saveHeader(){
	short tamBlk = tamanioBloque;
	char fin = '\0';
	FILE *archivo;
	archivo = fopen (nombreArchivo.data(),"r+b");
	fseek(archivo,0,SEEK_SET);
	fwrite ((char*)&tamBlk,1,sizeof(short),archivo);
	fwrite ((char*)formato.c_str(),1,formato.size(),archivo);
	fwrite (&fin,1,sizeof(char),archivo);
	fclose(archivo);
	
}

void ArchBlocks::readHeader(){
	FILE *archivo;
	bool terminar = false;
	char aux = 0;
	archivo = fopen (nombreArchivo.data(),"rb");
	fseek(archivo,0 ,SEEK_SET);
	if (fread((char*)&tamanioBloque,1,sizeof(short),archivo)==0) std::cout<<"Error lectura"<<std::endl;
	formato.clear();
	do {
			if(fread(&aux,1,sizeof(char),archivo)==0) std::cout<<"Error lectura"<<std::endl;
			if (aux == '\0') 
				terminar = true;
			else
				formato.push_back(aux);
	} while (!terminar);
	fclose(archivo);	
	offset = sizeof(short) + formato.size() + sizeof(char);
}

ArchBlocks::ArchBlocks(std::string nombreArchivo){
	this->nombreArchivo = nombreArchivo; 
	if (existeArchivo(nombreArchivo)){
		std::cout<<"Abriendo el archivo"<<std::endl;
		readHeader();
		std::cout<<"Tam bloque "<<tamanioBloque<<std::endl;
		std::cout<<"Formato "<<formato<<std::endl;
	}
	else {
		std::cout<<"El archivo no existe"<<std::endl;
	}
}

/*El formato va a ser el siguiente
 * El archivo va a comenzar con una cabecera 2 dos bytes la cual va a indicar  
 * la cantidad de bytes. Seguido del formato guardado como un registro de
 * longitud variable. Finalizando con \0. 
 * Luego sigue el byteMap y los bloques todos de tamaño fijo.
 */
ArchBlocks::ArchBlocks(std::string nombreArchivo,unsigned short tamanioBloque,std::string formato){
	this->nombreArchivo = nombreArchivo;
	this->tamanioBloque = tamanioBloque;
	this->formato = formato;
	this->offset =  sizeof(unsigned short)+ formato.size()+ sizeof(char);
	if (existeArchivo(nombreArchivo)){
		std::cout<<"El archivo ya existe será sobreescribido"<<std::endl;
	}
	else {
		this->cantidadDeBloques = 0;
	}
	crearArchivo(nombreArchivo,"wb+");
	saveHeader();
}

int ArchBlocks::getCantidadBloques(){
	return this->cantidadDeBloques;
}
ArchBlocks::~ArchBlocks() {
}

void ArchBlocks::leerBloque(char* destino,int numeroBloque){
	FILE *archivo;
	archivo = fopen (nombreArchivo.data(),"rb");
	fseek(archivo,(numeroBloque*tamanioBloque)+ offset ,SEEK_SET);
	if (fread(destino,tamanioBloque,1,archivo)==0) cout<<"Error Lectura"<<endl;
	fclose(archivo);
}

void ArchBlocks::leerFormato(std::string & formato){
	FILE *archivo;
	char * destino = new char[offset];
	archivo = fopen (nombreArchivo.data(),"rb");
	fseek(archivo,0 ,SEEK_SET);
	if (fread(destino,offset,1,archivo)==0) cout<<"Error Lectura"<<endl;
	formato.clear();
	formato.insert(0,destino,offset);
	delete destino;
	fclose(archivo);	
}
void ArchBlocks::grabarFormato(std::string & formato){
	FILE *archivo;
	archivo = fopen (nombreArchivo.data(),"r+b");
	fseek(archivo,0,SEEK_SET);
	fwrite (formato.c_str(),1,formato.size(),archivo);
	fclose(archivo);
}

//Sobrescribe el numero de bloque especificado
void ArchBlocks::grabarBloque(const char *bloque,unsigned int numeroDeBloque){
	FILE *archivo;
	archivo = fopen (nombreArchivo.data(),"r+b");
	fseek(archivo,(tamanioBloque * numeroDeBloque)+offset,SEEK_SET);
	fwrite (bloque,1,tamanioBloque,archivo);
	fclose(archivo);
}
//Graba un bloque al final
void ArchBlocks::grabarBloque(char * bloque){
	FILE *archivo;
	archivo = fopen (nombreArchivo.data(),"r+b");
	fseek(archivo,0,SEEK_END);
	fwrite (bloque,1,tamanioBloque,archivo);
	fclose(archivo);
}

unsigned short ArchBlocks::getTamBlock(){
  return this->tamanioBloque;
}
	
std::string ArchBlocks::getFormato(){
    return this->formato;
}