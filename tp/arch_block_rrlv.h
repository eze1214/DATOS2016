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
	Registro configuracion;//Va a guardar el tamaño del bloque y el formato
	void saveByteMap();
public:
	ArchBlockRRLV(std::string  nombre, unsigned short tamBlock,
							  std::string  formato);
	
	/*Inserta un bloque donde haya espacio
	 * 
	 */
	bool insert(Bloque & bloque);
	/*insert(sobrescribe el bloque que se encuentre en numBlock)
	 */
	bool insert(Bloque & bloque, unsigned numBlock);
	void del(unsigned numBlock);
	Bloque getBloque(unsigned numBlock);
};

#endif // ARCHBLOCKRRLV_H
