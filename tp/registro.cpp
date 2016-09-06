#include "registro.h"
#include <cstring>
#include "parser_formato.h"
#include <iostream>
Registro::Registro(const std::string & formato){
		ParserFormato parser(formato);
		formatos = parser.getFormatos();
		it_formatos = formatos.begin();
		for(;it_formatos != formatos.end();++it_formatos){
				Campo campo;
				campo.formato = *it_formatos;
				campo.value = ""; //Inicializo con nada
				campos.push_back(campo);
		}
}
	
	unsigned Registro::writeCampo(char * value,unsigned size,unsigned numCampo){
		unsigned len = 0;
		Campo campo = campos[numCampo];
		if (campo.formato.tipo != CADENA_VARIABLE){
				campo.value.insert(0,value,campos[numCampo].formato.longitud);
				len = campos[numCampo].formato.longitud;
		}
		else{
			while(len < size){
				campo.value.push_back(*(value+len));
				len++;
			}
			if (*(value+len-1)!= '\0'){ 
				campo.value[len-1] = '0';
			}
			campo.formato.longitud = len;
		}
		campos[numCampo] = campo;
		return len;
	}
	
	Campo Registro::getCampo(unsigned numero) const{
			return campos[numero];
	}
	
unsigned int Registro::serializar(char* buffer, unsigned int size){
	it_campos = campos.begin();
	unsigned pos = 0;
	for(;it_campos!= campos.end();++it_campos){
		memcpy(buffer + pos, (*it_campos).value.c_str() ,(*it_campos).value.length());
		pos += (*it_campos).formato.longitud;
	}
	return pos;
}

unsigned Registro::grabar(char * buffer,unsigned size,unsigned num){
	unsigned pos = 0;
		switch((campos[num]).formato.tipo){
			case (ENTERO):
			case (CADENA_FIJA):
			case (FECHA_CORTA):
			case (FECHA_LARGA):
			this->writeCampo(buffer,campos[num].formato.longitud,num);
			pos += campos[num].formato.longitud;
			break;
			case (CADENA_VARIABLE):{
			bool terminar = false;
			while(!terminar){
				pos++;
				if (*(buffer+pos)=='\0'){
					terminar = true; pos++;}
			}				
				this->writeCampo(buffer,pos,num);
			break;}
			default:
				std::cout<<"Error tipo de formato desconocido"<<std::endl;
		}
		return pos;
}

void Registro::hidratar(char* buffer, unsigned int size){
	unsigned numCampo = 0;
	unsigned pos = 0;
	it_campos = campos.begin();
	for(;it_campos != campos.end();++it_campos){
		pos += grabar(buffer+pos,size,numCampo);
		numCampo++;
	}
}
 
	
	unsigned Registro::size(){
			return campos.size();
	}