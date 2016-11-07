#include "gestor_aa_block.h"
#include <fstream>
#include <vector>
#include "bloque.h"
GestorAA::GestorAA(std::string filename):archivo(filename){}

bool GestorAA::find(Registro & registroComparar){
	bool find = false;
	std::vector <unsigned short> bloquesAProcesar = this->getNumBloquesOcupados();
	for (unsigned i = 0; i< bloquesAProcesar.size() and !find; ++i){
		Bloque bloque = this->getBloque(bloquesAProcesar[i]);
		for(unsigned j = 0; j<bloque.cantRegistros() and !find; j++){
				Registro registro(this->getFormato());
				registro = bloque.getRegistro(j);
				if (registroComparar.equals(registro))
					return find = true;
		}
	}
	return find;
}
unsigned short GestorAA::getTamBloque(){
		return archivo.getTamBloque();
}
GestorAA::GestorAA(string nombre, short unsigned int tamBlock, string formato):
													archivo(nombre,tamBlock,formato){}

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

string GestorAA::getFormato(){
	return archivo.getFormato();
}

std::vector<unsigned short> GestorAA::getNumBloquesOcupados(){
		return archivo.getNumBloquesOcupados();
}
