/*
 * ABM.h
 *
 *  Created on: 15/10/2015
 *      Author: cristian
 */

#ifndef ABM_H_
#define ABM_H_
#include "Comando.h"
#include <cstring>

using namespace std;

enum ENTIDADES {
	VENTAS, PRODUCTOS, VENDEDORES, GRUPOS
};

class ABM: public Comando {
protected:
	ENTIDADES entidad;
	char* pathEntrada;

public:
	ABM(ENTIDADES _entidad, const char* _pathEntrada) :
			entidad(_entidad) {
		pathEntrada = new char[strlen(_pathEntrada) + 1];
		strcpy(pathEntrada, _pathEntrada);
	}

	virtual ~ABM() {
		delete[] pathEntrada;
	}

	virtual void run()=0;

};

#endif /* ABM_H_ */
