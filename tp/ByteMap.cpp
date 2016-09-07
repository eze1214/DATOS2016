/*
 * ByteMap.cpp
 *
 *  Created on: 05/09/2016
 *      Author: Ezequiel
 */

#include "./headers/ByteMap.h"
#include <cstring>
#include <iostream>
using namespace std;
void ByteMap::insert(unsigned _pos, const Gap& _g) {
	if (_pos == listGaps.size())
		listGaps.push_back(_g);
	else {
		unsigned last = listGaps.size() - 1;

		listGaps.push_back(listGaps[last]);

		for (unsigned i = last; i > _pos; i--)
			listGaps[i] = listGaps[i - 1];

		listGaps[_pos] = _g;
	}
}

bool ByteMap::existe(unsigned long _ref, unsigned& _pos) const {
	unsigned i;
	bool encontrado = false;

	for (i = 0; i < listGaps.size(); i++)
		if (listGaps[i].ref > _ref)
			break;
		else if (listGaps[i].ref == _ref) {
			encontrado = true;
			break;
		}

	_pos = i;
	return encontrado;
}

ByteMap::ByteMap(unsigned _tamanio, Configuracion _config) :
		config(_config) {
	Gap g;

	listGaps.clear();
	g.cantBytes = g.ref = 0;
	for (unsigned i = 0; i < _tamanio; listGaps.push_back(g), i++)
		;
}

string ByteMap::serializar() const {
	char* p;
	unsigned i = 0;
	string cadena("");
	unsigned listGapsIndex = 0;

	if (config == ARCH_RRLV_EN_BLOCKS)
		while (listGapsIndex < listGaps.size()) {
			if (i < listGaps[listGapsIndex].ref)
				cadena.append(2, 0xFF);
			else {
				p = (char*) &listGaps[listGapsIndex].cantBytes;
				if (big_endian())
					p += ((sizeof(unsigned)) - 2);

				cadena.push_back(p[0]);
				cadena.push_back(p[1]);
				listGapsIndex++;
			}

			i++;
		}
	else
		while (listGapsIndex < listGaps.size()) {
			p = (char*) &listGaps[listGapsIndex].ref;
			if (big_endian())
				p += (sizeof(unsigned long) - 4);

			cadena.push_back(p[0]);
			cadena.push_back(p[1]);
			cadena.push_back(p[2]);
			cadena.push_back(p[3]);

			p = (char*) &listGaps[listGapsIndex].cantBytes;
			if (big_endian())
				p += ((sizeof(unsigned)) - 2);

			cadena.push_back(p[0]);
			cadena.push_back(p[1]);
			listGapsIndex++;
		}

	return cadena;
}

void ByteMap::hidratar(const string& _cadGaps)
		throw (eByteMapCadenaNoRespetaTamanio) {
	char* p;
	unsigned i = 0;
	unsigned listGapsIndex = 0;

	/**Falta controlar el tamanio de la cadena según la config.**/

	if (config == ARCH_RRLV_EN_BLOCKS)
		while (listGapsIndex < listGaps.size())
			if (((int) _cadGaps[i] == -1) && ((int) _cadGaps[i + 1] == -1))
				i += 2;
			else {
				listGaps[listGapsIndex].ref = i / 2;

				p = (char*) &listGaps[listGapsIndex].cantBytes;
				if (big_endian())
					p += ((sizeof(unsigned)) - 2);

				p[0] = _cadGaps[i];
				p[1] = _cadGaps[++i];
				listGapsIndex++;
				i++;
			}
	else
		while (listGapsIndex < listGaps.size()) {
			p = (char*) &listGaps[listGapsIndex].ref;
			if (big_endian())
				p += (sizeof(unsigned long) - 4);

			p[0] = _cadGaps[i];
			p[1] = _cadGaps[++i];
			p[2] = _cadGaps[++i];
			p[3] = _cadGaps[++i];

			p = (char*) &listGaps[listGapsIndex].cantBytes;
			if (big_endian())
				p += ((sizeof(unsigned)) - 2);

			p[0] = _cadGaps[++i];
			p[1] = _cadGaps[++i];
			listGapsIndex++;
			i++;
		}
}

