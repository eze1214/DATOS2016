/*
 * ArchRRLV.h
 *
 *  Created on: 12/10/2015
 *      Author: ezequiel
 */

#ifndef SRC_PHYSICAL_HEADERS_ARCHRRLV_H_
#define SRC_PHYSICAL_HEADERS_ARCHRRLV_H_
#include "ByteMap.h"
#include "ArchBlocks.h"
#include "./Parser.h"
#include "../../logical/headers/Registro.h"
using namespace std;
typedef unsigned short int TSize;
class ArchRRLV {
private:
	ArchBlocks * archBlocks;
	unsigned int tmnBlock;
	char * buffer;
	unsigned int buffOffset;
	unsigned int pBlock;//puntero que especifica numero de bloque que apunta el buffer dentro del archivo
	Parser parser;

	bool archivoVacio();
	void saveByteMap();
	void openByteMap();
	void addEndBlock();
	void addEndBlock(char *buffer,unsigned offset);
	int insert(char* data,unsigned int size);
	int getPosWriteBlock(char * block,unsigned length);
	void insertInMiddle(char *,int,TSize);
	void lshift(char*,unsigned,unsigned);

public:
	int edit(Registro &);
	int edit(Registro &,unsigned numBlock);
	int search(Registro &,unsigned numBlock);
	bool del(Registro &,unsigned numBlock);
	int del (Registro &);
	ByteMap * byteMap;
	void save();
	int insertU(const Registro &);
	int insert(const Registro &);
	void read(Registro &,unsigned numBlock,unsigned offset);
	bool search(Registro &);
	ArchRRLV(string,int);
	virtual ~ArchRRLV();
};



#endif /* SRC_PHYSICAL_HEADERS_ARCHRRLV_H_ */
