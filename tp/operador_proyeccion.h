#ifndef OPERADORPROYECCION_H
#define OPERADORPROYECCION_H
#include "gestor_aa.h"
#include <vector>
class OperadorProyeccion{
public:
	OperadorProyeccion(std::string filename,GestorAA & gestor, std::vector<unsigned> & listaCampos);
};

#endif // OPERADORPROYECCION_H
