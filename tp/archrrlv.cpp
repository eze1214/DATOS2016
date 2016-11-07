#include "archrrlv.h"
#include "registro.h"
#include <cstdio>
#include <cstdlib>

ArchRRLV::ArchRRLV(std::string filename, std::string formato):abierto(true){
	this->filename = filename;
	//Agrego el ID
	std::string id = "i4,";
	this->formato = id + formato;
	this->puntero = 0;
	if (existeArchivo(filename)){
		std::cout<<"El archivo ya existe será sobreescribido"<<std::endl;
	}
	crearArchivo("wb+");
	crearArchivoRegistrosLibres();
}

void ArchRRLV::crearArchivoRegistrosLibres(){
	const std::string prefijo("RegistrosLibres");
	registrosLibres = prefijo + filename;
	archivoRegistrosLibres = fopen(registrosLibres.data(),"w");
	if (archivo != NULL) std::cout<<"archivo de registros libres creado correctamente"<<std::endl;
}

ArchRRLV::~ArchRRLV(){
	if (abierto){
		std::cout<<"se ejecuta el destructor y se cierra el archivo"<<std::endl;
		fclose(archivo);
		fclose(archivoRegistrosLibres);
		abierto = false;
	}
}

std::string ArchRRLV::getFormato(){
	return formato;
}

void ArchRRLV::crearArchivo(std::string configuracion){
	archivo = fopen(filename.data(),configuracion.c_str());

	if (archivo != NULL) std::cout<<"archivo creado correctamente"<<std::endl;
	
	grabarFormato();	
}
//TODO revizar
/*Ahora esta todo encapsulado en la clase desriptores
 * Falta crear el comportamiento de cuando se agrega
 * un registro que busque en la lista de espacio libre cual es la 
 * mas conveniente.
 */
ArchRRLV::ArchRRLV(std::string filename):abierto(true){
	const std::string prefijo("RegistrosLibres");
	this->filename = filename;
	archivo = fopen(filename.data(),"rb+");
	registrosLibres = prefijo + filename.data();
	archivoRegistrosLibres = fopen(registrosLibres.data(),"r+");
	leerFormato();
	puntero = ftell(archivo);
}

void ArchRRLV::close(){
		if (abierto){
			abierto = false;
			fclose(archivo);
			fclose(archivoRegistrosLibres);
		}
	}

bool ArchRRLV::existeArchivo(std::string nombreArchivo){
	bool existencia;
	FILE *archivo;
	archivo = fopen(nombreArchivo.data(),"r+b");
	if (archivo != NULL) {
		existencia = true;
		fclose(archivo);
	}
	else existencia = false;
	return existencia;
}

void ArchRRLV::leerFormato(){
	//voy al inicio del archivo
	fseek(archivo,0,SEEK_SET);

	char * buffer;
	size_t size = 0;
	int outRead;
	outRead = fread(&size,sizeof(size_t),1,archivo);
	buffer = new char[size];
	outRead = fread(buffer,size,1,archivo);
	if (outRead<=0) std::cout<<"Error de lectura en leerFormato"<<std::endl;
	formato.clear();
	formato.append(buffer,size);
	delete[] buffer;
}

void ArchRRLV::grabarFormato(){
	size_t formato_size = formato.size();
	fwrite((char *) & formato_size, sizeof(size_t),1,archivo);
	fwrite((char*) formato.c_str(),formato.size(),1,archivo);
}

void ArchRRLV::grabarDescriptor(){
	std::string serializado;
	descriptor.serializar(serializado);
	puntero = descriptor.getNext();
	unsigned char size = descriptor.getSize();
	fwrite(&size, sizeof(char),1,archivo);
	fwrite(serializado.c_str(),serializado.size(),1,archivo);
}

bool ArchRRLV::eof(){
	return feof(archivo);
}
void ArchRRLV::leerDescriptor(unsigned offset){
	unsigned char size;
	int  out;
	out = fread(&size, sizeof(char), 1, archivo);
	char * buffer = new char[size];
	out = fread(buffer, size, 1, archivo);
	if(out <= 0) std::cout<<"Error al leerDescriptor";
	std::string serializado(buffer,size);
	descriptor.serializar(serializado);
	delete [] buffer;
}

