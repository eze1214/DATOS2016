/*
 * main.cpp
 *
 *  Created on: 12/09/2015
 *      Author: cristian
 */

#include <iostream>
#include "pruebas.h"
#include "./application/headers/Alta.h"
#include "./application/headers/ArmadorComandos.h"
#include <cstring>
//#include "./logical/headers/Ventas.h"
//#include "./logical/headers/Fecha.h"
//#include "./physical/headers/Parser.h"


int main(int argc,char * argv[]) {
//	pruebas prueba;
//	prueba.RRLF();
	ArmadorComandos armadorComando(argv[1],argv[2],argv[3]);
	Comando * comando = armadorComando.getComando();
	armadorComando.destroyComando();



}

