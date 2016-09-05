/*
 * Fecha.cpp
 *
 *  Created on: 18/10/2015
 *      Author: cristian
 */

#include "./headers/Fecha.h"

bool Fecha::isValid() const {
	if (dia == 0)
		return false;

	bool bisiesto = false;
	if ((anio % 4 == 0) && ((anio % 100 != 0) || (anio % 400 == 0)))
		bisiesto = true;

	switch (mes) {
	case 1:
		return dia <= 31;
	case 2:
		return (dia <= 28 || ((dia == 29) && bisiesto));
	case 3:
		return dia <= 31;
	case 4:
		return dia <= 30;
	case 5:
		return dia <= 31;
	case 6:
		return dia <= 30;
	case 7:
		return dia <= 31;
	case 8:
		return dia <= 31;
	case 9:
		return dia <= 30;
	case 10:
		return dia <= 31;
	case 11:
		return dia <= 30;
	case 12:
		return dia <= 31;

	default:
		return false;

	}

}

bool Fecha::operator<(const Fecha& _f) const throw (eFechaInvalida) {
	if (!isValid() || !_f.isValid())
		throw eFechaInvalida();

	if (anio < _f.anio)
		return true;
	else if (anio > _f.anio)
		return false;
	else if (mes < _f.mes)
		return true;
	else if (mes > _f.mes)
		return false;
	else if (dia < _f.dia)
		return true;
	else if (dia > _f.dia)
		return false;
	else if (hora < _f.hora)
		return true;
	else if (hora > _f.hora)
		return false;
	else if (minuto < _f.minuto)
		return true;
	else if (minuto > _f.minuto)
		return false;
	else if (segundo < _f.segundo)
		return true;
	else
		return false;

}

bool Fecha::operator==(const Fecha& _f) const throw (eFechaInvalida) {
	if (!isValid() || !_f.isValid())
		throw eFechaInvalida();

	if ((anio == _f.anio) && (mes == _f.mes) && (dia == _f.dia)
			&& (hora == _f.hora) && (minuto == _f.minuto)
			&& (segundo == _f.segundo))
		return true;
	else
		return false;

}

int Fecha::compare(const Fecha& _f) const throw (eFechaInvalida) {
	try {
		if (*this < _f)
			return -1;
		else if (*this == _f)
			return 0;
		else
			return 1;

	} catch (eFechaInvalida&) {
		throw eFechaInvalida();
	}

}
