#include "registro.h"
#include <cstring>
#include "parser_formato.h"
#include <iostream>
#include <sstream>

bool Registro::equals(Registro & registro)  {
	it_campos = campos.begin();
	bool equal =  true;
	for(unsigned i = 0; i < campos.size(); i++){
		std::cout<<campos[i].value<<" "<<registro.getCampo(i).value<<std::endl;
		if (campos[i].value != registro.getCampo(i).value)
			equal = false; 
	}
	return equal;
}

Registro::Registro(const std::string & formato):formato(formato){
		ParserFormato parser(formato);
		formatos = parser.getFormatos();
		it_formatos = formatos.begin();
		for(;it_formatos != formatos.end();++it_formatos){
				Campo campo;
				campo.formato = *it_formatos;
				campo.value = ""; //Inicializo con nada
				campo.bloqueado = false;
				campos.push_back(campo);
		}
}
	
	void Registro::bloquearCampo(const unsigned & numCampo){
		campos[numCampo].bloqueado = true;
	}
	
	void Registro::desbloquearCampo(const unsigned & numCampo){
		campos[numCampo].bloqueado = false;
	}
	
void Registro::bloquearTodosCampos(){
	for (unsigned i = 0; i<campos.size(); i++){
		campos[i].bloqueado = true;
	}
}

	
	unsigned Registro::writeCampo(const char * value,unsigned size,unsigned numCampo){
		unsigned len = 0;
		Campo campo = campos[numCampo];
		campo.value.clear();
		switch(campo.formato.tipo){
			case CADENA_FIJA:
				campo.formato.longitud = size;
				campo.value.insert(0,value,campos[numCampo].formato.longitud);
				break;
			case CADENA_VARIABLE:
				while(len < size){
				campo.value.push_back(*(value+len));
				len++;
				}
				if (*(value+len-1)!= '\0'){ 
					campo.value[len-1] = '0';
				}
				campo.formato.longitud = len;
			break;
			case ENTERO:
			case FECHA_CORTA:
			case FECHA_LARGA:
			campo.value.insert(0,value,campos[numCampo].formato.longitud);
			len = campos[numCampo].formato.longitud;
			break;
			default:
				std::cout<<"Formato desconodico"<<std::endl;
		}	
		campos[numCampo] = campo;
		return len;
	}
	
	Campo Registro::getCampo(unsigned numero) const{
			return campos[numero];
	}
	
	//Este aparentemente no se usa mas
 unsigned int Registro::serializar(char* buffer, unsigned int size){
 	it_campos = campos.begin();
 	unsigned pos = 0;
 	for(;it_campos!= campos.end();++it_campos){
		if(!(*it_campos).bloqueado){
			memcpy(buffer + pos, (*it_campos).value.c_str() ,(*it_campos).value.length());
			pos += (*it_campos).formato.longitud;}
 	}
 	return pos;
 }

unsigned int Registro::serializar(std::string & buffer){
	it_campos = campos.begin();
	buffer.clear();
	unsigned pos = 0;
	for(;it_campos!= campos.end();++it_campos){
		if(!(*it_campos).bloqueado){
			if ((*it_campos).formato.tipo == CADENA_FIJA){
				unsigned aux =((*it_campos).formato.longitud);
				char prefijo = aux-1;
				buffer.append(&prefijo,sizeof(char));//Le resto uno para poder aprovechar 256 bytes
				pos++;
			}
			buffer.append((*it_campos).value);
			pos += (*it_campos).formato.longitud;
		}
	}
	return pos;
}

unsigned Registro::grabar(const char * buffer,unsigned size,unsigned num){
	unsigned pos = 0;
		switch((campos[num]).formato.tipo){
			case ENTERO:
			case FECHA_CORTA:
			case FECHA_LARGA:
			this->writeCampo(buffer,campos[num].formato.longitud,num);
			pos += campos[num].formato.longitud;
			break;
			case CADENA_FIJA:{
				char prefijo=0;
				memcpy((char*)&prefijo, buffer,sizeof(char));
				//Se le sumo uno para avanzar uno en el buffer
				//y se le sumo uno en prefijo para obtener el verdadero valor son 256 pero va 
				//desde 0 a 255
				this->writeCampo(buffer+1,prefijo+1,num);}
				break;
			case CADENA_VARIABLE:{
			bool terminar = false;
			while(!terminar){
				pos++;
				if (*(buffer+pos)=='\0'){
					terminar = true; pos++;}
			}				
				this->writeCampo(buffer,pos,num);
			}break;
			default:
				std::cout<<"Error tipo de formato desconocido"<<std::endl;
				break;
		}
		return pos;
}

