#ifndef OPERADORPRODUCTOCARTESIANO1_H
#define OPERADORPRODUCTOCARTESIANO1_H
#include <string>
#include "gestor_aa_block.h"
#include "gestor_aa_rrlv.h"
class OperadorProducto{
public:
	OperadorProducto(std::string filename, GestorAARRLV & gestor, GestorAARRLV & gestor2);
	OperadorProducto(std::string filename, GestorAA& gestor, GestorAA& gestor2);
};

#endif // OPERADORPRODUCTOCARTESIANO1_H
