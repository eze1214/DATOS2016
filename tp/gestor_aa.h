#ifndef GESTORAA_H
#define GESTORAA_H
#include "arch_block_rrlv.h"
class GestorAA{
private:
	ArchBlockRRLV archivo;
public:

GestorAA(std::string filename);
void exportar(std::string csv);
GestorAA(std::string  nombre, unsigned short tamBlock,
							  std::string  formato);
unsigned short getTamBloque();
};

#endif // GESTORAA_H
