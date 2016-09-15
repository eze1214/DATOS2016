#include "operador_seleccion.h"
#include "registro.h"
#include <vector>
OperadorSeleccion::OperadorSeleccion(std::string filename, GestorAA& gestor, Condicion& condicion):
										gestor(gestor),condicion(condicion){
										
	GestorAA nuevo (filename,gestor.getTamBloque(),gestor.getFormato());
	
	std::vector <unsigned short> bloquesAProcesar = gestor.getNumBloquesOcupados();
	Bloque bloque;

	for (unsigned i = 0; i< bloquesAProcesar.size();++i){
		bloque = gestor.getBloque(bloquesAProcesar[i]);
		for(unsigned j = 0; j<bloque.cantRegistros();j++){
				Registro registro(gestor.getFormato());
				registro = bloque.getRegistro(j);
				if (condicion.evaluar(registro)){
					std::cout<<"condicion verdadera "<<"bloque"<<i+1<<" registro"<<j<<std::endl;
					registro.print();
					nuevo.insert(registro);}
		}
	}
}
