/*
 * BitMap.cpp
 *
 *  Created on: 29/09/2014
 *      Author: cristian
 */

#include "./headers/BitMap.h"
#include <cstring>
using namespace std;
void BitMap::on(unsigned char& _c, unsigned char _nroBit) {
	switch (_nroBit) {
	case 0:
		_c = _c | BIT0_ON;
		break;
	case 1:
		_c = _c | BIT1_ON;
		break;
	case 2:
		_c = _c | BIT2_ON;
		break;
	case 3:
		_c = _c | BIT3_ON;
		break;
	case 4:
		_c = _c | BIT4_ON;
		break;
	case 5:
		_c = _c | BIT5_ON;
		break;
	case 6:
		_c = _c | BIT6_ON;
		break;
	case 7:
		_c = _c | BIT7_ON;
		break;
	}
}

void BitMap::off(unsigned char& _c, unsigned char _nroBit) {
	switch (_nroBit) {
	case 0:
		_c = _c & ~BIT0_ON;
		break;
	case 1:
		_c = _c & ~BIT1_ON;
		break;
	case 2:
		_c = _c & ~BIT2_ON;
		break;
	case 3:
		_c = _c & ~BIT3_ON;
		break;
	case 4:
		_c = _c & ~BIT4_ON;
		break;
	case 5:
		_c = _c & ~BIT5_ON;
		break;
	case 6:
		_c = _c & ~BIT6_ON;
		break;
	case 7:
		_c = _c & ~BIT7_ON;
		break;
	}
}

unsigned char BitMap::estado(unsigned char _c, unsigned char _nroBit) const {
	unsigned char res;
	switch (_nroBit) {
	case 0:
		res = _c & BIT0_ON;
		break;
	case 1:
		res = _c & BIT1_ON;
		break;
	case 2:
		res = _c & BIT2_ON;
		break;
	case 3:
		res = _c & BIT3_ON;
		break;
	case 4:
		res = _c & BIT4_ON;
		break;
	case 5:
		res = _c & BIT5_ON;
		break;
	case 6:
		res = _c & BIT6_ON;
		break;
	case 7:
		res = _c & BIT7_ON;
		break;
	}

	return (res == 0 ? 0 : 1);

}

BitMap::BitMap(unsigned _tamanio) :
		tamanio(_tamanio) {
	bits.erase();
	int cociente = tamanio / 8;
	int resto = tamanio % 8;
	int cantBytes = (resto == 0 ? cociente : cociente + 1);
	for (int i = 0; i < cantBytes; bits.push_back(0x00), i++)
		;

}

void BitMap::serializar(char * data){
	unsigned offset = 0;
	unsigned short length = this->getTamanio();
	char aux;
	memcpy(data,&length,sizeof(length));
	offset = offset + sizeof(length);
	for(unsigned i = 0; i<bits.length();i++){
		aux = bits[i];
		memcpy(data+offset,&aux,sizeof(char));
		offset++;
	}
}
void BitMap::hidratar(char *data){
	char aux;
	unsigned short length;
	unsigned offset = 0;
	string stringAuxiliar;
	memcpy(&length,data,sizeof(length));
	offset = offset + sizeof(length);

	bits.erase();
	int cociente = length / 8;
	int resto = length % 8;
	int cantBytes = (resto == 0 ? cociente : cociente + 1);
	this->tamanio = length;
	for (int i = 0; i < cantBytes; bits.push_back(0x00), i++);

	for(int i = 0;i<cantBytes;i++){
		memcpy(&aux,data+offset,sizeof(char));
		offset = offset + sizeof(char);
		bits[i]=aux;
	}
}
void BitMap::hidratar(const string& _cadBits)
		throw (eBitMapCadenaNoRespetaTamanio) {
	if (_cadBits.length() != bits.length())
		throw eBitMapCadenaNoRespetaTamanio();
	for (unsigned i = 0; i < bits.length(); i++)
		bits[i] = _cadBits[i];

}

void BitMap::switchBit(unsigned _pos) throw (eBitMapPosFueraRango) {
	if (_pos >= tamanio)
		throw eBitMapPosFueraRango();

	unsigned posByte = _pos / 8;
	unsigned char posBit = _pos % 8;
	unsigned char c = bits[posByte];

	if (estado(c, posBit) == 0)
		on(c, posBit);
	else
		off(c, posBit);

	bits[posByte] = c;
}

void BitMap::appendBit() {
	unsigned char resto = tamanio % 8;

	if (resto == 0)
		bits.push_back(BIT0_ON);
	else {
		unsigned char c = bits[bits.length() - 1]; //Accedo al último byte.
		on(c, resto); //El resto es la posición del bit.
		bits[bits.length() - 1] = c;
	}

	tamanio++;
}

unsigned char BitMap::getBit(unsigned _pos) const throw (eBitMapPosFueraRango) {
	if (_pos >= tamanio)
		throw eBitMapPosFueraRango();

	return estado(bits[_pos / 8], _pos % 8);
}

int BitMap::getGap() const {
	for (unsigned i = 0; i < tamanio; i++)
		if (getBit(i) == 0)
			return i;

	return -1;
}

