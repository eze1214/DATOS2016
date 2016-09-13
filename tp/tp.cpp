#include <iostream>
#include "registro.h"
#include <vector>
#include <cstdlib>
#include <cstring>
#include "bytemap.h"
#include "arch_block_rrlv.h"
#include "bloque.h"
#include "registro.h"
#include "arch_blocks.h"
#include "gestor_aa.h"
int main(int argc, char * argv[]){
  ArchBlockRRLV archivo("prueba.bin",512,"i2,i2,d,dt");
	Registro registro("i2,i2,d,dt");
	short a = 20;
	short b = 5;
	char fecha [] = "19901214";
	char fechaLarga [] = "19901214-231223";
	std::string buffer;
	registro.writeCampo((char*)&a,sizeof(short),0);
	registro.writeCampo((char*)&b,sizeof(short),1);
	registro.writeCampo(fecha,sizeof(fecha),2);
	registro.writeCampo(fechaLarga,sizeof(fechaLarga),3);
	Bloque bloque;
	for(int i = 0; i<5;i++)
	bloque.add(registro);
	archivo.insert(bloque);
	//ArchBlockRRLV archivo2("prueba.bin");
	//Bloque bloque2 = archivo2.getBloque(1);
	//Registro registro1 = bloque2.getRegistro(0);
	//registro.print();
	//std::cout<<std::endl;
	//registro1.print();
	GestorAA gestor("prueba.bin");
	gestor.exportar("prueba.csv");
	return 0;
}