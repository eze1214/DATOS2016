/*
 * BusqSecuencial.h
 *
 *  Created on: 15/10/2015
 *      Author: cristian
 */

#ifndef BUSQSECUENCIAL_H_
#define BUSQSECUENCIAL_H_
#include "Busqueda.h"

using namespace std;

class BusqSecuencial: public Busqueda {
public:
	BusqSecuencial(CRITERIOS _criterio, const char* _pathSalida) :
			Busqueda(_criterio, _pathSalida) {
	}

	virtual ~BusqSecuencial() {
	}

	virtual void run();

};

#endif /* BUSQSECUENCIAL_H_ */
