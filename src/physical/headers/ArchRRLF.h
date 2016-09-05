/*
 * archRRLF.h
 *
 *  Created on: 23/10/2015
 *      Author: ezequiel
 */

#ifndef SRC_PHYSICAL_HEADERS_ARCHRRLF_H_
#define SRC_PHYSICAL_HEADERS_ARCHRRLF_H_
#include "BitMap.h"
#include "Parser.h"
#include "ArchBlocks.h"
class ArchRRLF{
private:
	ArchBlocks * archBlocks;
	BitMap * bitMap;
	Parser parser;
	unsigned tmnReg;
	char * block;
	bool archivoVacio();
	void saveBitMap();
	void openBitMap();
public:
	bool del(Registro &);
	int edit(Registro &);
	int insert(Registro&);
	int insertU(Registro&);
	int read(Registro &);
	int search(Registro &);
	ArchRRLF(string,unsigned);
	~ArchRRLF();
};



#endif /* SRC_PHYSICAL_HEADERS_ARCHRRLF_H_ */
