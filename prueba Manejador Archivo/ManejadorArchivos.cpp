/*
 * ManejadorArchivos.cpp
 *
 *  Created on: 27/6/2015
 *      Author: ezequiel
 */

#include "ManejadorArchivos.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <cstring>
using namespace std;

int ManejadorArchivos::obtenerCantidadBloquesTotales(){
	FILE *archivo;
	archivo =fopen(nombreArchivo.data(),"r+b");
	fseek(archivo, 0, SEEK_END);
	float cuenta = ftell(archivo)/(float)this->tamanioBloque;
	int aux = (int) ceil(cuenta);
	unsigned int  numeroDeBloquesTotales = aux;
	fclose(archivo);
	return (numeroDeBloquesTotales);
}
bool ManejadorArchivos::existeArchivo(string nombreArchivo){
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

void ManejadorArchivos::crearArchivo(string nombreArchivo){
	FILE * archivo;
	archivo = fopen(nombreArchivo.data(),"wt");
	if (archivo != NULL) cout<<"archivo creado correctamente"<<endl;
	fclose (archivo);

}
//Constructor verifica si existe el archivo
//en el caso de que exista bufferiza el bytemap
//en caso contrario crea el archivo
ManejadorArchivos::ManejadorArchivos(string nombreArchivo,int tamanioBloque){
	this->nombreArchivo = nombreArchivo;
	this->mapaByte = new char [tamanioBloque];
	this->tamanioBloque = tamanioBloque;
	if (existeArchivo(nombreArchivo)){
		this->cantidadDeBloques = this->obtenerCantidadBloquesTotales();
		this->leerMapaByte();
	}
	else {
		cout<<"Archivo inexistente se procede a crear"<<endl;
		this->cantidadDeBloques = 0;
		crearArchivo(nombreArchivo);
	}
}

int ManejadorArchivos::getCantidadBloques(){
	return this->cantidadDeBloques;
}
ManejadorArchivos::~ManejadorArchivos() {
	delete [] this->mapaByte;
}
void ManejadorArchivos::leerMapaByte(){
	FILE *archivo;
	archivo = fopen (nombreArchivo.data(),"rb");
	fseek(archivo,0,SEEK_SET);
	if (fread(this->mapaByte,tamanioBloque,1,archivo)==0)cout<<"error Lectura"<<endl;
	fclose(archivo);
}
void ManejadorArchivos::leerBloque(char* destino,int numeroBloque){
	FILE *archivo;
	archivo = fopen (nombreArchivo.data(),"rb");
	fseek(archivo,(numeroBloque)*tamanioBloque,SEEK_SET);
	if (fread(destino,tamanioBloque,1,archivo)==0) cout<<"Error Lectura"<<endl;
	fclose(archivo);
}

//Sobrescribe el numero de bloque especificado
void ManejadorArchivos::grabarBloque(char *bloque,unsigned int numeroDeBloque){
	FILE *archivo;
	archivo = fopen (nombreArchivo.data(),"r+b");
	fseek(archivo,tamanioBloque * numeroDeBloque,SEEK_SET);
	fwrite (bloque,1,tamanioBloque,archivo);
	fclose(archivo);
}
//Graba un bloque al final
void ManejadorArchivos::grabarBloque(char * bloque ){
	FILE *archivo;
	archivo = fopen (nombreArchivo.data(),"r+b");
	fseek(archivo,0,SEEK_END);
	fwrite (bloque,1,tamanioBloque,archivo);
	fclose(archivo);
}

