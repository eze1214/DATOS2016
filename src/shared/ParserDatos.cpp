/*
 * parserDatos.cpp
 *
 *  Created on: 25/10/2015
 *      Author: ezequiel
 */
#include <iostream>
#include<string>
#include "./headers/ParserDatos.h"
using namespace std;



void borrarCaracterInutil(string & cadena)
{
	for(int i = 0;i<cadena.length();i++){
		if(cadena.at[i]== "\"") erase
	}
}
ParserDatos::ParserDatos(string datos){
	this->buffer = datos;
}

bool ParserDatos::getDato(string & dato){
	if (buffer.empty())return false;
	int pos = buffer.find(";");
	string devolver;
	devolver = buffer.substr(0,pos-1);
	buffer.erase(0,pos);
	borrarCaracterInutil(devolver);
	dato = devolver;
	return true;
}
ParserDatos::~ParserDatos(){

}




