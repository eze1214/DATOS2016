/*
 * Vendedores.h
 *
 *  Created on: 3 de oct. de 2015
 *      Author: ezequiel
 */

#ifndef VENDEDORES_H_
#define VENDEDORES_H_
#include "Registro.h"
#include <string>
#include "Fecha.h"

using namespace std;

enum ATRIB_VENDEDORES {
	ID_VENDEDOR,
	NOM_VENDEDOR,
	FECHA_ALTA,
	NIF,
	FECHA_NAC,
	DIRECCION,
	POBLACION,
	COD_POSTAL,
	TELEFONO,
	EST_CIVIL
};

class Vendedores: public Registro {
private:
	unsigned int idVendedor;
	char nomVendedor[50];
	Fecha fechaAlta;
	char nif[10];
	Fecha fechaNac;
	char direccion[100];
	char poblacion[50];
	unsigned int codPostal;
	unsigned long telefono;
	char estCivil[20];

	virtual unsigned getCantAtributos() const {
		return 10;
	}

	virtual const void* getValor(unsigned indexAtributo) const
			throw (eRegistroElAtributoNoExiste);

	virtual void setValor(unsigned indexAtributo, const void* valor)
			throw (eRegistroElAtributoNoExiste);

	virtual TIPO_DATO getTipo(unsigned indexAtributo) const
			throw (eRegistroElAtributoNoExiste);

public:
	Vendedores(unsigned int _idVendedor);

	Vendedores(const Vendedores& _vendedor); /**Constructor de copia**/

	virtual ~Vendedores() {
	}

	virtual Registro& clone() const {
		return *(new Vendedores(*this));
	}

	unsigned int getIdVendedor() const {
		return idVendedor;
	}

	const char* getNomVendedor() const {
		return nomVendedor;
	}

	void setNomVendedor(const char* _nomVendedor) {
		strcpy(nomVendedor, _nomVendedor);
	}

	const Fecha& getFechaAlta() const {
		return fechaAlta;
	}

	void setFechaAlta(const Fecha& _fechaAlta) {
		fechaAlta = _fechaAlta;
	}

	const char* getNif() const {
		return nif;
	}

	void setNif(const char* _nif) {
		strcpy(nif, _nif);
	}

	const Fecha& getFechaNac() const {
		return fechaNac;
	}

	void setFechaNac(const Fecha& _fechaNac) {
		fechaNac = _fechaNac;
	}

	const char* getDireccion() const {
		return direccion;
	}

	void setDireccion(const char* _direccion) {
		strcpy(direccion, _direccion);
	}

	const char* getPoblacion() const {
		return poblacion;
	}

	void setPoblacion(const char* _poblacion) {
		strcpy(poblacion, _poblacion);
	}

	unsigned int getCodPostal() const {
		return codPostal;
	}

	void setCodPostal(unsigned int _codPostal) {
		codPostal = _codPostal;
	}

	unsigned long getTelefono() const {
		return telefono;
	}

	void setTelefono(unsigned long _telefono) {
		telefono = _telefono;
	}

	const char* getEstCivil() const {
		return estCivil;
	}

	void setEstCivil(const char* _estCivil) {
		strcpy(estCivil, _estCivil);
	}

};

#endif /* SRC_LOGICAL_VENDEDORES_H_ */
