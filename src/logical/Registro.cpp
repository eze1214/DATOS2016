/*
 * Registro.cpp
 *
 *  Created on: 07/10/2015
 *      Author: cristian
 */

#include "./headers/Registro.h"

int Registro::keycmp(const Registro& registro) const
		throw (eRegistrosDeDistintasClases,
		eRegistroClaveSinComportamientoDefinido, eRegistroWrongNumberKeyFields) {
	if (!classcmp(registro))
		throw eRegistrosDeDistintasClases();

	if (numberKeyFields == 0 || numberKeyFields > getCantAtributos())
		throw eRegistroWrongNumberKeyFields();

	int res;
	unsigned int i = 0;
	unsigned int key1, key2;
	do
		switch (getTipo(i)) {
		case STRING:
			res = (strcmp((char*) getValor(i), (char*) registro.getValor(i)));
			break;
		case FECHA:
			res = (((Fecha*) getValor(i))->compare(
					*(Fecha*) registro.getValor(i)));
			break;
		case UNSIGNED_INT: {
			key1 = *(unsigned int*) getValor(i);
			key2 = *(unsigned int*) registro.getValor(i);
			if (key1 == key2)
				res = 0;
			else if (key1 < key2)
				res = -1;
			else
				res = 1;

		}
			break;

		default:
			throw eRegistroClaveSinComportamientoDefinido();

		}

	while ((res == 0) && (++i != numberKeyFields));

	return res;

}

Registro& Registro::operator=(const Registro& _registro)
		throw (eRegistrosDeDistintasClases) {
	const void* ptr = NULL;

	if (!classcmp(_registro))
		throw eRegistrosDeDistintasClases();

	if (this != &_registro)
		for (unsigned i = 0; i < getCantAtributos(); i++)
			if ((ptr = _registro.getValor(i)))
				setValor(i, ptr);

	return *this;

}

