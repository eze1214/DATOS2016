#ifndef ARCHRRLV_H
#define ARCHRRLV_H
#include <string>
#include <iostream>
#include "registro.h"
#include <cstring>

class AchRRLV;

 class DescriptorEspacioLibre{
	friend class ArchRRLV;
	bool estaLibre;
	unsigned regSize;
	unsigned proximo;
	bool esUltimo;	
public:
	
	unsigned getNext(){return proximo;}
	DescriptorEspacioLibre():
			estaLibre(true),regSize(0),proximo(0),esUltimo(true){}
	
	void hidratar(std::string & buffer){
		unsigned offset = 0;
		const char * puntero = buffer.c_str();
		memcpy((char*)&estaLibre, puntero, sizeof(bool));
		offset += sizeof(bool);
		memcpy((char*)&regSize,puntero+offset,sizeof(unsigned));
		offset += sizeof(unsigned);
		memcpy((char*)&proximo,puntero+offset,sizeof(unsigned));
		offset += sizeof(unsigned);
		memcpy((char*)&esUltimo,puntero+offset,sizeof(bool));
		offset += sizeof(bool);
	}

	void serializar(std::string & buffer){
		buffer.clear();
		buffer.append((char *)&estaLibre,sizeof(bool));
		buffer.append((char *)&regSize,sizeof(unsigned));
		buffer.append((char * )& proximo,sizeof(unsigned));
		buffer.append((char *) & esUltimo,sizeof(bool));
	}
	
	unsigned getSize(){
			return (sizeof(estaLibre)+sizeof(regSize)+sizeof(proximo)+sizeof(esUltimo));
	}
	
};

class DescriptorRegistro{
	friend class ArchRRLV;
	std::string registro;

public:
	DescriptorRegistro (Registro & registro){
		registro.serializar(this->registro);
	}

	void serializar(std::string & buffer){
			buffer.clear();
			buffer.append(registro.c_str(),registro.size());
	}
	
	void hidratar(std::string buffer){
		registro.clear();
		registro = buffer;
	}
};

class ArchRRLV{
private:
	FILE * archivo;

	DescriptorEspacioLibre descriptor;
	std::string filename;
	std::string formato;
	bool abierto;
	bool existeArchivo(std::string nombreArchivo);
	void crearArchivo(std::string filename, std::string configuracion);
	unsigned puntero; //Contiene la posicion actual. Usado para lecturas secuenciales
	void grabarFormato();
	void leerFormato();
	void grabarDescriptor();
	void leerDescriptor(unsigned offset);
	void grabarRegistro(std::string registro);
	void buscarEspacioLibre();
	void gotoPuntero();
public:
	void close();
	bool eof();
	std::string getFormato();
	/*Constructor para crear un archivo nuevo*/
	ArchRRLV(std::string filename);

	/*Constructor para abrir un archivo*/
	ArchRRLV(std::string filename,std::string formato);

	~ArchRRLV();
	/*Lee un registro de forma secuencial
	 */
	unsigned read(Registro & registro);

	/*Elimina el registro que se encuentra en el ofset
	*/
	void delRegistro(unsigned offset);

	/*Si es mayor que el tamaño queda cortado el registro
	  si es menor lo rellena con 0
	*/
	void editRegistro(unsigned offset);

	void add(Registro & registro);
};

#endif // ARCHRRLV_H
