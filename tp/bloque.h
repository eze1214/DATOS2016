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
	void add(Registro & registro);
	
	/*Devuelve un string con la información empaquetada devolviendo la cantidad
	 * de bytes.
	 */
	unsigned serializar(std::string & buffer);
	unsigned size();
};

#endif // BLOQUE_H
