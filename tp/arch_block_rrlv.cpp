#include "arch_block_rrlv.h"
#include <string>
#define offset 32

ArchBlockRRLV::ArchBlockRRLV(std::string  nombre, unsigned short  tamBlock, std::string  formato):	archBlocks(nombre,tamBlock,formato),
											byteMap(tamBlock),
											configuracion(formato)
										{}

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
		char buffer[numBlock];
		archBlocks.leerBloque(buffer,numBlock);
		Bloque bloque;
	}
