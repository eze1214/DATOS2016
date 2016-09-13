#ifndef CONDICION_H
#define CONDICION_H
#include "registro.h"
#include <vector>
/*La condicion está compuesta por conjunto de la siguiente estructura
 * nroCampo
 * Registro: (Este registro está formado por un solo campo).
 */


class  Evaluador{
friend class Condicion;
private:
		unsigned nroCampo;
		Registro registro;
public:
		Evaluador(unsigned nroCampo, std::string formato):
			nroCampo(nroCampo),registro(formato){}
	};
	
class Condicion{
private:
	std::vector <Evaluador> condiciones;
	
public:
	void add(unsigned nroCampo,std::string formato, char* value, unsigned int size);
	bool evaluar(Registro & registro);
};

#endif // CONDICION_H
