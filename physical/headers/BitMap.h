/*
 * BitMap.h
 *
 *  Created on: 29/09/2014
 *      Author: cristian
 */

#ifndef BITMAP_H_
#define BITMAP_H_
#include <string>
#include "../exceptions/eBitMapCadenaNoRespetaTamanio.h"
#include "../exceptions/eBitMapPosFueraRango.h"

using namespace std;

const static unsigned char BIT0_ON = 0x80;
const static unsigned char BIT1_ON = 0x40;
const static unsigned char BIT2_ON = 0x20;
const static unsigned char BIT3_ON = 0x10;
const static unsigned char BIT4_ON = 0x08;
const static unsigned char BIT5_ON = 0x04;
const static unsigned char BIT6_ON = 0x02;
const static unsigned char BIT7_ON = 0x01;

class BitMap {
private:
	string bits;
	unsigned tamanio;

	void on(unsigned char& _c, unsigned char _nroBit);
	void off(unsigned char& _c, unsigned char _nroBit);
	unsigned char estado(unsigned char _c, unsigned char _nroBit) const;

public:
	BitMap(unsigned _tamanio = 0);

	virtual ~BitMap() {
	}

	unsigned getTamanio() const {
		return tamanio;
	}

	string serializar() const {
		return bits;
	}

	void serializar(char* data);

	void hidratar(char * data);

	void hidratar(const string& _cadBits) throw (eBitMapCadenaNoRespetaTamanio);

	void switchBit(unsigned _pos) throw (eBitMapPosFueraRango);

	void appendBit(); /**Por default en estado 1.**/

	unsigned char getBit(unsigned _pos) const throw (eBitMapPosFueraRango);

	int getGap() const; /**Devuelve -1 si no tiene éxito.**/

};

#endif /* BITMAP_H_ */
