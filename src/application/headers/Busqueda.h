/*
 * Busqueda.h
 *
 *  Created on: 15/10/2015
 *      Author: cristian
 */

#ifndef BUSQUEDA_H_
#define BUSQUEDA_H_
#include "Comando.h"
#include <cstring>

using namespace std;

enum CRITERIOS {
	BUS_VENDEDOR_X_ID,
	BUS_VENDEDOR_X_NOMBRE,
	BUS_VENTA_X_COD_VENDEDOR,
	BUS_VENTA_X_COD_PRODUCTO,
	BUS_PRODUCTO_X_ID,
	BUS_PRODUCTO_X_NOMBRE,
	BUS_GRUPO_X_ID
};

class Busqueda: public Comando {
protected:
	CRITERIOS criterio;
	char* pathSalida;

public:
	Busqueda(CRITERIOS _criterio, const char* _pathSalida) :
			criterio(_criterio) {
		if (_pathSalida == NULL)
			pathSalida = NULL;
		else {
			pathSalida = new char[strlen(_pathSalida) + 1];
			strcpy(pathSalida, _pathSalida);
		}

	}

	virtual ~Busqueda() {
		delete[] pathSalida;
	}

	virtual void run() = 0;

};

#endif /* BUSQUEDA_H_ */
