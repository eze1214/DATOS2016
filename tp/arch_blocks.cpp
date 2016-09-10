/*
 * ArchBlocks.cpp
 *
 *  Created on: 27/6/2015
 *      Author: ezequiel
 */

#include "arch_bloks.h"

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

void ArchBlocks::crearArchivo(string nombreArchivo){
	FILE * archivo;
	archivo = fopen(nombreArchivo.data(),"wt");
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
		crearArchivo(nombreArchivo);
	}
}

int ArchBlocks::getCantidadBloques(){
	return this->cantidadDeBloques;
}
ArchBlocks::~ArchBlocks() {
}

void ArchBlocks::leerBloque(char* destino,int numeroBloque){
	FILE *archivo;
	archivo = fopen (nombreArchivo.data(),"rb");
	fseek(archivo,(numeroBloque)*tamanioBloque,SEEK_SET);
	if (fread(destino,tamanioBloque,1,archivo)==0) cout<<"Error Lectura"<<endl;
	fclose(archivo);
}

//Sobrescribe el numero de bloque especificado
void ArchBlocks::grabarBloque(char *bloque,unsigned int numeroDeBloque){
	FILE *archivo;
	archivo = fopen (nombreArchivo.data(),"r+b");
	fseek(archivo,tamanioBloque * numeroDeBloque,SEEK_SET);
	fwrite (bloque,1,tamanioBloque,archivo);
	fclose(archivo);
}
//Graba un bloque al final
void ArchBlocks::grabarBloque(char * bloque ){
	FILE *archivo;
	archivo = fopen (nombreArchivo.data(),"r+b");
	fseek(archivo,0,SEEK_END);
	fwrite (bloque,1,tamanioBloque,archivo);
	fclose(archivo);
}

