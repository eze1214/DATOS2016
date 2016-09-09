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
      unsigned char tamFinal = convertir(tam);
      bytes[numero] += tamFinal;
  }
  void ByteMap::del(unsigned numero,unsigned tam){
    unsigned char tamFinal = convertir(tam);
    bytes[numero] -= tamFinal; 
  }
  
  unsigned ByteMap::getBloque(unsigned tam){
    bool encontro = false;
    unsigned char tamFinal = convertir(tam);
    unsigned i = 1;
    while( (i <= sizeBloque) && !encontro){
      unsigned char espacioLibre = MAX_CHAR - bytes[i];
      if (tamFinal <= espacioLibre){ 
	encontro = true;
      } else
	i++;
    }
    if (encontro) return i;
    else
    return 0;
  }
  
  unsigned char ByteMap::convertir(unsigned tam){
    unsigned char devolver;
    if (tam >= sizeBloque) devolver = sizeBloque -1;
    else
    devolver = floor(tam * MAX_CHAR / (sizeBloque-1));
    return devolver; 
  }