#include "bytemap.h"
#include <cmath>
#include <iostream>
#define MAX_CHAR 255.
ByteMap::ByteMap(unsigned sizeBloque){
  this->sizeBloque = sizeBloque;
  for(unsigned i = 0; i<=sizeBloque; i++){
    bytes.push_back(0);
  }
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
				if (tamFinal <= espacioLibre){ 
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
    unsigned char devolver;
    if (tam == sizeBloque) devolver = sizeBloque -1;
    else if (tam > sizeBloque) {
			return false;
		}else
			devolver = floor(tam * MAX_CHAR / (sizeBloque-1));
    tamFinal = devolver;
		return true;
  }