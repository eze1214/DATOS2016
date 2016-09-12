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
int main(int argc, char * argv[]){
  ArchBlockRRLV archivo("prueba.bin",512,"i2,i2");
	Registro registro("i2,i2");
	short a = 20;
	short b = 5;
	std::string buffer;
	registro.writeCampo((char*)&a,sizeof(short),0);
	registro.writeCampo((char*)&b,sizeof(short),1);
	Bloque bloque;
	bloque.add(registro);
	archivo.insert(bloque);
	ArchBlocks archivo2("prueba.bin");
	Bloque bloque2 = archivo.getBloque(1);
	Registro registro1 = bloque2.getRegistro(0);
	Registro registro2 = bloque2.getRegistro(1);
	return 0;
}