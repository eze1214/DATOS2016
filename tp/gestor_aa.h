#ifndef GESTORAA_H
#define GESTORAA_H
#include "arch_block_rrlv.h"
#include "bloque.h"
class GestorAA{
private:
	ArchBlockRRLV archivo;
public:

GestorAA(std::string filename);
void exportar(std::string csv);
GestorAA(std::string  nombre, unsigned short tamBlock,
							  std::string  formato);
unsigned short getTamBloque();
std::string getFormato();
std::vector <unsigned short>getNumBloquesOcupados();
Bloque getBloque(unsigned numBlk){
	return archivo.getBloque(numBlk);
}

void insert(Registro registro){
		archivo.insert(registro);
}
};

#endif // GESTORAA_H
