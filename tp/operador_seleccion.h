#ifndef OPERADORSELECCION_H
#define OPERADORSELECCION_H
#include "gestor_aa_block.h"
#include "gestor_aa_rrlv.h"
#include "condicion.h"
#include <string>

class OperadorSeleccion{
private:
	Condicion & condicion;
public:
	OperadorSeleccion(std::string filename, GestorAARRLV& gestor, Condicion& condicion);
	OperadorSeleccion(std::string filename, GestorAA & gestor, Condicion & condicion);
	
};

#endif // OPERADORSELECCION_H
