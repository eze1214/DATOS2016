#include "bytemap.h"
#include <cmath>
#include <iostream>
#define MAX_CHAR 255.

void ByteMap::setTamBlock(unsigned sizeBloque){
 this->sizeBloque = sizeBloque;
  for(unsigned i = 0; i<=sizeBloque; i++){
    bytes.push_back(0);
  }	
}
ByteMap::ByteMap(unsigned sizeBloque){
 setTamBlock(sizeBloque);
 coef = ceil(100 * MAX_CHAR / sizeBloque);
}

  std::string ByteMap::serializar(){
    std::string output;
    for(unsigned i = 1; i <= sizeBloque; i++){
      output.push_back(bytes[i]);
    }
    return output;
  }
  
  void ByteMap::hidratar (std::string buffer){
   for (unsigned i = 1; i <= sizeBloque; i++){
				bytes[i] = buffer.at(i-1);
   }
  }
  
void ByteMap::set(unsigned int numeroBloque, unsigned int ocupado){
	unsigned char tamFinal;
	convertir(ocupado,tamFinal);
  bytes[numeroBloque] = tamFinal;
}
  
  void ByteMap::add(unsigned numero,unsigned tam){
      unsigned char tamFinal;
			convertir(tam,tamFinal);
      bytes[numero] += tamFinal;
  }
  void ByteMap::del(unsigned numero,unsigned tam){
    unsigned char tamFinal;
		convertir(tam,tamFinal);
    bytes[numero] -= tamFinal; 
  }
  
  unsigned ByteMap::getBloque(unsigned tam){
    bool encontro = false;
    unsigned char tamFinal;
		if(convertir(tam,tamFinal)){
			unsigned i = 1;
			while( (i <= sizeBloque) && !encontro){
				unsigned char espacioLibre = MAX_CHAR - bytes[i];
				if (tamFinal <=	 espacioLibre){ 
					encontro = true;
				} else
					i++;
			}
			if (encontro) 
				return i;
			else
			return 0;}
  return 0;}
  
  bool ByteMap::convertir(unsigned tam, unsigned char & tamFinal){
     if (tam == sizeBloque) tamFinal = MAX_CHAR;
     else if (tam > sizeBloque) {
 			return false;
 		}else
 			tamFinal = ceil(tam * coef / 100);
	//	tamFinal = tam * (MAX_CHAR. / sizeBloque.)
		return true;
  }
  
std::vector< unsigned short > ByteMap::getBloquesOcupados(){
	std::vector<unsigned short> ocupados;
	for(unsigned i = 1; i<=sizeBloque; i++){
    if (bytes[i]!=0) ocupados.push_back(i);
  }	
  return ocupados;
}

//TODO testear
unsigned int ByteMap::getEspacioOcupado(unsigned int numBlk){
	unsigned espacioOcupado = (bytes[numBlk]*(sizeBloque /MAX_CHAR));
	return espacioOcupado;
}
