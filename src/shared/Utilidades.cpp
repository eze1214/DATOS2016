/*
 * Utilidades.cpp
 *
 *  Created on: 21/10/2015
 *      Author: cristian
 */

#include "./headers/Utilidades.h"

bool Utilidades::isDigit(const char& _c) {
	switch (_c) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return true;

	default:
		return false;

	}

}

unsigned char Utilidades::getDigit(const char& _c) {
	switch (_c) {
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	}

}

Fecha Utilidades::stringToFecha(const char* s) {
	Fecha f;
	unsigned i;

	if (strlen(s) < 17)
		return f;

	/******************************************DIA****************************************/
	if (isDigit(s[0]) && isDigit(s[1])) {
		f.setDia(getDigit(s[0]) * 10 + getDigit(s[1]));
		i = 2;
	} else if (isDigit(s[0])) {
		f.setDia(getDigit(s[0]));
		i = 1;
	} else
		return f;

	if (s[i] != '/')
		return f;
	else
		i++;

	/******************************************MES*****************************************/
	if (isDigit(s[i]) && isDigit(s[i + 1])) {
		f.setMes(getDigit(s[i]) * 10 + getDigit(s[i + 1]));
		i += 2;
	} else if (isDigit(s[i])) {
		f.setMes(getDigit(s[i]));
		i += 1;
	} else
		return f;

	if (s[i] != '/')
		return f;
	else
		i++;

	if ((strlen(s) - i) != 13)
		return f;

	/******************************************ANIO****************************************/
	if (isDigit(s[i]) && isDigit(s[i + 1]) && isDigit(s[i + 2])
			&& isDigit(s[i + 3])) {
		f.setAnio(
				getDigit(s[i]) * 1000 + getDigit(s[i + 1]) * 100
						+ getDigit(s[i + 2]) * 10 + getDigit(s[i + 3]));
		i += 4;
	} else
		return f;

	if (s[i] != ' ')
		return f;
	else
		i++;

	/****************************************HORA*******************************************/
	if (isDigit(s[i]) && isDigit(s[i + 1])) {
		f.setHora(getDigit(s[i]) * 10 + getDigit(s[i + 1]));
		i += 2;
	} else
		return f;

	if (s[i] != ':')
		return f;
	else
		i++;

	/***************************************MINUTO*****************************************/
	if (isDigit(s[i]) && isDigit(s[i + 1])) {
		f.setMinuto(getDigit(s[i]) * 10 + getDigit(s[i + 1]));
		i += 2;
	} else
		return f;

	if (s[i] != ':')
		return f;
	else
		i++;

	/*************************************SEGUNDO******************************************/
	if (isDigit(s[i]) && isDigit(s[i + 1]))
		f.setSegundo(getDigit(s[i]) * 10 + getDigit(s[i + 1]));

	return f;

}