void ByteMap::addGap(unsigned long _ref, unsigned _cantBytes)
		throw (eByteMapBytesLibresConReferenciasMultiples) {
	Gap g;
	int pos;

	g.ref = _ref;
	g.cantBytes = _cantBytes;

	if (((pos = insertOrdenado(g)) < 0))
		throw eByteMapBytesLibresConReferenciasMultiples();

	if (config == ARCH_SEC_RRLV) {
		if ((unsigned) pos != (listGaps.size() - 1)) {
			if (listGaps[pos + 1].ref < (_ref + _cantBytes))
				throw eByteMapBytesLibresConReferenciasMultiples();
			else if (listGaps[pos + 1].ref == (_ref + _cantBytes)) {
				listGaps[pos].cantBytes += listGaps[pos + 1].cantBytes;
				listGaps.erase(listGaps.begin() + pos + 1);
			}
		}

		if (pos != 0) {
			if ((listGaps[pos - 1].ref + listGaps[pos - 1].cantBytes) > _ref)
				throw eByteMapBytesLibresConReferenciasMultiples();
			else if ((listGaps[pos - 1].ref + listGaps[pos - 1].cantBytes)
					== _ref) {
				listGaps[pos - 1].cantBytes += listGaps[pos].cantBytes;
				listGaps.erase(listGaps.begin() + pos);
			}
		}
	}
}

void ByteMap::upDateGap(unsigned long _ref, int _cantBytes)
		throw (eByteMapReferenciaInexistente, eByteMapCantBytesMalEspecificada) {
	unsigned pos;

	if (!existe(_ref, pos))
		throw eByteMapReferenciaInexistente();

	if ((int) listGaps[pos].cantBytes < _cantBytes)
		throw eByteMapCantBytesMalEspecificada();

	listGaps[pos].cantBytes -= _cantBytes;

	if (config == ARCH_SEC_RRLV) {
		if (listGaps[pos].cantBytes == 0)
			listGaps.erase(listGaps.begin() + pos);
		else
			listGaps[pos].ref += _cantBytes;
	}
}
long ByteMap::getCantBytes(unsigned long ref){
	for(unsigned i = 0; i < listGaps.size();i++)
		if (listGaps[i].ref == ref)
			return listGaps[i].cantBytes;
	return -1;
}
long ByteMap::getGap(unsigned _cantBytes) const {
	for (unsigned i = 0; i < listGaps.size(); i++)
		if (listGaps[i].cantBytes >= _cantBytes)
			return listGaps[i].ref;

	return -1;
}

/**unsigned ByteMap::getGap(unsigned long _ref) const
 throw (eByteMapReferenciaInexistente) {
 unsigned pos;
 if (!existe(_ref, pos))
 throw eByteMapReferenciaInexistente();

 return listGaps[pos].cantBytes;
 }**/

unsigned int ByteMap::serializar(char* buffer,unsigned int tamanio){
	unsigned int offset = 0;
	unsigned short int cantElementos = listGaps.size();
	unsigned short int cantBytes = 0;
	memcpy (buffer,&cantElementos,sizeof(cantElementos));
	offset  = offset + sizeof(cantElementos);

	for (unsigned i = 0; i < listGaps.size(); i++){
		cantBytes = listGaps[i].cantBytes;
		memcpy(buffer+offset,&cantBytes,sizeof(cantBytes));
		offset = offset + sizeof(cantBytes);
	}
	return offset;
}

void ByteMap::hidratar(char* buffer){
	unsigned int offset = 0;
	unsigned short int cantElementos;
	unsigned long ref = 0;
	unsigned short int cantBytes = 0;
	memcpy(&cantElementos,buffer,sizeof(cantElementos));
	offset = offset + sizeof(cantElementos);
	for (unsigned i = 0; i < cantElementos; i++){
		ref = i+1;
		memcpy(&cantBytes,buffer+offset,sizeof(cantBytes));
		offset = offset + sizeof(cantBytes);
		this->addGap(ref,cantBytes);
		}
}
