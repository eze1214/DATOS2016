#include "operador_union.h"
OperadorUnion::OperadorUnion::OperadorUnion(std::string filename, GestorAA& gestor, GestorAA& gestor2){
	GestorAA nuevo (filename,gestor.getTamBloque(),gestor.getFormato());
	std::vector <unsigned short> bloquesAProcesar = gestor.getNumBloquesOcupados();
		Bloque bloque;
	for (unsigned i = 0; i< bloquesAProcesar.size();++i){
		bloque = gestor.getBloque(bloquesAProcesar[i]);
		for(unsigned j = 0; j<bloque.cantRegistros();j++){
				Registro registro(gestor.getFormato());
				registro = bloque.getRegistro(j);
				nuevo.insert(registro);
		}
	}
	
	bloquesAProcesar = gestor2.getNumBloquesOcupados();
	for (unsigned i = 0; i< bloquesAProcesar.size();++i){
		bloque = gestor2.getBloque(bloquesAProcesar[i]);
		for(unsigned j = 0; j<bloque.cantRegistros();j++){
				Registro registro(gestor2.getFormato());
				registro = bloque.getRegistro(j);
				nuevo.insert(registro);
		}
	}
}
