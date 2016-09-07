#include <gtest/gtest.h>
#include "../registro.h"
#include "../bloque.h"
#include <string>
#include <cstring>
#include "../headers/ByteMap.h"

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
    
  EXPECT_EQ(bloque.size(),14);
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
  EXPECT_EQ(bloque.serializar(cadena),14); 
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
int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}
