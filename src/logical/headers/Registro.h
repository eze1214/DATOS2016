/*
 * Registro.h
 *
 *  Created on: 06/10/2015
 *      Author: cristian
 */

#ifndef REGISTRO_H_
#define REGISTRO_H_
#include <string.h>
#include <stdio.h>
#include <typeinfo>
#include "../../logical/headers/Fecha.h"
#include "../exceptions/eRegistroWrongNumberKeyFields.h"
#include "../exceptions/eRegistroElAtributoNoExiste.h"
#include "../exceptions/eRegistrosDeDistintasClases.h"
#include "../exceptions/eRegistroClaveSinComportamientoDefinido.h"

using namespace std;

enum TIPO_DATO {
	FECHA,
	STRING,
	BOOL,
	CHAR,
	SIGNED_CHAR,
	UNSIGNED_CHAR,
	SHORT_INT,
	UNSINED_SHORT_INT,
	INT,
	UNSIGNED_INT,
	LONG_INT,
	UNSIGNED_LONG_INT,
	LONG_LONG_INT,
	UNSIGNED_LONG_LONG_INT,
	FLOAT,
	DOBLE
};

/**Es una clase abstracta de la cual heredan todas aquellas clases que implementen
 * los registros de nuestra aplicacion, incluyendo los registros de indice.
 * Los campos clave deben situarse en primer orden, siendo el primero el de mayor jerarquia.
 *
 */

class Registro {
private:
	unsigned numberKeyFields;

public:
	Registro(unsigned _numberKeyfields = 1) :
			numberKeyFields(_numberKeyfields) {
	}

	Registro(const Registro& _registro) :
			numberKeyFields(_registro.numberKeyFields) {
	}

	virtual ~Registro() {
	}

	virtual Registro& clone() const = 0;

	Registro& operator=(const Registro& _registro)
			throw (eRegistrosDeDistintasClases);

	virtual unsigned getCantAtributos() const=0;

	/**
	 * Retorna un nro negativo si la clave de this es menor.
	 * Retorna un nro positivo si la clave de this es mayor.
	 * Retorna 0 si ambas claves son iguales.
	 */
	int keycmp(const Registro& registro) const
			throw (eRegistrosDeDistintasClases,
			eRegistroClaveSinComportamientoDefinido,
			eRegistroWrongNumberKeyFields);

	bool classcmp(const Registro& registro) const {
		return (typeid(*this) == typeid(registro));
	}

	virtual const void* getValor(unsigned indexAtributo) const
			throw (eRegistroElAtributoNoExiste)=0;

	virtual void setValor(unsigned indexAtributo, const void* valor)
			throw (eRegistroElAtributoNoExiste)=0;

	virtual TIPO_DATO getTipo(unsigned indexAtributo) const
			throw (eRegistroElAtributoNoExiste)=0;

};

#endif /* REGISTRO_H_ */
