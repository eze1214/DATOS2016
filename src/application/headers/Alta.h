/*
 * Alta.h
 *
 *  Created on: 15/10/2015
 *      Author: cristian
 */

#ifndef ALTA_H_
#define ALTA_H_
#include "ABM.h"

using namespace std;

class Alta: public ABM {
public:
	Alta(ENTIDADES _entidad, const char* _pathEntrada) :
			ABM(_entidad, _pathEntrada) {
	}

	virtual ~Alta() {
	}

	virtual void run();

};

#endif /* ALTA_H_ */
