#include "bloque.h"
#include <string>
void Bloque::add(Registro & registro){
		registros.push_back(registro);
}

unsigned Bloque::serializar(std::string & buffer){
		it = registros.begin();
		buffer.clear();
		for(;it!=registros.end();++it){
			 std::string auxi; 
			 (*it).serializar(auxi);
			 buffer += auxi;
		}
	return size();	
	}
	
unsigned int Bloque::size(){
	unsigned contador = 0;
	it = registros.begin();
	for(;it!=registros.end();++it){
			contador += (*it).size();
	}
	return contador;
}
