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
	COD_VENDEDOR,
	COD_PRODUCTO,
	FECHAOP,
	KILOS,
};

class Ventas: public Registro {
private:
	unsigned int codVendedor;
	unsigned int codProducto;
	Fecha fecha;
	float kilos;

	virtual unsigned getCantAtributos() const {
		return 4;
	}

	virtual const void* getValor(unsigned indexAtributo) const
			throw (eRegistroElAtributoNoExiste);

	virtual void setValor(unsigned indexAtributo, const void* valor)
			throw (eRegistroElAtributoNoExiste);

	virtual TIPO_DATO getTipo(unsigned indexAtributo) const
			throw (eRegistroElAtributoNoExiste);

public:
	Ventas();
	Ventas(unsigned int,unsigned int, Fecha);

	Ventas(const Ventas& ); /**Constructor de copia**/

	virtual ~Ventas() {
	}

	virtual Registro& clone() const {
		return *(new Ventas(*this));
	}

	unsigned int getCodVendedor() const {
		return codVendedor;
	}

	unsigned int getCodProducto() const {
		return codProducto;
	}

	const Fecha& getFecha() const {
			return fecha;
	}

	float getKilos() const {
		return kilos;
	}
	void setCodVendedor(unsigned int _codVendedor) {
			codVendedor = _codVendedor;
	}

	void setCodProducto(unsigned int _codProducto) {
				codProducto = _codProducto;
	}

	void setFecha(const Fecha& _fecha) {
			this->fecha = _fecha;
		}
	void setKilos(float _kilos) {
				kilos = _kilos;
			}

};

#endif /* SRC_LOGICAL_VENDEDORES_H_ */
