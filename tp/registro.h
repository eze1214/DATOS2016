#ifndef REGISTRO_H
#define REGISTRO_H
#include "parser_formato.h"
#include <vector>
#include <iostream>
struct Campo{
		std::string value;
		Formato formato;
		bool bloqueado;
};

/*Registro: crea un registro.
 * Se debe inicializar en el constructor colocando un string que indique el 
 * formato ejemplo: i1,i2,d
 * Los campos se enumeran del 0 al n, siendo 0 el primer campo y n el ultimo
 * Para serializar se debe obtener el tamaño con size() y externamente tener 
 * una estructura que permita almacenarlo.
 * Para hidratar se utiliza una estructura externa buffer definida por el usuario
 * que tenga el formato que se obtuvo con serializar y se especifica el 
 * tamaño en bytes.
 */
class Registro{
	private:
	std::vector<Campo> campos;
	//Guarda los formatos ya parseados.
	std::vector<Formato> formatos;
	std::vector<Formato>::iterator it_formatos;
	std::vector<Campo>::iterator it_campos;
	std::string formato;
	/*Graba en un campo detallado por la variable num, 
	 * desde el buffer pasado como parametro con el size definido
	 * 
	 */
	unsigned grabar(const char * buffer,unsigned size,unsigned num);

public:
	
	bool equals(Registro & registro);
	/*Se utiliza para bloquear campos que no serán persistidos
	 * 
	 */
	void bloquearCampo(const unsigned & numCampo);
	void desbloquearCampo(const unsigned & numCampo);
	void bloquearTodosCampos();
	/*Inicializa al registro 
	 * con un formato especificado. Se arma el vecto de formatos 
	 * pero sin valores deben ser insertados con writeCampo.
	 */
	Registro(const std::string & formato);

	/*Escribe un valor en el campo destino especificado por numCampo
	 *en el caso de sD debe contener al final el caracter \0. Devuelve
	 * la cantidad de bytes escritos.
	 */
	unsigned writeCampo(const char * value,unsigned size,unsigned numCampo);
	
	/*Devuelve una copia de un campo para que sea accedido desde afuera
	 * 
	 */
	Campo getCampo(unsigned numero) const;
	
	/*Serializar buffer: dstino size: tamaño del destino
	 * retorna la cantidad de bytes serializadod.
	 */
	unsigned serializar(char * buffer,unsigned size);
	
	unsigned int serializar(std::string & buffer);
	
	/*Hidratar: buffer: origen de datos, size: tamaño del origen de datos.
	 */
	unsigned hidratar(const char * buffer,unsigned size); 
	
	unsigned size();
	
	void print();
	
	friend std::ostream& operator << (std::ostream &o,const Registro &p);
	
	std::string getString() const;
	
	std::string getFormato();
	
	void suma(Registro & reg1,Registro & reg2);
};

#endif // REGISTRO_H
