#include <gtest/gtest.h>
#include "../registro.h"
#include "../bloque.h"
#include <string>
#include <cstring>
#include "../bytemap.h"
#include <iostream>
#include "../condicion.h"

TEST(Registro, serializarEHidratar){
	Registro registro("sL");
	char mensaje[256]; 
	for (int i = 0; i< 256; i++)
		mensaje[i] = i;
	registro.writeCampo((char*)&mensaje,256,0);
	std::string buffer3;
	registro.serializar(buffer3);
	char buffer2[257];
	unsigned char prefijo = 255;
	memcpy(buffer2,(char*)&prefijo,sizeof(char));
	memcpy(buffer2+1,mensaje,sizeof(mensaje));
	Registro registro2("sL");
	registro.hidratar(buffer3.c_str(),buffer3.size());
	std::string buffer4;
	registro.serializar(buffer4);
	EXPECT_EQ(*buffer2,*buffer4.c_str());
}
TEST(Registro, RegistroLongitudFijaMaxima){
	Registro registro("sL");
	char mensaje[256]; 
	for (int i = 0; i< 256; i++)
		mensaje[i] = i;
	registro.writeCampo((char*)&mensaje,256,0);
	std::string buffer3;
	registro.serializar(buffer3);
	char buffer2[257];
	unsigned char prefijo = 255;
	memcpy(buffer2,(char*)&prefijo,sizeof(char));
	memcpy(buffer2+1,mensaje,sizeof(mensaje));
	EXPECT_EQ(*buffer2,*buffer3.c_str());
}
TEST(Registro, RegistroLongitudFija){
	Registro registro("sL");
	char mensaje[] = "Hola Soy Eze";
	registro.writeCampo((char*)&mensaje,12,0);
	std::string buffer3;
	registro.serializar(buffer3);
	char buffer2[13];
	unsigned char prefijo = 11;
	memcpy(buffer2,(char*)&prefijo,sizeof(char));
	memcpy(buffer2+1,mensaje,sizeof(mensaje)-1);
	EXPECT_EQ(*buffer2,*buffer3.c_str());
}
TEST(Registro, create) {
	Registro registro ("i1,i2,i4");
	char a = 5;
	short int b = 20;
	int c = 40;
	char buffer [7];
	memset(buffer,0,7);
	registro.writeCampo((char*)&a,sizeof(char),0);
	registro.writeCampo((char*)&b,sizeof(short int),1);
	registro.writeCampo((char*)&c,sizeof(int),2);
	registro.serializar(buffer,7);
	char buffer2[7];
	memset(buffer2,0,7);
	memcpy(buffer2,(char*)&a,sizeof(char));
	memcpy(buffer2+1,(char*)&b,sizeof(short));
	memcpy(buffer2+3,(char*)&c,sizeof(int));
	EXPECT_EQ(*buffer2,*buffer);
}

TEST(Registro, cadenaVariable){
 Registro registro("sD");
 char buffer[8] = "holanda";
 char buffer2[8];
 memset(buffer2,0,sizeof(buffer2));
 registro.writeCampo((char * )buffer,sizeof(buffer),0);
 registro.serializar(buffer2,sizeof(buffer2));
 EXPECT_EQ(*buffer2,*buffer);
}

TEST(Registro,variasVeces){
 Registro registro("sD");
 char buffer[8] = "holanda";
 char buffer2[8];
 memset(buffer2,0,sizeof(buffer2));
 registro.writeCampo((char * )buffer,sizeof(buffer),0);
 registro.serializar(buffer2,sizeof(buffer2));
 Registro registro2("sD");
 registro2.hidratar(buffer2,sizeof(buffer2));
 memset(buffer2,0,sizeof(buffer2));
 registro2.serializar(buffer2,sizeof(buffer2));
 EXPECT_EQ(*buffer2,*buffer);
}
TEST(Registro,size) {
  Registro registro ("i1,i2,i4");
  EXPECT_EQ(registro.size(),7);
}

TEST(Bloque,cantRegistro){
    Registro registro1("i1,i2,i4");
    Registro registro2("i1,i2,i4");
    Bloque bloque;
    bloque.add(registro1);
    bloque.add(registro2);
    EXPECT_EQ(bloque.cantRegistros(),2);
}

