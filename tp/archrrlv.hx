#ifndef ARCHRRLV_H
#define ARCHRRLV_H
#include <string>
#include <iostream>
#include "registro.h"
#include <cstring>

class AchRRLV;

 class DescriptorEspacioLibre{
	friend class ArchRRLV;
	bool esRegistro;
	unsigned regSize;
	unsigned proximo;
	bool ultimo;	
public:
	
	DescriptorEspacioLibre():esRegistro(false),ultimo(true){}
	void hidratar(char * buffer, unsigned size){
		memcpy((char*)&size, buffer, sizeof(unsigned));
		memcpy((char*)&proximo,buffer+sizeof(unsigned),sizeof(unsigned));
		memcpy((char*)ultimo,buffer+sizeof(unsigned)+sizeof(unsigned),sizeof(bool));
	}
	void serializar(std::string & buffer){
		buffer.clear();
		buffer.append((char *)&esRegistro,sizeof(bool));
		buffer.append((char *)&regSize,sizeof(unsigned));
		buffer.append((char * )& proximo,sizeof(unsigned));
		buffer.append((char *) & ultimo,sizeof(bool));
	}
	
	unsigned descriptorSize(){
			return (sizeof(esRegistro)+sizeof(regSize)+sizeof(proximo)+sizeof(ultimo));
	}
	
};

class DescriptorRegistro{
	friend class ArchRRLV;
	bool esRegistro;
	std::string registro;
	const char fin;
public:
	DescriptorRegistro (Registro & registro):esRegistro(true),fin('\n'){
		registro.serializar(this->registro);
	}
	void serializar(std::string & buffer){
			buffer.clear();
			buffer.append((char*)&esRegistro,sizeof(bool));
			buffer.append(registro.c_str(),registro.size());
			buffer.append(&fin,sizeof(char));
	}
	
	void hidratar(std::string buffer){
		unsigned contador = 0;
		registro.clear();
		memcpy((char*)&esRegistro, buffer.c_str(),sizeof(bool));
		contador += sizeof(bool);
		while((buffer.c_str()+contador)!='\n'){
				registro.append(buffer.c_str()+contador,sizeof(char));
				contador+=sizeof(char);
		}
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
