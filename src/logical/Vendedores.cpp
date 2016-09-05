/*
 * Vendedores.cpp
 *
 *  Created on: 3 de oct. de 2015
 *      Author: ezequiel
 */

#include "./headers/Vendedores.h"

Vendedores::Vendedores(unsigned int _idVendedor) :
		idVendedor(_idVendedor) {
	telefono = codPostal = 0;
	nomVendedor[0] = nif[0] = direccion[0] = poblacion[0] = estCivil[0] = '\0';

}

Vendedores::Vendedores(const Vendedores& _vendedor) :
		Registro(_vendedor) {
	idVendedor = _vendedor.idVendedor;
	telefono = _vendedor.telefono;
	codPostal = _vendedor.codPostal;
	fechaAlta = _vendedor.fechaAlta;
	fechaNac = _vendedor.fechaNac;

	strcpy(nomVendedor, _vendedor.nomVendedor);
	strcpy(nif, _vendedor.nif);
	strcpy(direccion, _vendedor.direccion);
	strcpy(poblacion, _vendedor.poblacion);
	strcpy(estCivil, _vendedor.estCivil);

}

const void* Vendedores::getValor(unsigned indexAtributo) const
		throw (eRegistroElAtributoNoExiste) {
	switch (indexAtributo) {
	case ID_VENDEDOR:
		return &idVendedor;
	case NOM_VENDEDOR:
		return nomVendedor;
	case FECHA_ALTA:
		return &fechaAlta;
	case NIF:
		return nif;
	case FECHA_NAC:
		return &fechaNac;
	case DIRECCION:
		return direccion;
	case POBLACION:
		return poblacion;
	case COD_POSTAL:
		return &codPostal;
	case TELEFONO:
		return &telefono;
	case EST_CIVIL:
		return estCivil;

	default:
		throw eRegistroElAtributoNoExiste();

	}

}

void Vendedores::setValor(unsigned indexAtributo, const void* valor)
		throw (eRegistroElAtributoNoExiste) {
	switch (indexAtributo) {
	case ID_VENDEDOR:
		idVendedor = *(unsigned int*) valor;
		break;
	case NOM_VENDEDOR:
		strcpy(nomVendedor, (char*) valor);
		break;
	case FECHA_ALTA:
		fechaAlta = *(Fecha*) valor;
		break;
	case NIF:
		strcpy(nif, (char*) valor);
		break;
	case FECHA_NAC:
		fechaNac = *(Fecha*) valor;
		break;
	case DIRECCION:
		strcpy(direccion, (char*) valor);
		break;
	case POBLACION:
		strcpy(poblacion, (char*) valor);
		break;
	case COD_POSTAL:
		codPostal = *(unsigned int*) valor;
		break;
	case TELEFONO:
		telefono = *(unsigned long int*) valor;
		break;
	case EST_CIVIL:
		strcpy(estCivil, (char*) valor);
		break;

	default:
		throw eRegistroElAtributoNoExiste();

	}

}

TIPO_DATO Vendedores::getTipo(unsigned indexAtributo) const
		throw (eRegistroElAtributoNoExiste) {
	switch (indexAtributo) {
	case ID_VENDEDOR:
	case COD_POSTAL:
		return UNSIGNED_INT;
	case TELEFONO:
		return UNSIGNED_LONG_INT;
	case FECHA_ALTA:
	case FECHA_NAC:
		return FECHA;
	case NOM_VENDEDOR:
	case NIF:
	case DIRECCION:
	case POBLACION:
	case EST_CIVIL:
		return STRING;

	default:
		throw eRegistroElAtributoNoExiste();

	}

}