TEST(Bloque,size){
  Registro registro1("i1,i2,i4");
  Registro registro2("i1,i2,i4");
  char a = 5;
  short int b = 20;
  int c = 40;
  registro1.writeCampo(&a,sizeof(char),0);
  registro1.writeCampo((char*)&b,sizeof(short int),1);
  registro1.writeCampo((char*)&c,sizeof(int),2);
  registro2.writeCampo((char*)&a,sizeof(char),0);
  registro2.writeCampo((char*)&b,sizeof(short int),1);
  registro2.writeCampo((char*)&c,sizeof(int),2);
  Bloque bloque;
  bloque.add(registro1);
  bloque.add(registro2);
    
  EXPECT_EQ(bloque.size(),15);//Uno mas por el fin de bloque
}

TEST (Bloque,serializarNummer){
  Registro registro1("i1,i2,i4");
  Registro registro2("i1,i2,i4");
  char a = 5;
  short int b = 20;
  int c = 40;
  registro1.writeCampo(&a,sizeof(char),0);
  registro1.writeCampo((char*)&b,sizeof(short int),1);
  registro1.writeCampo((char*)&c,sizeof(int),2);
  registro2.writeCampo((char*)&a,sizeof(char),0);
  registro2.writeCampo((char*)&b,sizeof(short int),1);
  registro2.writeCampo((char*)&c,sizeof(int),2);
  Bloque bloque;
  bloque.add(registro1);
  bloque.add(registro2);
  std::string cadena;
  EXPECT_EQ(bloque.serializar(cadena),15);//Uno mas por el fin de bloque 
}

TEST (Bloque,del){
  Registro registro1("i1,i2,i4");
  Registro registro2("i1,i2,i4");
  char a = 5;
  short int b = 20;
  int c = 40;
  registro1.writeCampo(&a,sizeof(char),0);
  registro1.writeCampo((char*)&b,sizeof(short int),1);
  registro1.writeCampo((char*)&c,sizeof(int),2);
  registro2.writeCampo((char*)&a,sizeof(char),0);
  registro2.writeCampo((char*)&b,sizeof(short int),1);
  registro2.writeCampo((char*)&c,sizeof(int),2);
  Bloque bloque;
  bloque.add(registro1);
  bloque.add(registro2);
  bloque.del(0);
  EXPECT_EQ(bloque.cantRegistros(),1); 
}

TEST (Bloque, serializar){
  Registro registro1("i1,i2,i4");
  Registro registro2("i1,i2,i4");
  char buffer1[14];
  memset(buffer1,0,sizeof(buffer1));
  char a = 5;
  short int b = 20;
  int c = 40;
  registro1.writeCampo(&a,sizeof(char),0);
  registro1.writeCampo((char*)&b,sizeof(short int),1);
  registro1.writeCampo((char*)&c,sizeof(int),2);
  registro2.writeCampo((char*)&a,sizeof(char),0);
  registro2.writeCampo((char*)&b,sizeof(short int),1);
  registro2.writeCampo((char*)&c,sizeof(int),2);
  memcpy(buffer1,(char*)&a,sizeof(a));
  memcpy(buffer1+1,(char*)&b,sizeof(b));
  memcpy(buffer1+3,(char*)&c,sizeof(c));
  memcpy(buffer1+7,(char*)&a,sizeof(a));
  memcpy(buffer1+8,(char*)&b,sizeof(b));
  memcpy(buffer1+10,(char*)&c,sizeof(c));
  Bloque bloque;
  bloque.add(registro1);
  bloque.add(registro2);
  std::string cadena;
  bloque.serializar(cadena);
  
  EXPECT_EQ(*cadena.c_str(),*buffer1);
}

TEST(bytemap, EspacioBloque2){
	ByteMap bytemap(256);
	bytemap.add(1,254);
	EXPECT_EQ(bytemap.getBloque(254),2);
}

TEST(bytemap, espacioUnBloque){
    ByteMap bytemap(256);
    std::cout<<bytemap.getBloque(100)<<std::endl;
    EXPECT_EQ(bytemap.getBloque(100),1);
}

TEST(bytemap, masGrande){
 ByteMap bytemap(2048);
 EXPECT_EQ(bytemap.getBloque(1000),1);
}

TEST(bytemap,del){
	ByteMap bytemap(256);
	bytemap.add(1,254);
	bytemap.del(1,254);
	EXPECT_EQ(bytemap.getBloque(254),1);
}

TEST(bytemap,delJusto){
    ByteMap bytemap(256);
    bytemap.add(1,256);
    bytemap.del(1,256);
    EXPECT_EQ(bytemap.getBloque(256),1);
}

