#include "operador_proyeccion.h"
#include "registro.h"

OperadorProyeccion::OperadorProyeccion(std::string filename,GestorAA& gestor, vector< unsigned >& listaCampos){
	std::string formato = gestor.getFormato();
	Registro registro(gestor.getFormato());
	Bloque bloque;
	std::vector <unsigned short> bloquesAProcesar = gestor.getNumBloquesOcupados();
	
	registro.bloquearTodosCampos();
	
	//Desbloqueo los que me interesan
	for (unsigned i = 0; i < listaCampos.size(); i++){
				registro.desbloquearCampo(listaCampos[i]);			
	}
	
	GestorAA nuevo (filename,gestor.getTamBloque(),registro.getFormato());
	
	for (unsigned i = 0; i< bloquesAProcesar.size();++i){
		bloque = gestor.getBloque(bloquesAProcesar[i]);
		for(unsigned j = 0; j<bloque.cantRegistros();j++){
				registro = bloque.getRegistro(j);
					registro.bloquearTodosCampos();
	
	//Desbloqueo los que me interesan
	for (unsigned i = 0; i < listaCampos.size(); i++){
				registro.desbloquearCampo(listaCampos[i]);			
	}
				//registro.print();
				nuevo.insert(registro);
			
		}
	}
}
	
OperadorProyeccion::OperadorProyeccion(std::string filename,GestorAARRLV& gestor, vector< unsigned >& listaCampos){
	std::string formato = gestor.getFormato();
	Registro registro(formato);
	
	registro.bloquearTodosCampos();
	
	//Desbloqueo los que me interesan
	for (unsigned i = 0; i < listaCampos.size(); i++){
				registro.desbloquearCampo(listaCampos[i]);			
	}
	
	GestorAARRLV nuevo (filename,registro.getFormato());
	
	int salida;
	bool terminar = false;

	while(!terminar){
		salida = gestor.read(registro);
		if (salida == 0) {
			terminar = true;
		}else{
			registro.bloquearTodosCampos();
			//Desbloqueo los que me interesan
			for (unsigned i = 0; i < listaCampos.size(); i++){
				registro.desbloquearCampo(listaCampos[i]);			
			}
			nuevo.write(registro);
		}
	}
}
