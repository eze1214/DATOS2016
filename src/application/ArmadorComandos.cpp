#include "./headers/ArmadorComandos.h"
#include <cstring>
#include <iostream>
using namespace std;

void ArmadorComandos::obtenerArchivo(char* nombreArch){
	if(strcmp(nombreArch,"vendedores")==0) this->archivo = VENDEDORES;
	if(strcmp(nombreArch,"ventas")==0) this->archivo = VENTAS;
	if(strcmp(nombreArch,"productos")==0) this->archivo = PRODUCTOS;
	if(strcmp(nombreArch,"grupos")==0) this->archivo = GRUPOS;
}

void ArmadorComandos::obtenerTipoComando(char * opcion,char *path){
	if(strcmp(opcion,"-a")==0)	comando = new Alta(this->archivo,path);
}
ArmadorComandos::ArmadorComandos(char* opcion,char* archivo,char* path){
	this->obtenerArchivo(archivo);
	this->obtenerTipoComando(opcion,path);
}
ArmadorComandos::~ArmadorComandos(){

}

Comando * ArmadorComandos::getComando(){
	return comando;
}

void ArmadorComandos::destroyComando(){
	delete comando;
}


