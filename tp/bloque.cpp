#include "bloque.h"
#include <string>


void Bloque::edit(const Registro & registro, unsigned numeroRegistro){
		registros[numeroRegistro] = registro;
}


bool Bloque::del(const unsigned & numRegistro){
	bool exito = (numRegistro<=registros.size());	
	registros.erase(registros.begin()+numRegistro);
	return exito;
}


Registro Bloque::getRegistro(unsigned int numeroRegistro){
	return registros[numeroRegistro];
}

unsigned Bloque::cantRegistros(){
		return registros.size();
}

void Bloque::add(const Registro & registro){
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
