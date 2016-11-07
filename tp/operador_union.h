#ifndef OPERADORUNION_H
#define OPERADORUNION_H
#include "gestor_aa_block.h"
#include "gestor_aa_rrlv.h"
class OperadorUnion{
public:
	OperadorUnion (std::string filename,GestorAA& gestor, GestorAA& gestor2);
	OperadorUnion (std::string filename, GestorAARRLV& gestor, GestorAARRLV& gestor2);
};

#endif // OPERADORUNION_H
