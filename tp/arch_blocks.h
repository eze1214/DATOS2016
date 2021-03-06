/*
 * ArchBlocks.h
 *
 *  Created on: 2/8/2015
 *      Author: Dufau Ezequiel
 */

#ifndef MANEJADORARCHIVOS_H_
#define MANEJADORARCHIVOS_H_
#include <string>
/*
 * Clase ArchBlocks
 * Permite el manejo de archivos por bloques
 *
 * Modo de uso:
 * inicializar la clase con el constructor pasando como parámetro el nombre del archivo
 * y el tamaño de bloque a utilizar.
 * Si el archivo no existe lo crea.
 *
 * Aclaraciones: la clase internamente utiliza un bytemap que esta en el bloque 0
 *				El usuario no debe acceder al mismo, los bloques con datos se cuentan desde el
 *				1 hasta n.
 *
 * */
using namespace std;
class ArchBlocks {
private:
	string nombreArchivo;
	string formato;
	unsigned cantidadDeBloques;
	unsigned short tamanioBloque;
	unsigned obtenerCantidadBloquesTotales();
	bool existeArchivo(string nombreArchivo);
	void crearArchivo(string nombreArchivo,std::string configuracion);
	char unsigned offset; //Me indica el offset que tiene el archivo dado por el sector destinado a guardar
												//la configuracion (tamño mapa de bytes y formato de registro)
	void readHeader();
	void saveHeader();
public:
	void grabarFormato(std::string & formato);
	void leerFormato(std::string & formato);
	
	ArchBlocks(std::string nombreArchivo);
	ArchBlocks(string filename ,unsigned short tamBlock ,string formato);
	
	ArchBlocks(string,int);
	virtual ~ArchBlocks();
	
	bool existeBloque(int numeroBloque);
	void leerBloque(char* destino,int numeroBloque);
	unsigned getCantidadBloques();
	char * getDatosBloque();
	void grabarBloque(char *bloque);
	void grabarBloque(const char *bloque,unsigned int numeroDeBloque);
	unsigned short getTamBlock();
	std::string getFormato();
};
#endif /* MANEJADORARCHIVOS_H_ */
