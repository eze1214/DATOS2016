#ifndef ARCHBLOCKRRLV_H
#define ARCHBLOCKRRLV_H
#include "bytemap.h"
#include "registro.h"
class ArchBlockRRLV{
private:
	ByteMap byteMap;
	Registro configuracion;//Va a guardar el tamañoi del bloque y el formato
public:
	ArchBlockRRLV(std::string nombre, unsigned tamBlock);
	
	/*Inserta un bloque donde haya espacio
	 * 
	 */
	insert(std::string bloque);
	/*insert(sobrescribe el bloque que se encuentre en numBlock)
	 */
	insert(std::string bloque, unsigned numBlock);
	del(unsigned numBlock);
	
};

#endif // ARCHBLOCKRRLV_H
