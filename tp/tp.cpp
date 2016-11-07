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
#include "gestor_aa_block.h"
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
	OperadorProducto("producto.bin",gestor,gestor3);

}

void pruebas2(){
	char a = 5;
	short b = 10;
	int c = 20;
	ArchRRLV archivo("RRLV.bin","i1,i2,i4");
	Registro registro("i1,i2,i4");
	registro.writeCampo((char*)&a,sizeof(a),0);
	registro.writeCampo((char*)&b,sizeof(b),1);
	registro.writeCampo((char*)&c,sizeof(c),2);

	archivo.add(registro);
	
	a = 50;
	registro.writeCampo((char*)&a,sizeof(a),0);
	registro.writeCampo((char*)&b,sizeof(b),1);
	registro.writeCampo((char*)&c,sizeof(c),2);
	archivo.add(registro);
	Condicion condicion; 
	condicion.add(1,"i1",(char * )&a,sizeof(char));
	archivo.close();
	GestorAARRLV gestor("RRLV.bin");
	OperadorSeleccion operador ("RRLVSeleccion.bin",gestor,condicion);

	ArchRRLV archivo2("RRLV2.bin","i1,i2,i4");
	archivo2.add(registro);
	archivo2.close();
	GestorAARRLV gestor2("RRLV2.bin");
	OperadorUnion("RRLVUnion.bin",gestor,gestor2);	
}

void pruebaUnion(){
	char a = 5;
	short b = 10;
	int c = 20;
	ArchRRLV archivo("RRLV.bin","i1,i2,i4");
	Registro registro("i1,i2,i4");
	registro.writeCampo((char*)&a,sizeof(a),0);
	registro.writeCampo((char*)&b,sizeof(b),1);
	registro.writeCampo((char*)&c,sizeof(c),2);

	archivo.add(registro);
	
	a = 50;
	registro.writeCampo((char*)&a,sizeof(a),0);
	registro.writeCampo((char*)&b,sizeof(b),1);
	registro.writeCampo((char*)&c,sizeof(c),2);
	archivo.add(registro);
	archivo.close();
	
	ArchRRLV archivo2("RRLV2.bin","i1,i2,i4");
	archivo2.add(registro);
	archivo2.close();
	
	GestorAARRLV gestor("RRLV.bin");
	GestorAARRLV gestor2("RRLV2.bin");
	
	OperadorUnion("RRLVUnion.bin",gestor,gestor2);		
}

void exportarCSV(){
	std::string nombre;
	std::string nombreDestino;
	cout<<"Ingrese el nombre del archivo de bloques de registro de longitud variable a exportar"<<std::endl;
	cin>>nombre;
	cout<<"Ingrese el nombre del archivo csv, con extension"<<std::endl;
	cin>>nombreDestino;

	GestorAA gestor(nombre);
	gestor.exportar(nombreDestino);
}

int tipoArchivo(){
	int tipoArchivo;
	std::cout<<"Ingrese el tipo de archivo"<<std::endl;
	std::cout<<"1. Bloques de registro de longitud variable"<<std::endl;
	std::cout<<"2. Registros de longitud variable"<<std::endl;
	std::cin>>tipoArchivo;
	return tipoArchivo;;
}
void operadorSeleccion(){
	int tipo;
	std::string arch1;
	std::string archDestino;
	int cantidades;
	std::cout<<"Ingrese el nombre del archivo a procesar con extension"<<std::endl;
	std::cin>>arch1;
	std::cout<<"Ingrese el nombre del archivo destino con extension"<<std::endl;
	std::cin>>archDestino;
	tipo = tipoArchivo();
	std::cout<<"Ingrese la cantidad de condiciones";
	std::cin>>cantidades;

	Condicion condicion;
	
	for(int i = 0; i< cantidades; i++){
		std::string formato;
		std::cout<<"Ingrese el formato del elemento "<<i<<" de la condicion ej: i1 "<<std::endl;
		std::cin>>formato;
		if (formato == "i1"){
			char valor;
			std::cout<<"Ingrese el valor del elemento "<<std::endl;
			std::cin>>valor;
			condicion.add(i,formato,(char * )&valor,sizeof(valor));
		} else if(formato == "i2"){
			short valor;
			std::cout<<"Ingrese el valor del elemento "<<std::endl;
			std::cin>>valor;
			condicion.add(i,formato,(char * )&valor,sizeof(valor));
		} else if(formato == "i4"){
			int valor;
			std::cout<<"Ingrese el valor del elemento "<<std::endl;
			std::cin>>valor;
			condicion.add(i,formato,(char * )&valor,sizeof(valor));
		} else if(formato == "sL" or formato == "sD"){
			std::string valor;
			std::cout<<"Ingrese el valor del elemento, menor a 256"<<std::endl;
			std::cin>>valor;
			condicion.add(i,formato,(char * )valor.c_str() ,valor.size());
		} else if(formato == "d"){
			const int tamValor = 8;
			std::string valor;
			std::cout<<"Ingrese el valor del elemento"<<std::endl;
			std::cin>>valor;
			condicion.add(i,formato,(char * )valor.c_str() ,tamValor);
		}else if(formato == "dt"){
			const int tamValor = 15;
			std::string valor;
			std::cout<<"Ingrese el valor del elemento"<<std::endl;
			std::cin>>valor;
			condicion.add(i,formato,(char * )valor.c_str() ,tamValor);
		}
	}

	switch(tipo){
		case 1:{
			GestorAA gestor(arch1);
			OperadorSeleccion operador(archDestino,gestor,condicion);		
		}
		break;
		case 2:{
			GestorAARRLV gestor(arch1);
			OperadorSeleccion operador(archDestino,gestor,condicion);
		}
		break;
	}
	
}

