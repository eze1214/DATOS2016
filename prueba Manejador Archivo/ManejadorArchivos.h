/*
 * manejadorArchivos.h
 *
 *  Created on: 27/6/2015
 *      Author: ezequiel
 */

#ifndef MANEJADORARCHIVOS_H_
#define MANEJADORARCHIVOS_H_
#include <string>
/*
 * Clase ManejadorArchivos
 * permite el manejo de archivos por bloques
 *
 * Modo de uso:
 * inicializar la clase con el constructor pasando como parámetro el nombre del archivo
 * y el tamaño de bloque a utilizar.
 * Si el archivo no existe lo crea.
 *
 *Aclaraciones: la clase internamente utiliza un bytemap que esta en el bloque 0
 *				El usuario no debe acceder al mismo, los bloques con datos se cuentan desde el
 *				1 hasta n.
 *
 * */
using namespace std;
class ManejadorArchivos {
private:
	char * mapaByte;
	string nombreArchivo;
	int cantidadDeBloques;
	int tamanioBloque;
	int obtenerCantidadBloquesTotales();
	bool existeArchivo(string nombreArchivo);
	void leerMapaByte();
	void crearArchivo(string nombreArchivo);
public:
	ManejadorArchivos(string,int,string);
	ManejadorArchivos(string,int);
	virtual ~ManejadorArchivos();
	bool existeBloque(int numeroBloque);
	void leerBloque(char* destino,int numeroBloque);
	int getCantidadBloques();
	char* getDatosBloque();
	void grabarBloque(char *bloque);
	void grabarBloque(char *bloque,unsigned int numeroDeBloque);
};
#endif /* MANEJADORARCHIVOS_H_ */
