/*
 * ArmadorComandos.h
 *
 *  Created on: 25/10/2015
 *      Author: ezequiel
 */

#ifndef SRC_APPLICATION_HEADERS_ARMADORCOMANDOS_H_
#define SRC_APPLICATION_HEADERS_ARMADORCOMANDOS_H_
#include "Alta.h"
class ArmadorComandos{
private:
	ENTIDADES archivo;
	void obtenerTipoComando(char *,char*);
	void obtenerArchivo(char*);
	Comando * comando;
public:
	ArmadorComandos(char*,char*,char*);
	~ArmadorComandos();
	Comando * getComando();
	void destroyComando();//LiberaLaMemoria
};



#endif /* SRC_APPLICATION_HEADERS_ARMADORCOMANDOS_H_ */
