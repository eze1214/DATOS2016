/*
 * Comando.h
 *
 *  Created on: 15/10/2015
 *      Author: cristian
 */

#ifndef COMANDO_H_
#define COMANDO_H_

using namespace std;

class Comando {
public:
	Comando() {
	}

	virtual ~Comando() {
	}

	virtual void run() = 0;

};

#endif /* COMANDO_H_ */
