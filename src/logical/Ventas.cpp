/*
 * Vendedores.cpp
 *
 *  Created on: 3 de oct. de 2015
 *      Author: ezequiel
 */

#include "./headers/Ventas.h"

Ventas::Ventas(unsigned int _codVendedor,unsigned int _codProducto,Fecha _fecha) :
	codVendedor(_codVendedor),codProducto(_codProducto),fecha(_fecha) {
	kilos = 0;
}
Ventas::Ventas(const Ventas& _ventas) :
	Registro(_ventas) {
	codVendedor = _ventas.codVendedor;
	codProducto = _ventas.codProducto;
	fecha = _ventas.fecha;
	kilos = _ventas.kilos;
}
Ventas::Ventas(){

}

const void* Ventas::getValor(unsigned indexAtributo) const
		throw (eRegistroElAtributoNoExiste) {
	switch (indexAtributo) {
	case COD_VENDEDOR:
		return &codVendedor;
	case COD_PRODUCTO:
		return &codProducto;
	case FECHAOP:
		return &fecha;
	case KILOS:
		return &kilos;
	default:
		throw eRegistroElAtributoNoExiste();
	}
}

void Ventas::setValor(unsigned indexAtributo, const void* valor)
		throw (eRegistroElAtributoNoExiste) {
	switch (indexAtributo) {
	case COD_VENDEDOR:
		codVendedor = *(unsigned int*) valor;
		break;
	case COD_PRODUCTO:
		codProducto = *(unsigned int*) valor;
		break;
	case FECHAOP:
			fecha = *(Fecha*) valor;
			break;
	case KILOS:
		kilos = *(float*) valor;
		break;
	default:
		throw eRegistroElAtributoNoExiste();

	}

}

TIPO_DATO Ventas::getTipo(unsigned indexAtributo) const
		throw (eRegistroElAtributoNoExiste) {
	switch (indexAtributo) {
	case COD_PRODUCTO:
	case COD_VENDEDOR:
		return UNSIGNED_INT;
	case KILOS:
		return FLOAT;
	case FECHAOP:
		return FECHA;
	default:
		throw eRegistroElAtributoNoExiste();

	}
}

