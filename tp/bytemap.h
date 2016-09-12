#ifndef BYTEMAP_H
#define BYTEMAP_H

#include <vector>
#include <string>


/*Aclaración: La clase maneja numeros de bloque del 
 * sizeoOf de un char esto esto es de 0 a 255 en total 
 * 256 bytes. 
 * Internamente maneja valores entre 0 y 255 pero el 
 *usuario de la clase debe ingresar numeros entre 1 y 256
 *o su equivalente según el tamaño 1 a 1024 etc (internamente
 *0 a 1023) 
 */

class ByteMap{
private:
  /*Este vector guarda el espacio ocupado*/
  std::vector<unsigned char> bytes;
  
  // Va desde 1 hasta n
  unsigned sizeBloque;
  /*Convierte el tamaño en un rango desde 1 a 256
   * recibe un numero que debe arrancar el 1
   * la transformación la hace tomando como parámetro que el 
   * valor máximo de bloque puede tener que es especificado en el 
   * constructor
	 * Devuelve true siempre que haya exito.
	 * falsa cuando no hay exito, es decir que el tamaño ingresado excesa a 
	 * el tamaño del bloque
   */
  bool convertir(unsigned tam,unsigned char & );

public:
  
  /* getBloque: devuelve un bloque que tenga el espacio 
   * suficiente para guardar datos que tenga el tamaño
   * especificado por tam
   * Defvuelve 0 en caso de error
   */
  unsigned int getTamBlock(){ return sizeBloque;}
	unsigned getBloque(unsigned tam);
  
  /* Recibe la longitud del tamaño del bloque
   * debe ser un numero entre 1 y 256
   */
  ByteMap(unsigned sizeBloque);
  
  /*Devuelve un string que tiene encapsulado el 
   * mapa de bytes listo para ser guardado a disco
   */
  std::string serializar();
  
  /*Recibe un string que tiene encapsulado el mapa de bytes
   * el mismo debe tener el formato provisto por serializar*/
  
  void hidratar (std::string hidratar);
  
  /*Agrega bytes al bloque especificado
   *es decir que aumenta el espacio ocupado
   */
  void add(unsigned numeroBloque,unsigned tamBlk);
  
  /*Quita bytes del bloque espedcificado
   * es decir que disminuye el espacio ocupado
   */
  void del(unsigned numero,unsigned tamBlk);
};

#endif // BYTEMAP_H
