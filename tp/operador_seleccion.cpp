#include "operador_seleccion.h"
#include <iostream>
#include "registro.h"
#include <vector>

OperadorSeleccion::OperadorSeleccion(std::string filename, GestorAA& gestor, Condicion& condicion):
									condicion(condicion){
										
	GestorAA nuevo (filename,gestor.getTamBloque(),gestor.getFormato());
	
	std::vector <unsigned short> bloquesAProcesar = gestor.getNumBloquesOcupados();
	Bloque bloque;

	for (unsigned i = 0; i< bloquesAProcesar.size();++i){
		bloque = gestor.getBloque(bloquesAProcesar[i]);
		for(unsigned j = 0; j<bloque.cantRegistros();j++){
				Registro registro(gestor.getFormato());
				registro = bloque.getRegistro(j);
				if (condicion.evaluar(registro)){
					nuevo.insert(registro);}
		}
	}
}

OperadorSeleccion::OperadorSeleccion(std::string filename, GestorAARRLV& gestor, Condicion& condicion):
									condicion(condicion){
										
	GestorAARRLV nuevo (filename,gestor.getFormato());
	Registro registro(gestor.getFormato());
	bool terminar = false;
	int salida;
	while(!terminar){
		salida = gestor.read(registro);
		if (salida == 0) {
			terminar = true;
		}else{
			if (condicion.evaluar(registro)){
					nuevo.write(registro);}
		}
	}
}

