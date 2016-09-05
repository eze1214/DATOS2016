/*
 * Baja.h
 *
 *  Created on: 15/10/2015
 *      Author: cristian
 */

#ifndef BAJA_H_
#define BAJA_H_
#include "ABM.h"

using namespace std;

class Baja: public ABM {
public:
	Baja(ENTIDADES _entidad, const char* _pathEntrada) :
			ABM(_entidad, _pathEntrada) {
	}

	virtual ~Baja() {
	}

	virtual void run();

};

#endif /* BAJA_H_ */
