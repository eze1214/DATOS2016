/*
 * Modificacion.h
 *
 *  Created on: 15/10/2015
 *      Author: cristian
 */

#ifndef MODIFICACION_H_
#define MODIFICACION_H_
#include "ABM.h"

using namespace std;

class Modificacion: public ABM {
public:
	Modificacion(ENTIDADES _entidad, const char* _pathEntrada) :
			ABM(_entidad, _pathEntrada) {
	}

	virtual ~Modificacion() {
	}

	virtual void run();

};

#endif /* MODIFICACION_H_ */