void ArchRRLV::add(Registro & registro){
	std::string serializado;
	registro.serializar(serializado);
	this->grabarRegistro(serializado);
}

void ArchRRLV::buscarEspacioLibre(unsigned size){
	unsigned idSeleccionado = getLibre(size);
	if (idSeleccionado == 0)
		fseek(archivo,0,SEEK_END);
	else
		fseek(archivo,idSeleccionado,SEEK_SET);	
}


void ArchRRLV::agregarID(std::string & registro){
	unsigned id = ftell(archivo);
	std::string cadenaId;
	cadenaId.append((char *) &id,sizeof(unsigned));
	registro = cadenaId + registro;
}
void ArchRRLV::grabarRegistro( std::string registro){
	size_t size = registro.size()+sizeof(unsigned);//Le sumo el size del ID
	buscarEspacioLibre(size+sizeof(size_t));//Le sumo el size of del if
	agregarID(registro);
	
	int salida = fwrite((char * ) & size, sizeof(size_t) ,1,archivo);
	salida = fwrite(registro.c_str(),size,1,archivo);
	if (salida <= 0) std::cout<<"error al grabar registro"<<std::endl;
}


void ArchRRLV::gotoPuntero(){
	fseek(archivo,puntero,SEEK_SET);
}

void ArchRRLV::addLibre(unsigned id, size_t size){
	fprintf(archivoRegistrosLibres,"%u %u\n",id,size);
}

//FIXME solucionar el tema del borrado que pued dejar algun caracter
void ArchRRLV::borrarLibre(unsigned linea){
	rewind(archivoRegistrosLibres);
	bool terminar = false;
	unsigned idLeido=0;
	size_t size=0;
	int salida=0;
	unsigned contador = 0;
	while (!terminar){
		if (contador == linea){
			fprintf(archivoRegistrosLibres,"%u %u\n",salida,salida);
			terminar = true;
		}else{
		contador++;
		if(fscanf(archivoRegistrosLibres,"%u %u",&idLeido,&size)<=0)
			std::cout<<"Error borrarLibre";
		}
	}

}

unsigned ArchRRLV::getLibre(unsigned sizeNecesario){
	rewind(archivoRegistrosLibres);
	bool terminar = false;
	unsigned idLeido=0;
	unsigned idSeleccionado=0; 
	size_t size=0;
	unsigned salida;
	unsigned linea = 0;
	while (!terminar){
		salida = fscanf(archivoRegistrosLibres,"%u %u",&idLeido,&size);
		if (feof(archivoRegistrosLibres) or salida <= 0 or idLeido == 0){
			terminar = true;
		} else{
			if (size >= sizeNecesario){
				idSeleccionado = idLeido;
				borrarLibre(linea);
			}
		}
		linea++;
	}
	return idSeleccionado;
}

void ArchRRLV::del(unsigned id){
	fseek(archivo,id,SEEK_SET);
	size_t size;
	if(fread((char * ) &size, sizeof(size_t), 1, archivo)<=0)
		std::cout<<"error al leer un archvo"<<std::endl;
	char * buffer = new char [size+sizeof(size_t)];
	memset(buffer,0,size+sizeof(size_t));
	fseek(archivo,-sizeof(size_t),SEEK_CUR);
	fwrite(buffer,size+sizeof(size_t),1,archivo);

	addLibre(id,size+sizeof(size_t));
}

int ArchRRLV::read(Registro & registro, unsigned id){
	fseek(archivo,id,SEEK_SET);
	return read(registro);
}


int ArchRRLV::read(Registro & registro){
	size_t size; 
	int leido;
	do{
		if((leido = fread((char * ) &size, sizeof(size_t), 1, archivo))<=0 and !feof(archivo))
			std::cout<<"error al leer un archvo leido"<<leido<<std::endl;
		if (leido > 0 and size==0 and !feof(archivo)){
			fseek(archivo,-(sizeof(unsigned)-1),SEEK_CUR);
		}
	} while(leido > 0 and size==0 and !feof(archivo));
	if (size!=0 and !feof(archivo)) {
		char * buffer = new char [size];
		int out =fread(buffer,size,1,archivo);
		if (out <= 0 ) std::cout<<"Error al leer "<<std::endl;
		registro.hidratar(buffer,size);
		delete [] buffer;
	}
	if (feof(archivo)) return 0;
		else
		return size;
}