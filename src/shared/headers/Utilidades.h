/*
 * Utilidades.h
 *
 *  Created on: 21/10/2015
 *      Author: cristian
 */

#ifndef UTILIDADES_H_
#define UTILIDADES_H_
#include <cstring>
#include "../../logical/headers/Fecha.h"

using namespace std;

class Utilidades {
public:
	Utilidades() {
	}

	virtual ~Utilidades() {
	}

	static bool big_endian() {
		int entero = 1;
		char* p = (char*) &entero;
		return p[0] == 0x00;
	}

	static bool isDigit(const char& _c);
	static unsigned char getDigit(const char& _c);
	static Fecha stringToFecha(const char* _s);

};

#endif /* UTILIDADES_H_ */
