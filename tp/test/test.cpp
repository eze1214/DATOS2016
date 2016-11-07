#include <gtest/gtest.h>
#include "../registro.h"
#include "../bloque.h"
#include <string>
#include <cstring>
#include "../bytemap.h"
#include <iostream>
#include "../condicion.h"
#include "../archrrlv.h"

TEST(Campo,getCampo){
	ArchRRLV arch("prueba.bin","i1,i2,i4");
	char a = 5;
	short int b = 10;
	int c = 20;
	Registro registro("i1,i2,i4");
	registro.writeCampo((char*)&a,sizeof(a),0);
	registro.writeCampo((char*)&b,sizeof(b),1);
	registro.writeCampo((char*)&c,sizeof(c),2);
	Campo campo;
	campo = registro.getCampo(0);
	char A; campo.get(A);
	campo = registro.getCampo(1);
	short int B; campo.get(B);
	campo = registro.getCampo(2);
	int C; campo.get(C);
	EXPECT_EQ(A,5);
	EXPECT_EQ(B,10);
	EXPECT_EQ(C,20);
}
TEST(ARCHRRLV,newFileAndRead){
	ArchRRLV arch("prueba.bin2","i1,i2,i4");
	arch.close();
	ArchRRLV arch2("prueba.bin2");
	std::string formato = arch2.getFormato();
	EXPECT_EQ(formato,"i4,i1,i2,i4");
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

TEST(Registro, notEqualBorde){
	Registro registro1("i1,i1");
	Registro registro2("i1,i1");
	char a = 5;
	char b = 6;
	char c = 5;
	char d = 20;
	registro1.writeCampo((char*)&a,sizeof(char),0);
	registro1.writeCampo((char*)&b,sizeof(char),1);

	registro2.writeCampo((char*)&c,sizeof(char),0);
	registro2.writeCampo((char*)&d,sizeof(char),1);

	EXPECT_EQ(false,registro1.equals(registro2));
}

TEST(Registro, notEqual){
	Registro registro1("i1,i1");
	Registro registro2("i1,i1");
	char a = 5;
	char b = 6;
	char c = 20;
	char d = 20;
	registro1.writeCampo((char*)&a,sizeof(char),0);
	registro1.writeCampo((char*)&b,sizeof(char),1);

	registro2.writeCampo((char*)&c,sizeof(char),0);
	registro2.writeCampo((char*)&d,sizeof(char),1);

	EXPECT_EQ(false,registro1.equals(registro2));
}

TEST(Registro, Equal){
	Registro registro1("i1,i1");
	Registro registro2("i1,i1");
	char a = 5;
	char b = 6;
	char c = 5;
	char d = 6;
	registro1.writeCampo((char*)&a,sizeof(char),0);
	registro1.writeCampo((char*)&b,sizeof(char),1);

	registro2.writeCampo((char*)&c,sizeof(char),0);
	registro2.writeCampo((char*)&d,sizeof(char),1);

	EXPECT_EQ(true,registro1.equals(registro2));
}

TEST(Registro, suma){
	Registro registro1("i1,i1");
	Registro registro2("i2,i2");
	char a = 5;
	char b = 6;
	short c = 20;
	short d = 20;
	registro1.writeCampo((char*)&a,sizeof(char),0);
	registro1.writeCampo((char*)&b,sizeof(char),1);

	registro2.writeCampo((char*)&c,sizeof(int),0);
	registro2.writeCampo((char*)&d,sizeof(int),1);

	Registro registro3("i1,i1,i2,i2");
	registro3.suma(registro1,registro2);

	char buffer[6];

	memcpy(buffer,(char*)&a,sizeof(char));
	memcpy(buffer+1,(char*)&b,sizeof(char));
	memcpy(buffer+2,(char*)&c,sizeof(short));
	memcpy(buffer+4,(char*)&d,sizeof(short));
	
	std::string serializado;
	registro3.serializar(serializado);
	
	EXPECT_EQ(*buffer,*serializado.c_str());
}

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

TEST(bytemap, getBloque){
		ByteMap bytemap(1024);
		for(int i = 0; i<10; i++){
			EXPECT_EQ(bytemap.getBloque(100),1);
			bytemap.add(1,100);
		}
		EXPECT_EQ(bytemap.getBloque(100),2);
	
}

TEST(bytemap, getBloqueWithSet){
		ByteMap bytemap(1024);
		int acum = 0;
		for(int i = 0; i<39; i++){
			EXPECT_EQ(bytemap.getBloque(27),1);
			acum +=27;
			bytemap.add(1,27);
		}
		EXPECT_EQ(bytemap.getBloque(27),1);
	
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

TEST(ARCHRRLV,addAndReadRegistro){
	ArchRRLV arch("prueba.bin","i1,i2,i4");
	std::cout<<"Se termino de crear el archivo 1"<<std::endl;
	char a = 5;
	short int b = 10;
	int c = 20;
	Registro registro("i1,i2,i4");
	registro.writeCampo((char*)&a,sizeof(a),0);
	registro.writeCampo((char*)&b,sizeof(b),1);
	registro.writeCampo((char*)&c,sizeof(c),2);
	std::cout<<"yes"<<std::endl;
	arch.add(registro);
	std::cout<<"yes"<<std::endl;
	std::string formato = arch.getFormato();
	arch.close();
	ArchRRLV arch2("prueba.bin");
	Registro registro2(formato);
	arch2.read(registro2);
	Campo campo;
	campo = registro2.getCampo(1);
	char A; campo.get(A);
	campo = registro2.getCampo(2);
	short int B; campo.get(B);
	campo = registro2.getCampo(3);
	int C; campo.get(C);
	EXPECT_EQ(A,5);
	EXPECT_EQ(B,10);
	EXPECT_EQ(C,20);
}


TEST(ARCHRRLV,getRegistroXId){
	ArchRRLV arch("prueba.bin","i1,i2,i4");
	std::cout<<"Se termino de crear el archivo 1"<<std::endl;
	char a = 5;
	short int b = 10;
	int c = 20;
	Registro registro("i1,i2,i4");
	registro.writeCampo((char*)&a,sizeof(a),0);
	registro.writeCampo((char*)&b,sizeof(b),1);
	registro.writeCampo((char*)&c,sizeof(c),2);
	
	arch.add(registro);
	c = 50;
	registro.writeCampo((char*)&c,sizeof(c),2);
	arch.add(registro);

	ArchRRLV arch2("prueba.bin");
	Registro registro2(arch.getFormato());
	arch.close();
	arch2.read(registro2,15);
	Campo campo;
	campo = registro2.getCampo(1);
	char A; campo.get(A);
	campo = registro2.getCampo(2);
	short int B; campo.get(B);
	campo = registro2.getCampo(3);
	int C; campo.get(C);
	EXPECT_EQ(A,5);
	EXPECT_EQ(B,10);
	EXPECT_EQ(C,20);
}

TEST(ARCHRRLV,getRegistroXId2){
	ArchRRLV arch("prueba.bin","i1,i2,i4");
	std::cout<<"Se termino de crear el archivo 1"<<std::endl;
	char a = 5;
	short int b = 10;
	int c = 20;
	Registro registro("i1,i2,i4");
	registro.writeCampo((char*)&a,sizeof(a),0);
	registro.writeCampo((char*)&b,sizeof(b),1);
	registro.writeCampo((char*)&c,sizeof(c),2);
	
	arch.add(registro);
	c = 50;
	registro.writeCampo((char*)&c,sizeof(c),2);
	arch.add(registro);

	ArchRRLV arch2("prueba.bin");
	Registro registro2(arch.getFormato());
	arch.close();
	arch2.read(registro2,30);
	Campo campo;
	campo = registro2.getCampo(0);
	int id; campo.get(id);
	campo = registro2.getCampo(1);
	char A; campo.get(A);
	campo = registro2.getCampo(2);
	short int B; campo.get(B);
	campo = registro2.getCampo(3);
	int C; campo.get(C);
	arch2.del(15);
	arch2.del(30);
	EXPECT_EQ(id,30);
	EXPECT_EQ(A,5);
	EXPECT_EQ(B,10);
	EXPECT_EQ(C,50);
	//arch2.del(30);
}

TEST(ARCHRRLV,delAndRead){
	ArchRRLV arch("prueba.bin","i1,i2,i4");
	std::cout<<"Se termino de crear el archivo 1"<<std::endl;
	char a = 5;
	short int b = 10;
	int c = 20;
	Registro registro("i1,i2,i4");
	registro.writeCampo((char*)&a,sizeof(a),0);
	registro.writeCampo((char*)&b,sizeof(b),1);
	registro.writeCampo((char*)&c,sizeof(c),2);
	
	arch.add(registro);
	c = 50;
	registro.writeCampo((char*)&c,sizeof(c),2);
	arch.add(registro);
	arch.add(registro);
	ArchRRLV arch2("prueba.bin");
	std::string formato = arch.getFormato();
	arch.del(30);
	arch.close();

	Registro registro2(formato);
	c = 19;
	registro.writeCampo((char*)&a,sizeof(a),0);
	registro.writeCampo((char*)&b,sizeof(b),1);
	registro.writeCampo((char*)&c,sizeof(c),2);
	std::cout<<"Agregado arch2"<<std::endl;
	arch2.add(registro);
	arch2.read(registro2,30);
	
	Campo campo;
	campo = registro2.getCampo(0);
	int id; campo.get(id);
	campo = registro2.getCampo(1);
	char A; campo.get(A);
	campo = registro2.getCampo(2);
	short int B; campo.get(B);
	campo = registro2.getCampo(3);
	int C; campo.get(C);

	EXPECT_EQ(id,30);
	EXPECT_EQ(A,5);
	EXPECT_EQ(B,10);
	EXPECT_EQ(C,19);
}

TEST(ARCHRRLV,readWithEof){
	ArchRRLV arch("prueba.bin","i1,i2,i4");
	std::cout<<"Se termino de crear el archivo 1"<<std::endl;
	char a = 5;
	short int b = 10;
	int c = 20;
	Registro registro("i1,i2,i4");
	registro.writeCampo((char*)&a,sizeof(a),0);
	registro.writeCampo((char*)&b,sizeof(b),1);
	registro.writeCampo((char*)&c,sizeof(c),2);

	//Agrego 3 registros
	arch.add(registro);
	arch.add(registro);
	arch.add(registro);
	ArchRRLV arch2("prueba.bin");
	std::string formato = arch.getFormato();
	arch.close();
	
	Registro registro2(formato);
	
	EXPECT_EQ(arch2.read(registro2),11);
	EXPECT_EQ(arch2.read(registro2),11);
	EXPECT_EQ(arch2.read(registro2),11);
	EXPECT_EQ(arch2.read(registro2),0);
	}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}

