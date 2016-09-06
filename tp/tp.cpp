#include <iostream>
#include "registro.h"
#include <vector>
#include <cstdlib>
#include <cstring>
int main(int argc, char * argv[]){
 Registro registro("i1,i2,i4,i8,sD"); 
 char cadena[8] = "holanda";
 char a = 5;
 short int b = 2;
 int c = 10;
 long long int d = 20;
 std::cout<<registro.writeCampo((char*)&a,sizeof(char),0);
 std::cout<<registro.writeCampo((char*)&b,sizeof(short int),1);
 std::cout<<registro.writeCampo((char*)&c,sizeof(int),2);
 std::cout<<registro.writeCampo((char*)&d,sizeof(long long int),3);
 
 std::cout<<registro.writeCampo(cadena,sizeof(cadena),4);
 
 char buffer [512];
 memset(buffer,0,512);
 registro.serializar(buffer,512);
 Registro registro2("i1,i2,i4,i8,sD");
 registro2.hidratar(buffer,512);
 char buffer2[512];
 memset(buffer2,0,512);
 registro2.serializar(buffer2,512);
	std::cout<<"Longitud "<<registro.size();
 return 0;
}