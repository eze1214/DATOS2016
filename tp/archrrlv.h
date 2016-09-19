#ifndef ARCHRRLV_H
#define ARCHRRLV_H
#include <string>
#include <iostream>
#include "registro.h"
#include <cstring>

 class DescriptorEspacioLibre{
	friend class ArchRRLV;
	unsigned RegSize;
	unsigned proximo;
	bool ultimo;	
public:
	DescriptorEspacioLibre():ultimo(true){}
	void hidratar(char * buffer, unsigned size){
		memcpy((char*)&size, buffer, sizeof(unsigned));
		memcpy((char*)&proximo,buffer+sizeof(unsigned),sizeof(unsigned));
		memcpy((char*)ultimo,buffer+sizeof(unsigned)+sizeof(unsigned),sizeof(bool));
	}
	void serializar(char * buffer, unsigned size){
		memcpy(buffer,(char*)&size,sizeof(unsigned);
		memcpy(buffer+sizeof(unsigned),(char*)&proximo,sizeof(unsigned));
		memcpy(buffer+sizeof(unsigned)+sizeof(unsigned),(char*)&ultimo,sizeof(bool));
	}
	unsigned descriptorSize(){
			return (sizeof(unsigned) + sizeof(unsigned) +sizeof(bool));
	}
	
};
class ArchRRLV{
private:
	DescriptorEspacioLibre descriptor;
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