unsigned Registro::hidratar(const char* buffer, unsigned int size){
	unsigned numCampo = 0;
	unsigned pos = 0;
	it_campos = campos.begin();
	for(;it_campos != campos.end();++it_campos){
		pos += grabar(buffer+pos,size,numCampo);
		numCampo++;
	}
	return pos;
}
 
	
	unsigned Registro::size(){
			unsigned contador = 0;
			it_campos = campos.begin();
			for (; it_campos!= campos.end();++it_campos){
					if(!(*it_campos).bloqueado)
						contador+=(*it_campos).formato.longitud;
			}
			return contador;
	}
	
	
// Sobrecarga del operador << para la clase Pareja
std::ostream& operator << (std::ostream &o, const Registro &p){
		std::string final = p.getString();
		o << final;
    return o;
}

std::string Registro::getString() const{
	std::vector<Campo>::const_iterator it_campos_const = campos.cbegin();
	std::stringstream output;
	for (; it_campos_const!= campos.cend();++it_campos_const){
						switch((*it_campos_const).formato.tipo){
							case ENTERO:
								switch ((*it_campos_const).formato.longitud){
									case 1:{
										char variable;
										memcpy(&variable,(*it_campos_const).value.c_str(),sizeof(char));
										output<<variable;}
										break;
									case 2:{
										short variable;
										memcpy((char*)&variable,(*it_campos_const).value.c_str(),sizeof(short));
										output<<variable;}
										break;
									case 4:{
										int variable;
										memcpy((char*)&variable,(*it_campos_const).value.c_str(),sizeof(int));
										output<<variable;}
										break;
									case 8:{
										long long variable;
										memcpy((char*)&variable,(*it_campos_const).value.c_str(),sizeof(long long));
										output<<variable;}
										break;
									default: std::cout<<"Registro no imprimible"<<std::endl;
								}
								break;
							case CADENA_FIJA:
							case CADENA_VARIABLE:
							case FECHA_CORTA:
							case FECHA_LARGA:
								output<<(*it_campos_const).value;
							break;
							default:
								std::cout<<"Formato desconocido"<<std::endl;
						}
						output<<",";
			}
			output<<std::endl;
			std::string final = output.str();
			unsigned pos = final.find_last_of(",");
			final.erase(pos,1);
			return final;
}
void Registro::print(){
	it_campos = campos.begin();
	for (; it_campos!= campos.end();++it_campos){
						switch((*it_campos).formato.tipo){
							case ENTERO:
								switch ((*it_campos).formato.longitud){
									case 1:{
										char variable;
										memcpy(&variable,(*it_campos).value.c_str(),sizeof(char));
										std::cout<<"Value: "<<variable<<std::endl;}
										break;
									case 2:{
										short variable;
										memcpy((char*)&variable,(*it_campos).value.c_str(),sizeof(short));
										std::cout<<"Value: "<<variable<<std::endl;}
										break;
									case 4:{
										int variable;
										memcpy((char*)&variable,(*it_campos).value.c_str(),sizeof(int));
										std::cout<<"Value: "<<variable<<std::endl;}
										break;
									case 8:{
										long long variable;
										memcpy((char*)&variable,(*it_campos).value.c_str(),sizeof(long long));
										std::cout<<"Value: "<<variable<<std::endl;}
										break;
									default: std::cout<<"Registro no imprimible"<<std::endl;
								}
								break;
							case CADENA_FIJA:
							case CADENA_VARIABLE:
							case FECHA_CORTA:
							case FECHA_LARGA:
								std::cout<<"Value: "<<(*it_campos).value<<std::endl;
							break;
							default:
								std::cout<<"Formato desconocido"<<std::endl;
						}
			}
}

std::string Registro::getFormato(){
	std::string salida;
	salida.clear();
	
	std::stringstream buffer;
  std::string::const_iterator it = formato.begin();
	std::cout<<formato<<std::endl;
	std::vector<std::string> auxiliar;
	 for(;it != formato.end();it++){ 
    if ((*it) != ',')
      buffer<<*it;
    else{		
    	auxiliar.push_back(buffer.str());
		buffer.str("");
		buffer.clear();
    }
  }
  
  buffer.str("");
  for(unsigned i = 0;i < auxiliar.size(); i++){
			if (!campos[i].bloqueado){
					buffer<<auxiliar[i];
					buffer<<",";
			}
	}
	
	salida = buffer.str();
	//Borro la coma
	unsigned pos = salida.find_last_of(",");
	salida.erase(pos,1);
	return salida;
}

void Registro::suma(Registro& reg1, Registro& reg2){
	std::string serializado1;
	std::string serializado2;
	std::string serializado3;
	reg1.serializar(serializado1);
	reg2.serializar(serializado2);
	serializado3 = serializado1+serializado2;
	this->hidratar(serializado3.c_str(),serializado3.size());
}