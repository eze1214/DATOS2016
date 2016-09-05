/*
 * Fecha.h
 *
 *  Created on: 18/10/2015
 *      Author: cristian
 */

#ifndef FECHA_H_
#define FECHA_H_
#include "../exceptions/eFechaInvalida.h"
#include <iostream>

using namespace std;

class Fecha {
private:
	unsigned char dia;
	unsigned char mes;
	unsigned int anio;
	unsigned char hora;
	unsigned char minuto;
	unsigned char segundo;

public:
	Fecha() {
		dia = mes = anio = hora = minuto = segundo = 0;
	}

	Fecha(unsigned char dia,unsigned char mes,unsigned int anio,
			unsigned char hora,unsigned char minuto,unsigned char segundo){
		this->dia = dia;
		this->mes  = mes;
		this->anio = anio;
		this->hora = hora;
		this->minuto = minuto;
		this->segundo = segundo;
	}
	virtual ~Fecha() {
	}

	void imprimir(){
		if ((int)dia <10) cout<<"0";
		cout<<(int)dia<<"/";
		if ((int)mes <10) cout<<"0";
		cout<<(int)mes<<"/";
		if ((int)anio <10) cout<<"0";
		cout<<(int)anio<<" ";
		if ((int)hora <10) cout<<"0";
		cout<<(int)hora<<":";
		if ((int)minuto <10) cout<<"0";
		cout<<(int)minuto<<":";
		if ((int)segundo <10) cout<<"0";
		cout<<(int)segundo<<endl;
	}
	bool isValid() const;

	bool operator<(const Fecha& _f) const throw (eFechaInvalida);
	bool operator==(const Fecha& _f) const throw (eFechaInvalida);

	int compare(const Fecha& _f) const throw (eFechaInvalida);

	void set(unsigned char dia,unsigned char mes,unsigned int anio,
			unsigned char hora,unsigned char minuto,unsigned char segundo){
		this->dia = dia;
		this->mes  = mes;
		this->anio = anio;
		this->hora = hora;
		this->minuto = minuto;
		this->segundo = segundo;
	}
	unsigned int getAnio() const {
		return anio;
	}

	void setAnio(unsigned int anio) {
		this->anio = anio;
	}

	unsigned char getDia() const {
		return dia;
	}

	void setDia(unsigned char dia) {
		this->dia = dia;
	}

	unsigned char getHora() const {
		return hora;
	}

	void setHora(unsigned char hora) {
		this->hora = hora;
	}

	unsigned char getMes() const {
		return mes;
	}

	void setMes(unsigned char mes) {
		this->mes = mes;
	}

	unsigned char getMinuto() const {
		return minuto;
	}

	void setMinuto(unsigned char minuto) {
		this->minuto = minuto;
	}

	unsigned char getSegundo() const {
		return segundo;
	}

	void setSegundo(unsigned char segundo) {
		this->segundo = segundo;
	}

};

#endif /* FECHA_H_ */
