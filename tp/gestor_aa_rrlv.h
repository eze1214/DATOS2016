#ifndef GESTOR_AA_RRLV
#define GESTOR_AA_RRLV

#include "archrrlv.h"
#include "registro.h"
#include <string>

class GestorAARRLV{
private:
	ArchRRLV archivo;

public:
GestorAARRLV(std::string nombre);
GestorAARRLV(std::string  nombre,std::string  formato);

//Devuelve 0 cuando llega al eof
int read(Registro & registro);

void write(Registro & registro);

std::string getFormato();
};
#endif
