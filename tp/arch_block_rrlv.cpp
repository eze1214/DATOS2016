#include "arch_block_rrlv.h"
#include <string>
#include <iostream>
#include <cstring>
#define offset 32

ArchBlockRRLV::ArchBlockRRLV(std::string  nombre, unsigned short  tamBlock, std::string  formato):	archBlocks(nombre,tamBlock,formato),
											byteMap(tamBlock)
										{}

ArchBlockRRLV::ArchBlockRRLV(std::string nombre):archBlocks(nombre){
	unsigned short tamBlock = archBlocks.getTamBlock();
	byteMap.setTamBlock(tamBlock);
	char * buffer = new char[tamBlock];
	memset(buffer,0,tamBlock);
	archBlocks.leerBloque(buffer,0);
	std::string buffer2;
	buffer2.insert(0,buffer,tamBlock);
	byteMap.hidratar(buffer2);
	delete [] buffer;
}
	
void ArchBlockRRLV::saveByteMap(){
	std::string serializado = byteMap.serializar();
	archBlocks.grabarBloque(serializado.c_str(),0);
}
bool ArchBlockRRLV::insert(Bloque & bloque){
		unsigned int numBlk = byteMap.getBloque(bloque.size());
		if (numBlk != 0 ){
			byteMap.add(numBlk,bloque.size());
			saveByteMap();
			std::string serializado;
			bloque.serializar(serializado);
			while(serializado.size()!= byteMap.getTamBlock()){
			serializado.push_back(0);
			}
			archBlocks.grabarBloque(serializado.c_str(),numBlk);}
		else 
			return false;
		return true;
}
	/*insert(sobrescribe el bloque que se encuentre en numBlock)
	 */
	bool ArchBlockRRLV::insert(Bloque & bloque, unsigned numBlock){
		if (numBlock != 0 ){
			std::string serializado;
			bloque.serializar(serializado);
			while(serializado.size()!= byteMap.getTamBlock()){
			serializado.push_back(0);
			}
			archBlocks.grabarBloque(serializado.c_str(),numBlock);}
		else 
			return false;
		return true;
		
	}
	
	//Falta terminar esto
	/*Hay dos opciones
	 * 1)Del buffer cargar el registro
	 * 2)Que bloque tenga una primitiva para cargar los registros (me parece lo mas apropiado)
	 * 3)archBlock que tenga una primitiva que interactue con los buffers (no me parece bien 
	 * porque grabar bloque funcionar con char *
	 */
	Bloque ArchBlockRRLV::getBloque(unsigned short numBlock){
		unsigned short tamBlock = archBlocks.getTamBlock();
		char * buffer= new char[tamBlock];
		archBlocks.leerBloque(buffer,numBlock);
		unsigned pos=0;
		Bloque bloque;
		bool terminar = false;
		while (!terminar){
				if ((buffer[pos]) == '\n') terminar = true;
				else{
					Registro registro(archBlocks.getFormato());
					pos+=registro.hidratar(buffer+pos,tamBlock-pos);
					bloque.add(registro);}
		}
		delete [] buffer;
		return bloque;
	}

	std::vector <unsigned short> ArchBlockRRLV::getNumBloquesOcupados(){
		return byteMap.getBloquesOcupados();
	}