#include "operador_seleccion.h"
#include "registro.h"
#include <vector>
OperadorSeleccion::OperadorSeleccion(std::string filename, GestorAA& gestor, Condicion& condicion):
										gestor(gestor),condicion(condicion){
	GestorAA nuevo (filename,gestor.getTamBloque(),gestor.getFormato());
	
	std::vector <unsigned short> bloquesAProcesar = gestor.getNumBloquesOcupados();
	Bloque bloque;
	Registro registro(gestor.getFormato());
	for (unsigned i = 0; i< bloquesAProcesar.size();++i){
		std::cout<<"Bloque "<<i<<"numero logico "<<bloquesAProcesar[i]<<std::endl;
		bloque = gestor.getBloque(bloquesAProcesar[i]);
		std::cout<<"bloque "<<(char*)&bloque<<std::endl;
		for(unsigned j = 0; j<bloque.cantRegistros()-1;j++){
				std::cout<<"registro "<<j<<std::endl;
				registro = bloque.getRegistro(i);
				std::cout<<registro<<std::endl;
				//if (condicion.evaluar(registro))
					//nuevo.insert(registro);
		}
	}
}
