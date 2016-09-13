#ifndef OPERADORSELECCION_H
#define OPERADORSELECCION_H
#include "gestor_aa.h"
#include "condicion.h"
#include <string>
class OperadorSeleccion{
private:
	GestorAA & gestor;
	Condicion & condicion;
public:
	OperadorSeleccion(std::string filename, GestorAA & gestor, Condicion & condicion);
};

#endif // OPERADORSELECCION_H
