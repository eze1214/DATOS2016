#ifndef OPERADORPROYECCION_H
#define OPERADORPROYECCION_H
#include "gestor_aa_block.h"
#include "gestor_aa_rrlv.h"
#include <vector>
class OperadorProyeccion{
public:
	OperadorProyeccion(std::string filename,GestorAA & gestor, std::vector<unsigned> & listaCampos);
	OperadorProyeccion(std::string filename,GestorAARRLV& gestor, vector< unsigned >& listaCampos);

};

#endif // OPERADORPROYECCION_H
