/*
 * ByteMap.h
 *
 *  Created on: 29/09/2014
 *      Author: cristian
 */

#ifndef BYTEMAP_H_
#define BYTEMAP_H_
#include <vector>
#include <string>
#include "../exceptions/eByteMapCadenaNoRespetaTamanio.h"
#include "../exceptions/eByteMapCantBytesMalEspecificada.h"
#include "../exceptions/eByteMapReferenciaInexistente.h"
#include "../exceptions/eByteMapBytesLibresConReferenciasMultiples.h"

using namespace std;

enum Configuracion {
	ARCH_RRLV_EN_BLOCKS, ARCH_SEC_RRLV
};

struct Gap {
	unsigned long ref; /**Representa un nro de block ó un offset según sea la config.**/
	unsigned cantBytes;/**Representa la cant de bytes libres en la locación.**/
};

class ByteMap {
private:
	Configuracion config;
	vector<Gap> listGaps;

	bool big_endian() const {
		int entero = 1;
		char* p = (char*) &entero;
		return p[0] == 0x00;
	}

	void insert(unsigned _pos, const Gap& _g);
	bool existe(unsigned long _ref, unsigned& _pos) const;
	int insertOrdenado(const Gap& _g) {
		unsigned pos;
		if (existe(_g.ref, pos))
			return -1;
		else {
			insert(pos, _g);
			return pos;
		}
	}

public:
	ByteMap(unsigned _tamanio = 0, Configuracion _config = ARCH_RRLV_EN_BLOCKS);

	virtual ~ByteMap() {

	}

	unsigned getTamanio() const {
		return listGaps.size();
	}

	string serializar() const;

	unsigned int serializar(char* buffer,unsigned int tamanio);

	void hidratar(const string& _cadGaps) throw (eByteMapCadenaNoRespetaTamanio);

	void hidratar(char*);

	void addGap(unsigned long _ref, unsigned _cantBytes)
			throw (eByteMapBytesLibresConReferenciasMultiples);

	/*
	 * _cantBytes es la cantidad de bytes escritos o borrados en el archivo.
	 * _cantBytes debe ser positivo cuando se trate de bytes escritos.
	 * _cantBytes debe ser negativo cuando se trate de bytes borrados.
	 */
	void upDateGap(unsigned long _ref, int _cantBytes)
			throw (eByteMapReferenciaInexistente,
			eByteMapCantBytesMalEspecificada);

	long getCantBytes(unsigned long ref);
	long getGap(unsigned _cantBytes) const; /**Devuelve -1 si no tiene éxito.**/

	/**unsigned getGap(unsigned long _ref) const
	 throw (eByteMapReferenciaInexistente);**/
};

#endif /* BYTEMAP_H_ */
