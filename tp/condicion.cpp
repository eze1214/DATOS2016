#include "condicion.h"
#include <iostream>
void Condicion::add(unsigned int nroCampo, std::string formato, char* value, unsigned int size){
	Evaluador evaluador(nroCampo,formato);
	evaluador.registro.writeCampo(value,size,0);
	this->condiciones.push_back(evaluador);
}

bool Condicion::evaluar(Registro& registro){
	bool evaluacion = true;
	for(unsigned i = 0; i<condiciones.size(); i++){
			if ((condiciones[i].registro.getCampo(0)).value != (registro.getCampo(condiciones[i].nroCampo)).value)
				evaluacion = false;
	}
	return evaluacion;
}
