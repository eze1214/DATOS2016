#include "gestor_aa_rrlv.h"
#include <string>
#include "registro.h"

GestorAARRLV::GestorAARRLV(std::string nombre):archivo(nombre){}

GestorAARRLV::GestorAARRLV(std::string  nombre,std::string  formato):archivo(nombre,formato){}

int GestorAARRLV::read(Registro & registro){
	return archivo.read(registro);
}

void GestorAARRLV::write(Registro & registro){
	archivo.add(registro);
}

std::string GestorAARRLV::getFormato(){
	return archivo.getFormato();
}