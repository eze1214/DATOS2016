/*
 * pruebas.cpp
 *
 *  Created on: 24/10/2015
 *      Author: ezequiel
 */
#include "pruebas.h"
#include <iostream>
//#include "logical/headers/Registro.h"
//#include "logical/headers/Vendedores.h"
#include "logical/headers/Ventas.h"
#include "physical/headers/Parser.h"
#include "physical/headers/ArchRRLF.h"
#include "./logical/headers/Ventas.h"
#include "./logical/headers/Fecha.h"
#include "./physical/headers/ByteMap.h"
#include "./physical/headers/Parser.h"
//void pruebas::RRLV(){
//	/**Voy a probar la clonación de un registro y la asignación de registros**/
//		Vendedores vendedorA(777);
//		Vendedores vendedorB(666);
//		Registro* ptrVendedorA = &vendedorA;
//		vendedorA.setCodPostal(3938);
//		vendedorA.setNomVendedor("Ezequiel");
//		vendedorA.setDireccion("Loria 56.456");
//		vendedorA.setPoblacion("Capital");
//		vendedorA.setEstCivil("Soltero");
//		Fecha fecha(30,12,2019,00,0,0);
//		vendedorA.setFechaAlta(fecha);
//		fecha.set(30,11,2222,0,0,0);
//		vendedorA.setFechaNac(fecha);
//		vendedorA.setNif("32456623H");
//		vendedorA.setTelefono(1538881099);
//
//		/**cLONAMOS POLIMORFICAMENTE**/
//		Registro& clon = ptrVendedorA->clone();
//
//		cout << ((Vendedores&)clon).getIdVendedor() << endl;
//		cout << ((Vendedores&)clon).getCodPostal() << endl;
//		cout << ((Vendedores&)clon).getNomVendedor() << endl;
//		cout << ((Vendedores&)clon).getDireccion() << endl;
//		cout << ((Vendedores&)clon).getPoblacion() << endl;
//		cout << ((Vendedores&)clon).getEstCivil() << endl;
//		fecha =((Vendedores&)clon).getFechaNac();
//		fecha.imprimir();
//		fecha = ((Vendedores&)clon).getFechaAlta() ;
//		fecha.imprimir();
//		cout << ((Vendedores&)clon).getNif() << endl;
//		cout << ((Vendedores&)clon).getTelefono() << endl;
//
//		/**Probamos la asignacion**/
//		vendedorB = vendedorA;
//
//		cout << vendedorB.getIdVendedor() << endl;
//		cout << vendedorB.getCodPostal() << endl;
//		cout << vendedorB.getNomVendedor() << endl;
//		cout << vendedorB.getDireccion() << endl;
//		cout << vendedorB.getPoblacion() << endl;
//		cout << vendedorB.getEstCivil() << endl;
//		Fecha fecha2;
//		fecha2 = vendedorB.getFechaNac();
//		fecha2.imprimir();
//		fecha2 = vendedorB.getFechaAlta();
//		fecha2.imprimir();
//		cout << vendedorB.getNif() << endl;
//		cout << vendedorB.getTelefono() << endl;
//
//
//		cout << "------------------------------------FIN PRUEBA REGISTRO************************"<<endl;
//		delete &clon;
//
//
//		/**Voy a probar el parser serializando e hidratando a un vendedor**/
//		Parser parser;
//		char* buffer = new char[1024];
//		Vendedores vendedor(551);
//		Vendedores copy_vendedor(223);/*Lo creo con un ID distinto a propósito**/
//
//		vendedor.setCodPostal(1842);
//		vendedor.setNomVendedor("Cristian");
//		vendedor.setDireccion("Carlos Pellegrini 564");
//		vendedor.setPoblacion("Monte Grande");
//		vendedor.setEstCivil("Soltero");
//		Fecha fecha3(21,6,2019,0,7,0);
//		vendedor.setFechaNac(fecha3);
//		Fecha fecha4(15,3,2004,0,0,23);
//		vendedor.setFechaAlta(fecha4);
//		vendedor.setNif("32456645D");
//		vendedor.setTelefono(1538881052);
//
//		cout << parser.serializar(vendedor, buffer)
//				<< " caracteres totales empleados" << endl;
//		parser.hidratar(copy_vendedor, buffer);
//
//		cout << copy_vendedor.getIdVendedor() << endl;
//		cout << copy_vendedor.getCodPostal() << endl;
//		cout << copy_vendedor.getNomVendedor() << endl;
//		cout << copy_vendedor.getDireccion() << endl;
//		cout << copy_vendedor.getPoblacion() << endl;
//		cout << copy_vendedor.getEstCivil() << endl;
//		Fecha fecha5 = copy_vendedor.getFechaNac();
//		fecha.imprimir();
//		fecha5 = copy_vendedor.getFechaAlta();
//		cout << copy_vendedor.getNif() << endl;
//		cout << copy_vendedor.getTelefono() << endl;
//
//		delete[] buffer;
//
//		cout
//				<< "----------------------FIN PRUEBA PARSER----------------------------"
//				<< endl;
//
//		/**Creamos un bitmap para un archivo nuevo**/
//		BitMap bitMap;
//
//		/**Se dan de alta 6 registros en el archivo nuevo**/
//		bitMap.appendBit(); //bit 0
//		bitMap.appendBit(); //bit 1
//		bitMap.appendBit(); //bit 2
//		bitMap.appendBit(); //bit 3
//		bitMap.appendBit(); //bit 4
//		bitMap.appendBit(); //bit 5
//
//		/**Borramos el registro 3 del archivo**/
//		bitMap.switchBit(3);
//
//		/**Buscamos espacio libre en el archivo: nos debería devolver 3**/
//		cout << bitMap.getGap() << endl;
//
//		/**Imprimimos el valor del bit 3: debería devolver 0 indicando
//		 * espacio libre en ese sitio.**/
//		cout << (int) bitMap.getBit(3) << endl;
//
//		/**Ahora cerramos el archivo y lo abrimos de vuelta: debemos
//		 * hidratar el bitmap desde disco. En ese caso hay que construir
//		 * el bitmap con el tamanio que tenia antes de serializarlo.
//		 */
//		BitMap copia_bitMap(bitMap.getTamanio());
//		copia_bitMap.hidratar(bitMap.serializar());
//
//		cout
//				<< "_______________________FIN PRUEBA BITMAP____________________________________"
//				<< endl;
//
//		/**
//		 * Creamos un archivo de rrlv en bloques nuevo**/
//		ByteMap byteMap;
//
//		/**Se agregan 6 bloques al archivo nuevo**/
//		unsigned tam_blk = 512;
//
//		byteMap.addGap(0, tam_blk);
//		byteMap.addGap(1, tam_blk);
//		byteMap.addGap(2, tam_blk);
//		byteMap.addGap(3, tam_blk);
//		byteMap.addGap(4, tam_blk);
//		byteMap.addGap(5, tam_blk);
//
//		/**Se realiza una alta de un reg de 45 bytes en el bloque 3**/
//		byteMap.upDateGap(3, 45);
//
//		/**Se realiza la baja del mismo registro**/
//		byteMap.upDateGap(3, -45);
//
//		/**Ahora hacemos alta de reg de 26 bytes en el bloque 0
//		 *               alta de reg de 500 bytes en el bloque 1
//		 *               alta de reg de 10 bytes en el bloque 2
//		 *
//		 */
//		byteMap.upDateGap(0, 26);
//		byteMap.upDateGap(1, 500);
//		byteMap.upDateGap(2, 10);
//
//		/**Ahora buscamos espacio libre para hacer una alta de un registro
//		 * que ocupa 503 bytes: deberia devolver el bloque 3 que quedó vacio
//		 *
//		 */
//		cout << byteMap.getGap(503) << endl;
//
//		/**Ahora cerramos el archivo y lo abrimos de vuelta: entonces tenemos
//		 * que hidratar el byteMap al igual que como hicimos con el bitmap.
//		 * Tenemos que construir el byteMap con el tamanio que tenia antes de su
//		 * serializacion
//		 *
//		 */
//		ByteMap copia_byteMpa(byteMap.getTamanio());
//		copia_byteMpa.hidratar(byteMap.serializar());
//
//
//		//EJEMPLOS HECHOS POR EZE
//
//
//		/*Pruebo  guardando el resultado del la serialización en un string
//		 * y luego lo hidato desde ese string y comparo el comportamiento de ambos
//		 */
//		ByteMap nuevoByteMap;
//		ByteMap nuevoByteMap2;
//		nuevoByteMap.addGap(1,256);
//		nuevoByteMap.addGap(2,512);
//		char *auxiliar=new char [1024];
//		nuevoByteMap.serializar(auxiliar,1024);
//		nuevoByteMap2.hidratar(auxiliar);
//		delete[] auxiliar;
//		cout << "espacio en 1 con byteMap1 "<<nuevoByteMap.getCantBytes(1) <<"con ByteMap 2 "<<nuevoByteMap2.getCantBytes(1)<<endl;//debe dar 3
//		cout << "espacio en 1 con byteMap1 "<<nuevoByteMap.getCantBytes(2) <<"con ByteMap 2 "<<nuevoByteMap2.getCantBytes(2)<<endl;//debe dar 3
//
//	/*
//	 * Ejemplo que muestra el uso de las primitivas insert y search
//	 *  */
//		ArchRRLV arch("eze.eze",1024); //ME creo un nuevo vendedor
//		Vendedores nuevo(321);
//		nuevo.setCodPostal(1842);
//		nuevo.setNomVendedor("Ezequiel");
//		nuevo.setDireccion("Calle Falsa 564");
//		nuevo.setPoblacion("Lanus");
//		nuevo.setEstCivil("Soltero");
//		Fecha fecha6(21,6,2020,0,7,0);
//		nuevo.setFechaNac(fecha6);
//		Fecha fecha7(15,3,2005,0,0,23);
//		nuevo.setFechaAlta(fecha7);
//		nuevo.setNif("32452642D");
//		nuevo.setTelefono(1522881052);
//		Vendedores modificar(321);
//		modificar.setCodPostal(1842);
//		modificar.setNomVendedor("Leandro");
//		modificar.setDireccion("Calle Falsisima564345643");
//		modificar.setPoblacion("Lanus Oeste");
//		modificar.setEstCivil("Re Soltero");
//		Fecha fecha8(21,6,2020,0,7,0);
//		modificar.setFechaNac(fecha8);
//		fecha8.set(15,3,2005,0,0,23);
//		modificar.setFechaAlta(fecha8);
//		modificar.setNif("324526");
//		modificar.setTelefono(1522881052);
//		buffer = new char [1024];
//
//		cout<<"cantidad de bytes por vendedor nuevo"<<parser.serializar(nuevo,buffer)<<endl;
//		cout<<"cantidad de bytes por vendedor modificar"<<parser.serializar(modificar,buffer)<<endl;
//		delete []buffer;
//
//		cout<<"Insertado en bloque "<<arch.insert(vendedor)<<endl;//inserto varios registros todavia no hace chequeo de unicidad
//		cout<<"Insertado en bloque "<<arch.insertU(nuevo)<<endl;
//		cout<<"Insertado en bloque "<<arch.insert(vendedor)<<endl;
//		cout<<"Insertado en bloque "<<arch.insert(vendedor)<<endl;
//		cout<<"Insertado en bloque "<<arch.insert(vendedor)<<endl;
//		cout<<"Insertado en bloque "<<arch.insert(vendedor)<<endl;
//		cout<<"Insertado en bloque "<<arch.insert(vendedor)<<endl;
//		cout<<"Insertado en bloque "<<arch.insert(vendedor)<<endl;
//		cout<<"Insertado en bloque "<<arch.insert(vendedor)<<endl;
//		arch.save();
//		cout<<"modificacion "<<arch.edit(modificar);
//		//cout<<"get tamanio "<<arch.byteMap->getTamanio();
//		Vendedores buscar(321);//creo un resigistro con el objetivo de buscar
//		Vendedores encontrado(321);
//
//		bool yes = arch.search(encontrado);
//		if (yes) { // si lo encuentro imprimo sus datos
//			cout<<"Registro encontrado sus datos son ";
//			cout << "ID Vendedor "<<encontrado.getIdVendedor() << endl;
//			cout << "Cod Postal "<<encontrado.getCodPostal() << endl;
//			cout << "Nombre Vendedor "<<encontrado.getNomVendedor() << endl;
//			cout << "Direccion "<<encontrado.getDireccion() << endl;
//			cout << "Poblacion "<<encontrado.getPoblacion() << endl;
//			cout << "Estado civil "<<encontrado.getEstCivil() << endl;
//			fecha = encontrado.getFechaNac();
//			fecha.imprimir();
//			fecha = encontrado.getFechaAlta();
//			fecha.imprimir();
//			cout << "Ninf "<<encontrado.getNif() << endl;
//			cout << "Telefono "<<encontrado.getTelefono() << endl;
//		}
//		cout<<"Resultado del la eliminación "<<arch.del(encontrado)<<endl;
//
//
//}
void pruebas::RRLF(){
	Fecha fechaOP(0,9,10,2,2,2);
	Ventas venta (123,321,fechaOP);
	venta.setKilos(10.24);
	/**Voy a probar la clonación de un registro y la asignación de registros**/
	Registro* ptrVenta = &venta;

	/**cLONAMOS POLIMORFICAMENTE**/
	Registro& clonVenta = ptrVenta->clone();
	cout << ((Ventas&)clonVenta).getCodVendedor()<<endl;
	cout << ((Ventas&)clonVenta).getCodProducto() << endl;
	fechaOP = ((Ventas&)clonVenta).getFecha();
	fechaOP.imprimir();
	cout<< ((Ventas&)clonVenta).getKilos()<<endl;
	delete &clonVenta;

	Parser parser;
	char* buffer = new char[1024];
	Ventas copiaVenta(21,432,fechaOP);
	int tamanio =parser.serializar(venta, buffer);
	cout <<tamanio << " caracteres totales empleados" << endl;
	parser.hidratar(copiaVenta, buffer);
	cout << ((Ventas&)copiaVenta).getCodVendedor()<<endl;
	cout << ((Ventas&)copiaVenta).getCodProducto() << endl;
	fechaOP = ((Ventas&)copiaVenta).getFecha();
	fechaOP.imprimir();
	cout<< ((Ventas&)copiaVenta).getKilos()<<endl;
	delete[] buffer;

	ArchRRLF arch("archRegFijo.eze",tamanio);
	arch.insert(venta);
	Ventas regBuscar(123,321,fechaOP);
	cout<<"regBuscar "<<arch.read(regBuscar)<<endl;
	if(arch.read(regBuscar) != -1){
		cout<<"Cantidad de kilos "<<regBuscar.getKilos()<<endl;
	}
	cout<<"regBuscar "<<arch.read(venta)<<endl;
	if(arch.insertU(venta)==-1)cout<<"Registro Existente no se puede insertar"<<endl;//Inserto de nuevo el registro me detecta la existencia
	fechaOP.set(14,12,2000,12,20,20);
	Ventas otraVenta(321,32,fechaOP);otraVenta.setKilos(25.67);
	cout<<"insertado en bloque "<<arch.insertU(otraVenta)<<endl;
	cout<<"del "<<arch.del(venta)<<endl;
	if(arch.read(regBuscar) == -1){ //busco el registro que elimine
		cout<<"Registro inexistente "<<endl;
	}
	cout<<"insert en bloque "<<arch.insertU(venta);//lo vuelvo a insertar

	//Busco los dos registro y los imprimo
	fechaOP.set(0,9,10,2,2,2);
	Ventas buscar1(123,321,fechaOP);
	fechaOP.set(14,12,2000,12,20,20);
	Ventas buscar2(321,32,fechaOP);
	arch.read(buscar1); cout<<"Kilos reg1 "<<buscar1.getKilos()<<endl;
	arch.read(buscar2); cout<<"Kilos reg2 "<<buscar2.getKilos()<<endl;

	//Edito el primer registro
	fechaOP.set(0,9,10,2,2,2);
	Ventas editar(123,321,fechaOP);editar.setKilos(5.08);
	cout<<"bloque donde fue editado "<<arch.edit(editar)<<endl;
	cout<< arch.read(buscar1); cout<<"Kilos reg1 "<<buscar1.getKilos();

}

