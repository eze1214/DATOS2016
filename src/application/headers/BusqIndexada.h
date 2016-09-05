/*
 * BusqIndexada.h
 *
 *  Created on: 15/10/2015
 *      Author: cristian
 */

#ifndef BUSQINDEXADA_H_
#define BUSQINDEXADA_H_
#include "Busqueda.h"

using namespace std;

class BusqIndexada: public Busqueda {
public:
	BusqIndexada(CRITERIOS _criterio, const char* _pathSalida) :
			Busqueda(_criterio, _pathSalida) {
	}

	virtual ~BusqIndexada() {
	}

	virtual void run();

};

#endif /* BUSQINDEXADA_H_ */
