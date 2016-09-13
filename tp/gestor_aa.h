#ifndef GESTORAA_H
#define GESTORAA_H
#include "arch_block_rrlv.h"
class GestorAA{
private:
	ArchBlockRRLV archivo;
public:

GestorAA(std::string filename);
void exportar(std::string csv);

};

#endif // GESTORAA_H
