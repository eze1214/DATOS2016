Este repositorio no contiene un proyecto eclipse c++ si no sólo los fuentes.
Para crear el proyecto en eclipse tienen que hacer lo siguiente:

0_instalar git y el plugin de git para eclipse.
1_clonar el repositorio en su máquina.
2_crear desde eclipse un nuevo proyecto c++ vacio del tipo executable.
3_el nombre del nuevo proyecto puede ser cualquiera
4-la locacion deben poner el path del repositorio clonado.
5-eclipse crea entonces un proyecto linkeado y funciona como si estubiera en el workspace
6-luego solo deben compiarlo y ejecutarlo.
7-el archivo commit está puesto a propósito para que me suba la estructura de directorios.
  (si un dir está vacio entonces no me lo sube al repo remoto)
  
  
Mi experiencia es que cuando ponemos un proyecto eclipse en el repositoriio remoto, luego
cuando lo bajamos hay problemas para compilarlo debido a que los .proyect difieren de una maquina a otra.
Por eso decidí hacerlo de este modo.