void operadorUnion(){
	int tipo;
	std::string arch1;
	std::string arch2;
	std::string archDestino;
	std::cout<<"Ingrese el nombre del archivo a procesar con extension"<<std::endl;
	std::cin>>arch1;
	std::cout<<"Ingrese el nombre del archivo a procesar con extension"<<std::endl;
	std::cin>>arch2;
	std::cout<<"Ingrese el nombre del archivo destino con extension"<<std::endl;
	tipo = tipoArchivo();
	
	switch(tipo){
		case 1:{
			GestorAA gestor(arch1);
			GestorAA gestor2(arch2);
			OperadorUnion operador(archDestino,gestor,gestor2);}		
		break;
		case 2:{
			GestorAARRLV gestor(arch1);
			GestorAARRLV gestor2(arch2);
			OperadorUnion operador(archDestino,gestor,gestor2);}
		break;
	}
}

void operadorProyeccion(){
	int tipo;
	int n;
	std::string arch1;
	std::string archDestino;
	std::cout<<"Ingrese el nombre del archivo a procesar con extension"<<std::endl;
	std::cin>>arch1;
	std::cout<<"Ingrese el nombre del archivo destino con extencion"<<std::endl;
	std::cin>>archDestino;
	tipo = tipoArchivo();
	std::cout<<"Ingrese la cantidad de campos a proyectar"<<std::endl;
	std::cin>>n;
	std::vector<unsigned> lista;
	for(int i = 0;i<n;i++){
		int num;
		std::cout<<"Ingrese el numero del campot a proyectar"<<std::endl;
		std::cin>>num;	
		lista.push_back(num);
	}
	switch(tipo){
		case 1:{
			GestorAA gestor (arch1);
			OperadorProyeccion operador(archDestino,gestor,lista);}		
		break;
		case 2:{
			GestorAARRLV gestor(arch1);
			OperadorProyeccion operador(archDestino,gestor,lista);}
		break;
	}
}

void operadorProducto(){
	int tipo;
	std::string arch1;
	std::string arch2;
	std::string archDestino;
	std::cout<<"Ingrese el nombre del archivo a procesar con extension"<<std::endl;
	std::cin>>arch1;
	std::cout<<"Ingrese el nombre del archivo a procesar con extension"<<std::endl;
	std::cin>>arch2;
	std::cout<<"Ingrese el nombre del archivo destino con extension"<<std::endl;
	std::cin>>archDestino;
	tipo = tipoArchivo();
	
	switch(tipo){
		case 1:{
			GestorAA gestor(arch1);
			GestorAA gestor2(arch2);
			OperadorProducto operador(archDestino,gestor,gestor2);}		
		break;
		case 2:{
			GestorAARRLV gestor(arch1);
			GestorAARRLV gestor2(arch2);
			OperadorProducto operador(archDestino,gestor,gestor2);
		}

			//OperadorProductoCartesiano operador(archDestino,gestor,gestor2);}		
		break;
	}	
}
void ejecutarOperador(){
	int operador;
	std::string arch1;
	
	do{
	std::cout<<"Ingrese el operador que quiere ejecutar"<<std::endl;
	std::cout<<"1. Seleccion"<<std::endl;
	std::cout<<"2. Union"<<std::endl;
	std::cout<<"3. Proyeccion"<<std::endl;
	std::cout<<"4. Producto Cartesiano"<<std::endl;
	std::cout<<"5.Volver al menu principal"<<std::endl;
	std::cin>>operador;
		
		switch(operador){
			case 1:
				operadorSeleccion();		
			break;
			case 2:
				operadorUnion();
			break;
			case 3:
				operadorProyeccion();
			break;
			case 4:
				operadorProducto();
			break;
			case 5:
			break;
			default:
				std::cout<<"Opcion incorrecta"<<std::endl;
		}
	}while(operador!=5);
}

int main(int argc, char * argv[]){
	int op;
	do{
	std::cout<<"Ingrese la opcion"<<std::endl;
	std::cout<<"1. Exportar a CSV"<<std::endl;
	std::cout<<"2. Ejecutar operador"<<std::endl;
	std::cout<<"3. Salir"<<std::endl;

	std::cin>>op;
	switch(op){
		case 1:
			exportarCSV();
			std::cout<<"Archivo Exportado"<<std::endl;
		break;
		case 2:
			ejecutarOperador();
			std::cout<<"Operador ejecutado"<<std::endl;
		break;
		case 3:
			break;
		default:
			std::cout<<"Opcion incorrecta"<<std::endl;
	}
}while(op != 3 );
	return 0;
}