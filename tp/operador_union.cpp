#include "operador_union.h"
OperadorUnion::OperadorUnion(std::string filename, GestorAA& gestor, GestorAA& gestor2){
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

OperadorUnion::OperadorUnion(std::string filename, GestorAARRLV& gestor, GestorAARRLV& gestor2){
	GestorAARRLV nuevo (filename,gestor.getFormato());
	Registro registro(gestor.getFormato());
	
	int salida;
	bool terminar = false;

	while(!terminar){
		salida = gestor.read(registro);
		if (salida == 0) {
			terminar = true;
		}else{
					nuevo.write(registro);}
		}

	terminar = false;

while(!terminar){
		salida = gestor2.read(registro);
		if (salida == 0) {
			terminar = true;
		}else{
					nuevo.write(registro);}
	}
}