#ifndef ARCHRRLV_H
#define ARCHRRLV_H
#include <string>
#include <iostream>
#include "registro.h"
class ArchRRLV{
private:
	std::string filename;
	std::string formato;
	void existeArchivo(string nombreArchivo);
	unsigned puntero;
	
public:
	ArchRRLV(std::string filename,std::string formato);
	crearArchivo(std::string filename, std::string configuracion);
	
	/*Lee un registro de forma secuencial
	 */
	Registro readRegistro();
};

#endif // ARCHRRLV_H
