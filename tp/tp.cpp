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
#include "condicion.h"
#include "operador_seleccion.h"
#include "operador_proyeccion.h"
#include "operador_union.h"
#include "operador_producto_cartesiano.h"
#include "archrrlv.h"
void pruebas1(){
GestorAA gestor5("producto.bin");
	gestor5.exportar("productoExportado.csv");
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
					 	for(int i = 0; i<50;i++)
					 		archivo.insert(registro);
						registro.writeCampo((char*)&b,sizeof(short),0);
						archivo.insert(registro);
	//	bloque.add(registro);
	//archivo.insert(bloque);
	//ArchBlockRRLV archivo2("prueba.bin");
	//Bloque bloque2 = archivo2.getBloque(1);
	//Registro registro1 = bloque2.getRegistro(0);
	//registro.print();
	//std::cout<<std::endl;
	//registro1.print();
	
	GestorAA gestor("prueba.bin");
	//gestor.exportar("prueba.csv");
	GestorAA gestor2("prueba.bin");
	Condicion condicion;
	condicion.add(0,"i2",(char * )&b,sizeof(short));
	OperadorSeleccion operador("seleccion.bin",gestor,condicion);
	
	std::vector<unsigned> lista;
	lista.push_back(0);
	lista.push_back(2);
	OperadorProyeccion proyeccion("proyeccion.bin",gestor,lista);
	
	OperadorUnion unione("union.bin",gestor,gestor2);
	
	GestorAA gestor3("proyeccion.bin");
	OperadorProductoCartesiano("producto.bin",gestor,gestor3);

}

int main(int argc, char * argv[]){
	ArchRRLV archivo("RRLV.bin","i1,i2");
	return 0;
}