/*
 * Parser.h
 *
 *  Created on: 09/10/2015
 *      Author: cristian
 */

#ifndef PARSER_H_
#define PARSER_H_
#include <cstring>
#include "../../logical/headers/Registro.h"
#include "../exceptions/eParserTipoDeDatoDesconocido.h"
#include "../../logical/headers/Fecha.h"

using namespace std;

class Parser {
private:
	static unsigned tamanio(TIPO_DATO) throw (eParserTipoDeDatoDesconocido);

	static bool big_endian() {
		int entero = 1;
		char* p = (char*) &entero;
		return p[0] == 0x00;
	}

public:
	Parser() {
	}

	virtual ~Parser() {
	}

	/**
	 * Retorna la cantidad de caracteres empleados en la serialización.
	 */
	static unsigned serializar(const Registro& registro, char* buffer)
			throw (eParserTipoDeDatoDesconocido);

	static void hidratar(Registro& registro, const char* buffer)
			throw (eParserTipoDeDatoDesconocido);

};

#endif /* PARSER_H_ */
