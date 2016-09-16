#include "operador_producto_cartesiano.h"
#include <string>
#include "gestor_aa.h"
OperadorProductoCartesiano::OperadorProductoCartesiano(std::string filename, GestorAA& gestor, GestorAA& gestor2){
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
						registro3.print();
						std::cout<<std::endl;
						nuevo.insert(registro3);
					}
				}
		}
	}
}