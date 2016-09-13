#ifndef PARSERFORMATO_H
#define PARSERFORMATO_H
#include <vector>
#include <sstream>
/* Formato: Estructura para manejar el formato
 * de un registro
 */

const unsigned SIZE_CADENA_CORTA = 256;//Esto no va
const unsigned SIZE_FECHA_CORTA = 8;
const unsigned SIZE_FECHA_LARGA = 15; 

  enum TIPO_FORMATOS{
   ENTERO=0,
   CADENA_FIJA,
   CADENA_VARIABLE,
   FECHA_CORTA,
   FECHA_LARGA
 };
 
struct Formato{
 
 TIPO_FORMATOS tipo;
 unsigned longitud;
};

/*ParserFormato: Dato un string un lo parsea
 * obteniendo un vector de formatos
 * 
 */
class ParserFormato{
private:
  std::vector <Formato> formatos;
  Formato buildFormato(const std::stringstream & buffer);
  
public:
  ParserFormato(const std::string&);
  std::vector <Formato> getFormatos() const;
};

#endif // PARSERFORMATO_H
