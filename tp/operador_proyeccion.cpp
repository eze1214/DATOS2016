#include "operador_proyeccion.h"
#include "registro.h"

OperadorProyeccion::OperadorProyeccion(std::string filename,GestorAA& gestor, vector< unsigned >& listaCampos){
	GestorAA nuevo (filename,gestor.getTamBloque(),gestor.getFormato());
	std::string formato = gestor.getFormato();
	Registro registro(gestor.getFormato());
	Bloque bloque;
	std::vector <unsigned short> bloquesAProcesar = gestor.getNumBloquesOcupados();
	
	registro.bloquearTodosCampos();
	
	//Desbloqueo los que me interesan
	for (unsigned i = 0; i < listaCampos.size(); i++){
				registro.desbloquearCampo(listaCampos[i]);			
	}
	
	for (unsigned i = 0; i< bloquesAProcesar.size();++i){
		bloque = gestor.getBloque(bloquesAProcesar[i]);
		for(unsigned j = 0; j<bloque.cantRegistros();j++){
				registro = bloque.getRegistro(j);
				registro.print();
				nuevo.insert(registro);
			
		}
	}
}
	
