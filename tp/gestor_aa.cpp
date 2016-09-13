#include "gestor_aa.h"
#include <fstream>
#include <vector>
#include "bloque.h"
GestorAA::GestorAA(std::string filename):archivo(filename){}

void GestorAA::exportar(std::string csv){
	ofstream fs(csv.data());
	std::vector <unsigned short> ocupados = archivo.getNumBloquesOcupados();
	std::vector <unsigned short>::iterator it = ocupados.begin();
	for(;it!=ocupados.end();it++){
			Bloque bloque = archivo.getBloque(*it);
			unsigned cantRegistros = bloque.cantRegistros();
			for(unsigned i = 0; i<cantRegistros; i++){
					Registro registro = bloque.getRegistro(i);
					fs<<registro;
			}
	}
	fs.close();
}