TEST(bytemap,addJusto){
   ByteMap bytemap(256);
   EXPECT_EQ(bytemap.getBloque(256),1);
}

TEST(bytemap,ultimoBloque){
   ByteMap bytemap(256);
   for (int i = 1;i<256;i++){
    bytemap.add(i,256);
  }
  EXPECT_EQ(bytemap.getBloque(256),256);
}

TEST(bytemap,sinEspacio){
   ByteMap bytemap(256);
   for(int i = 1 ; i<=256;i++)
    bytemap.add(i,200);
  EXPECT_EQ(bytemap.getBloque(200),0);
}

TEST(bytemap,serializarVacio){
  ByteMap bytemap(256);
  std::string serializado;
  serializado = bytemap.serializar();
  std::string comparar;
  for(int i = 1; i<=256;i++)
    comparar.push_back(0);
  EXPECT_EQ(comparar,serializado);
}

TEST(bytemap,serializarUnoLleno){
  ByteMap bytemap(256);
  std::string serializado;
  bytemap.add(1,256);
  serializado = bytemap.serializar();
  std::string comparar;
  unsigned char lleno = 255;
  comparar.push_back(lleno);
  for(int i = 2; i<=256;i++)
    comparar.push_back(0);
  EXPECT_EQ(comparar,serializado);
}

TEST(bytemap,serializarTodoLleno){
  ByteMap bytemap(256);
  std::string serializado;
  for ( int i = 1; i <=256; i++)
    bytemap.add(i,256);
  serializado = bytemap.serializar();
  std::string comparar;
  unsigned char lleno = 255;
  for(int i = 1; i<=256;i++)
    comparar.push_back(lleno);
  EXPECT_EQ(comparar,serializado);
}

TEST(bytemap,registroExcedeBloque){
		ByteMap bytemap(256);
		EXPECT_EQ(bytemap.getBloque(2000),0);
}

TEST(condicion,condicionVerdadera){
	Registro registro("i2");
	short a = 5;
	registro.writeCampo((char*)&a,sizeof(short),0);
	Condicion condicion;
	condicion.add(0,"i2",(char*)&a,sizeof(short));
	EXPECT_EQ(condicion.evaluar(registro),true);
}

TEST(condicion,condicionFalsa){
	Registro registro("i2");
	short a = 5;
	registro.writeCampo((char*)&a,sizeof(short),0);
	Condicion condicion;
	short b = 6;
	condicion.add(0,"i2",(char*)&b,sizeof(short));
	EXPECT_EQ(condicion.evaluar(registro),false);
}

TEST(condicion,condicionVerdaderaVariosCampos){
	Registro registro("i2,sD,i2");
	short a = 5;
	short b = 20;
	char cadena [] = "holanda";
	registro.writeCampo((char*)&a,sizeof(short),0);
	registro.writeCampo((char*)&cadena,sizeof(cadena),1);
	registro.writeCampo((char*)&b,sizeof(short),2);
	Condicion condicion;
	condicion.add(0,"i2",(char*)&a,sizeof(short));
	condicion.add(2,"i2",(char*)&b,sizeof(short));
	EXPECT_EQ(condicion.evaluar(registro),true);
}

TEST(Registro, longitudVariable){
	Registro registro("i2,sD,i2");
	short a = 5;
	char cadena [] = "holanda";
	short b =20;
	registro.writeCampo((char*)&a,sizeof(short),0);
	registro.writeCampo((char*)&cadena,sizeof(cadena),1);
	registro.writeCampo((char*)&b,sizeof(short),2);
	std::string serializado;
	registro.serializar(serializado);
	std::string buffer;
	buffer.insert(0,(char*)&a,sizeof(short));
	buffer.insert(2,cadena,8);
	buffer.insert(10,(char*)&b,2);
	EXPECT_EQ(*buffer.c_str(),*serializado.c_str());	
}

TEST(Registro, longitudFija){
	Registro registro("sL");
	char cadena [] = "holanda";
	registro.writeCampo((char*)&cadena,sizeof(cadena),0);
	std::string serializado;
	registro.serializar(serializado);
	std::string buffer;
	char a = 7;
	buffer.insert(0,(char*)&a,sizeof(char));
	buffer.insert(1,cadena,7);
	EXPECT_EQ(*buffer.c_str(),*serializado.c_str());
	
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}

