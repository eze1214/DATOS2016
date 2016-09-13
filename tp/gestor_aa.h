#ifndef GESTORAA_H
#define GESTORAA_H

class GestorAA{
	enum TIPO {
		ARCHBLOCK,ARCHRRLV
	};
	TIPO tipoDeGestor;
private:
	
public:

GestorAA(std::string filename);
GestorAA(std::string formato);
import(std::string csv);

};

#endif // GESTORAA_H
