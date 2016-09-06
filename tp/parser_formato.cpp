#include "parser_formato.h"
#include <sstream>
#include <iostream>

Formato ParserFormato::buildFormato(const std::stringstream &  buffer){
  Formato formato;
  if(buffer.str() == "i1"){
    formato.tipo = ENTERO;
    formato.longitud = 1;
  } else if (buffer.str() == "i2"){
    formato.tipo = ENTERO;
    formato.longitud = 2;
  } else if (buffer.str() == "i4"){
    formato.tipo = ENTERO;
    formato.longitud = 4;
	} else if (buffer.str() == "i8"){
		formato.tipo = ENTERO;
    formato.longitud = 8;
  } else if (buffer.str() == "sL"){
    formato.tipo = CADENA_FIJA;
    formato.longitud = SIZE_CADENA_CORTA;
  } else if (buffer.str() == "sD"){
    formato.tipo = CADENA_VARIABLE;
    formato.longitud = 0; //Pongo 0 ya que no tiene un tamaño especificado 
  } else if (buffer.str() == "d"){
    formato.tipo = FECHA_CORTA;
    formato.longitud = SIZE_FECHA_CORTA;
  } else if (buffer.str() == "dt"){
    formato.tipo = FECHA_LARGA;
    formato.longitud = SIZE_FECHA_LARGA;
  } else 
		std::cout<<"Formato invalido"<<std::endl;
  return formato;
}

ParserFormato::ParserFormato(const std::string & entrada){
  std::stringstream buffer;
  std::string::const_iterator it = entrada.begin();
  
  for(;it != entrada.end();it++){ 
    if ((*it) != ',')
      buffer<<*it;
    else{
      Formato formato;
      formato = buildFormato(buffer);
      formatos.push_back(formato);
      buffer.str("");
    }
  }
  if (buffer.str() != ""){
      Formato formato;
      formato = buildFormato(buffer);
      formatos.push_back(formato);
  }
}

std::vector<Formato> ParserFormato::getFormatos() const{
  return this->formatos;
}