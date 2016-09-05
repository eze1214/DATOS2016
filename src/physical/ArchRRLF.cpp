/*
 * archRRLF.cpp
 *
 *  Created on: 23/10/2015
 *      Author: ezequiel
 */
#include "headers/ArchRRLF.h"

#include <string>
#define POSBITMAP 0
#define TAMBITMAP 20 //Cuantos bloques fisicos ocupa
					//Si tmnReg ocupa 19 tenemos 19 * 8 * 20 = 3040 registros
bool ArchRRLF::archivoVacio(){
	return (archBlocks->getCantidadBloques()==0);
}

void ArchRRLF::saveBitMap(){
	int offset = 0;
	char * block = new char[TAMBITMAP*tmnReg];
	memset(block,0,TAMBITMAP*tmnReg);
	bitMap->serializar(block);
	for(int i = 0;i<TAMBITMAP;i++){
		archBlocks->grabarBloque(block+offset,POSBITMAP+i);
		offset = offset + tmnReg;
	}

	delete [] block;
}

void ArchRRLF::openBitMap(){
	unsigned offset = 0;
	char * block = new char[TAMBITMAP* tmnReg];
	memset(block,0,tmnReg*TAMBITMAP);
	for(unsigned i = 0;i<TAMBITMAP;i++){
		archBlocks->leerBloque(block+offset,POSBITMAP+i);
		offset = offset + tmnReg;
	}
	if (bitMap!= NULL) delete bitMap;
	bitMap = new BitMap();
	bitMap->hidratar(block);
	delete [] block;
}

ArchRRLF::ArchRRLF(string fileName,unsigned tmnReg){
	this->tmnReg = tmnReg;
	this->archBlocks = new ArchBlocks(fileName,tmnReg);
	this->block = new char [tmnReg];
	bitMap = NULL;
	if(archivoVacio()){
		this->bitMap = new BitMap;
		saveBitMap();
		}
		else{
		openBitMap();
		}
}

ArchRRLF::~ArchRRLF(){
	delete archBlocks;
	delete bitMap;
	delete []block;
}

int ArchRRLF::edit(Registro & registro){
	int blockDest = 0;
	Registro * regHid = &registro.clone();
	*regHid = registro;
	if((blockDest = read(*regHid))!=-1){
		memset(block,0,tmnReg);
		parser.serializar(registro,block);
		archBlocks->grabarBloque(block,blockDest+TAMBITMAP);
		delete regHid;
		return blockDest;
	}
	delete regHid;
	return -1;

}
int ArchRRLF::insert(Registro& registro){
	int blockDest = 0;
	if((blockDest= bitMap->getGap())==-1){//Si no hay huecos inserto al final
		bitMap->appendBit();
		blockDest = bitMap->getTamanio();
	}
	else {
		bitMap->switchBit(blockDest);
		blockDest++;//le sumo uno pues tengo que trabajar con numero de bloque desde 1 hasta n
	}
	parser.serializar(registro,block);
	archBlocks->grabarBloque(block,blockDest+TAMBITMAP);
	this->saveBitMap();
	return blockDest;
}

bool ArchRRLF::del(Registro & registro){
	int blockDest= 0;
	if((blockDest = read(registro))!=-1){
		bitMap->switchBit(blockDest-1);//le resto 1 ya que esta hecho el bitMap a partir de 0 y yo necesito desde 1 contar
		memset(block,0,tmnReg);
		archBlocks->grabarBloque(block,blockDest+TAMBITMAP);
		this->saveBitMap();
		return true;
	}
	return false;
}

int ArchRRLF::insertU(Registro & registro){
	if(read(registro)==-1) return insert(registro);
	else
		return -1;
}
int ArchRRLF::read(Registro & registro){
	Registro * regHid = &registro.clone();
	bool found = false;
	unsigned i = 1;
	while((!found and i <= bitMap->getTamanio())){
		if((int)bitMap->getBit(i-1)!=0){
			archBlocks->leerBloque(block,i+TAMBITMAP);
			parser.hidratar(*regHid,block);
			if(registro.keycmp(*regHid)==0)
				found = true;
			else i++;
		}
		else i++;
	}
	if (found) {
		registro = *regHid;
		delete regHid;
		return i;
	}
	else {
		delete regHid;
		return -1;
	}
}


