#ifndef GESTORAA_BLOCK_H
#define GESTORAA_BLOCK_H
#include "arch_block_rrlv.h"
#include "bloque.h"
#include "registro.h"
class GestorAA{
private:
	unsigned contadorBloque;
	unsigned contadorRegistro;
	ArchBlockRRLV archivo;
public:


Registro getRegistro();
bool find(Registro & registro);
GestorAA(std::string filename);
void exportar(std::string csv);
GestorAA(std::string  nombre, unsigned short tamBlock,
							  std::string  formato);
unsigned short getTamBloque();
std::string getFormato();
std::vector <unsigned short>getNumBloquesOcupados();
Bloque getBloque(unsigned numBlk){
	Bloque bloque = archivo.getBloque(numBlk);
	Registro registro = bloque.getRegistro(0);
	return bloque;
}

void insert(Registro registro){
		archivo.insert(registro);
}
};

#endif // GESTORAA_BLOCK_H
