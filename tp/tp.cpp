#include <iostream>
#include "parser_formato.h"
#include <vector>

int main(int argc, char * argv[]){
 std::vector<Formato> formatos;
 const std::string parametro("i1,sD,i4,i8,i8"); 
 ParserFormato parser(parametro);
 formatos = parser.getFormatos();
 std::vector<Formato>::const_iterator it = formatos.begin();
 for(;it!=formatos.end();++it){
    std::cout<<(*it).tipo<<" "<<(*it).longitud<<std::endl;
 }
 return 0;
}