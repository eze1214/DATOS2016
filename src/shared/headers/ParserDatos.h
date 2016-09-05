/*
 * ParserDatos.h
 *
 *  Created on: 25/10/2015
 *      Author: ezequiel
 */

#ifndef SRC_SHARED_HEADERS_PARSERDATOS_H_
#define SRC_SHARED_HEADERS_PARSERDATOS_H_
#include <string>
#include <iostream>
using namespace std;
class ParserDatos{
private:
	string buffer ;
public:
	ParserDatos(string);
	bool getDato(string &);
	~ParserDatos();
};



#endif /* SRC_SHARED_HEADERS_PARSERDATOS_H_ */
