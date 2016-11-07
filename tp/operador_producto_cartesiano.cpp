#include "operador_producto_cartesiano.h"
#include <string>
OperadorProducto::OperadorProducto(std::string filename, GestorAA& gestor, GestorAA& gestor2){
	std::string coma = ",";
	GestorAA nuevo (filename,gestor.getTamBloque(),gestor.getFormato() + coma + gestor2.getFormato());
	std::vector <unsigned short> bloquesAProcesar = gestor.getNumBloquesOcupados();
		Bloque bloque;
	for (unsigned i = 0; i< bloquesAProcesar.size();++i){
		bloque = gestor.getBloque(bloquesAProcesar[i]);
		for(unsigned j = 0; j<bloque.cantRegistros();j++){
				Registro registro1(gestor.getFormato());
				Registro registro2(gestor2.getFormato());
				registro1 = bloque.getRegistro(j);
				
				std::vector <unsigned short> bloquesAProcesar2 = gestor2.getNumBloquesOcupados();
				Bloque bloque2;
				for (unsigned k = 0; k< bloquesAProcesar2.size();++k){
					bloque2 = gestor2.getBloque(bloquesAProcesar2[k]);
					for(unsigned l = 0; l<bloque2.cantRegistros();l++){
						registro2 = bloque2.getRegistro(l);
						Registro registro3(gestor.getFormato()+","+gestor2.getFormato());
						registro3.suma(registro1,registro2);
						nuevo.insert(registro3);
					}
				}
		}
	}
}

OperadorProducto::OperadorProducto(std::string filename, GestorAARRLV& gestor, GestorAARRLV& gestor2){
	std::string coma = ",";
	GestorAARRLV nuevo (filename,gestor.getFormato() + coma + gestor2.getFormato());

	Registro registro1(gestor.getFormato());
	Registro registro2(gestor2.getFormato());
	
	int salida;
	bool terminar = false;

	while(!terminar){
		salida = gestor.read(registro1);
		if (salida == 0) {
			terminar = true;
		}else{
			int salida2;
			bool terminar2 = false;
			while(!terminar2){
				salida2 = gestor.read(registro2);
				if (salida2 == 0) {
					terminar2 = true;
				}else{
					Registro registro3(gestor.getFormato()+","+gestor2.getFormato());
					registro3.suma(registro1,registro2);
					nuevo.write(registro3);
				}
			}	
		}
	}
}