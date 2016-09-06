#ifndef BLOQUE_H
#define BLOQUE_H
#include "registro.h"
#include <vector>

/*Clase que representa un bloque de archivos
 *no chequea el tamaño ya que el gestor determina si el bloque es apto o no 
 *para ser guardado.
 *Este bloque tiene el tamaño de la suma de sus registros.
 */
class Bloque{
private:
	std::vector<Registro> registros;
	std::vector<Registro>::iterator it;
public:
	
	/*delete: Elimina un registro segun el numeroRegistro que es el numero de inserción 
	 * segun el orden que fue ingresado devuelve false si no existe;
	 */
	bool del(const unsigned & numeroRegistro);
	void edit(const Registro & registro, unsigned numeroRegistro); 
	void add(const Registro & registro);
	
	/*Es responsabilidad de quien utiliza la clase colocar un numero de registro 
	 * valido. Se puede obtener la cantidad de registros con cantRegistro
	 * 
	 */
	Registro getRegistro(unsigned numeroRegistro);
	/*Devuelve un string con la información empaquetada devolviendo la cantidad
	 * de bytes.
	 */
	unsigned serializar(std::string & buffer);
	unsigned size();
	
	unsigned cantRegistros();
};

#endif // BLOQUE_H
