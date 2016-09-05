/*
 * Parser.cpp
 *
 *  Created on: 09/10/2015
 *      Author: cristian
 */

#include "./headers/Parser.h"

unsigned Parser::tamanio(TIPO_DATO tipoDato)
		throw (eParserTipoDeDatoDesconocido) {
	switch (tipoDato) {
	case BOOL:
		return sizeof(bool);
	case CHAR:
		return sizeof(char);
	case SIGNED_CHAR:
		return sizeof(signed char);
	case UNSIGNED_CHAR:
		return sizeof(unsigned char);
	case SHORT_INT:
		return sizeof(short int);
	case UNSINED_SHORT_INT:
		return sizeof(unsigned short int);
	case INT:
		return sizeof(int);
	case UNSIGNED_INT:
		return sizeof(unsigned int);
	case LONG_INT:
		return sizeof(long int);
	case UNSIGNED_LONG_INT:
		return sizeof(unsigned long int);
	case LONG_LONG_INT:
		return sizeof(long long int);
	case UNSIGNED_LONG_LONG_INT:
		return sizeof(unsigned long long int);
	case FLOAT:
		return sizeof(float);
	case DOBLE:
		return sizeof(double);

	default:
		throw eParserTipoDeDatoDesconocido();

	}

}

unsigned Parser::serializar(const Registro& registro, char* buffer)
		throw (eParserTipoDeDatoDesconocido) {
	char cadFecha[7];
	char dia, mes, hora, min, seg;
	int anio;
	TIPO_DATO tipoDato;
	const void* atribValue = NULL;
	unsigned atribTamanio = 0;
	unsigned cantCaracteres = 0;

	for (unsigned atribIndex = 0; atribIndex < registro.getCantAtributos();
			atribIndex++) {
		atribValue = registro.getValor(atribIndex);
		tipoDato = registro.getTipo(atribIndex);

		if (tipoDato == STRING)
			atribTamanio = strlen((char*) atribValue) + 1;
		else if (tipoDato == FECHA) {
			anio = ((Fecha*) atribValue)->getAnio();
			mes = ((Fecha*) atribValue)->getMes();
			dia = ((Fecha*) atribValue)->getDia();
			hora = ((Fecha*) atribValue)->getHora();
			min = ((Fecha*) atribValue)->getMinuto();
			seg = ((Fecha*) atribValue)->getSegundo();

			if (big_endian())
				memcpy(cadFecha, &anio + sizeof(anio) - 2, 2);
			else
				memcpy(cadFecha, &anio, 2);

			memcpy(cadFecha + 2, &mes, 1);
			memcpy(cadFecha + 3, &dia, 1);
			memcpy(cadFecha + 4, &hora, 1);
			memcpy(cadFecha + 5, &min, 1);
			memcpy(cadFecha + 6, &seg, 1);

			atribValue = cadFecha;
			atribTamanio = 7;

		} else
			try {
				atribTamanio = tamanio(tipoDato);
			} catch (eParserTipoDeDatoDesconocido&) {
				throw eParserTipoDeDatoDesconocido();
			}

		memcpy(buffer, atribValue, atribTamanio);
		buffer += atribTamanio;
		cantCaracteres += atribTamanio;

	}

	return cantCaracteres;

}

void Parser::hidratar(Registro& registro, const char* buffer)
		throw (eParserTipoDeDatoDesconocido) {
	Fecha f;
	unsigned char dia, mes, hora, min, seg;
	unsigned int anio = 0;
	TIPO_DATO tipoDato;
	unsigned atribTamanio = 0;
	char* atribValue = NULL;

	for (unsigned atribIndex = 0; atribIndex < registro.getCantAtributos();
			atribIndex++) {
		tipoDato = registro.getTipo(atribIndex);

		if (tipoDato == STRING)
			atribTamanio = strlen(buffer) + 1;
		else if (tipoDato == FECHA)
			atribTamanio = 7;
		else
			try {
				atribTamanio = tamanio(tipoDato);
			} catch (eParserTipoDeDatoDesconocido&) {
				throw eParserTipoDeDatoDesconocido();
			}

		atribValue = new char[atribTamanio];
		memcpy(atribValue, buffer, atribTamanio);

		if (tipoDato != FECHA)
			registro.setValor(atribIndex, atribValue);
		else {

			if (big_endian())
				memcpy(&anio + sizeof(anio) - 2, atribValue, 2);
			else
				memcpy(&anio, atribValue, 2);

			memcpy(&mes, atribValue + 2, 1);
			memcpy(&dia, atribValue + 3, 1);
			memcpy(&hora, atribValue + 4, 1);
			memcpy(&min, atribValue + 5, 1);
			memcpy(&seg, atribValue + 6, 1);

			f.setAnio(anio);
			f.setMes(mes);
			f.setDia(dia);
			f.setHora(hora);
			f.setMinuto(min);
			f.setSegundo(seg);

			registro.setValor(atribIndex, &f);

		}

		delete[] atribValue;
		buffer += atribTamanio;

	}

}

