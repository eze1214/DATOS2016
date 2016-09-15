#ifndef ARCHBLOCKRRLV_H
#define ARCHBLOCKRRLV_H
#include "bytemap.h"
#include "registro.h"
#include "arch_blocks.h"
#include "bloque.h"
/*ArchBlockRRLV los registros de longitud variable van desde el bloque 1 hasta 
 * n. Siendo el bloque 0 utilizado por el bytemap
 * Internamente utiliza un offset donde se especifica el tamaño de bloque
 * y el formato del registros
 * 2 Bytes para el tamaño del bloque
 * 30 Bytes para la información de la estructura del registro
 */
class ArchBlockRRLV{
private:
	ArchBlocks archBlocks;
	ByteMap byteMap;
	void saveByteMap();
public:
	//Constructor para abrir un archivo
	ArchBlockRRLV(std::string nombre);
	//Constructor para crear un archivo
	ArchBlockRRLV(std::string  nombre, unsigned short tamBlock,
							  std::string  formato);
	
	/*Obtiene un vector con los numeros de los bloques ocupados
	 * 
	 */
		std::vector <unsigned short> getNumBloquesOcupados();
	/*Inserta un bloque donde haya espacio
	 * 
	 */
	bool insert(Bloque & bloque);
	/*insert(sobrescribe el bloque que se encuentre en numBlock)
	 */
	bool insert(Bloque & bloque, unsigned numBlock);
	
	void insert(Registro & registro);
	void del(unsigned numBlock);
	Bloque getBloque(unsigned short numBlock);
	unsigned short getTamBloque();
	std::string getFormato();
};

#endif // ARCHBLOCKRRLV_H
