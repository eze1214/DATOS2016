#include "gestor_aa.h"
#include <fstream>
#include <vector>
#include "bloque.h"
GestorAA::GestorAA(std::string filename):archivo(filename){}

void GestorAA::exportar(std::string csv){
	ofstream fs(csv.data());
	std::vector <unsigned short> ocupados = archivo.getNumBloquesOcupados();
	std::vector <unsigned short>::iterator it = ocupados.begin();
	std::cout<<"impresion"<<std::endl;
	for(;it!=ocupados.end();it++){
			std::cout<<"Imprimo un bloque nuevo"<<std::endl;
			Bloque bloque = archivo.getBloque(*it);
			unsigned cantRegistros = bloque.cantRegistros();
			for(unsigned i = 0; i<cantRegistros; i++){
				std::cout<<"Imprimo un registro nuevo"<<std::endl;
					Registro registro = bloque.getRegistro(i);
					cout<<registro;
			}
	}
	fs.close();
}