#include "gestor_aa.h"
#include <cstdlib>
GestorAA::GestorAA(std::string formato){
	
}

GestorAA::import(std::string csv,std::string formato){
	FILE *archivo;
 	
 	char caracteres[100];
 	
 	archivo = fopen(csv.data(),"r");
 	
 	if (archivo == NULL)
 		std::cout<<"Error el archivo no existe"<<std::endl;
 	
 	while (feof(archivo) == 0)
 	{
 		fgets(caracteres,100,archivo);
 		
	}
        fclose(archivo);
}