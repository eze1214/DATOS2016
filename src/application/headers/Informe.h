/*
 * Informe.h
 *
 *  Created on: 15/10/2015
 *      Author: cristian
 */

#ifndef INFORME_H_
#define INFORME_H_
#include <cstring>
#include "Comando.h"

enum QUESTION {
	LISTADO_VENTAS_X_VENDEDOR, AHORRO_ESP_X_COMPRESION
};

class Informe: public Comando {
private:
	QUESTION question;
	char* pathSalida;

public:
	Informe(QUESTION _question, const char* _pathSalida) :
			question(_question) {
		if (_pathSalida == NULL)
			pathSalida = NULL;
		else {
			pathSalida = new char[strlen(_pathSalida) + 1];
			strcpy(pathSalida, _pathSalida);
		}

	}

	virtual ~Informe() {
		delete[] pathSalida;
	}

	virtual void run();

};

#endif /* INFORME_H_ */
