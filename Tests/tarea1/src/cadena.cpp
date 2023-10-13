/* 5413213 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/cadena.h"

// los elementos se mantienen entre 0 y cantidad - 1, incluidos
struct _rep_cadena {
  TInfo par;
  struct _rep_cadena * sig;
};

TCadena crearCadena() {
  return NULL;
}

/* en siguientes tareas
void liberarCadena(TCadena cad) {
}
*/

nat cantidadEnCadena(TCadena cad) {
  TCadena aux_cad = cad;
  nat idx = 0;
  while (aux_cad != NULL && idx<L)
  {
    idx++;
    aux_cad = (*aux_cad).sig;
  }
  return idx;
}

bool estaEnCadena(nat natural, TCadena cad) {
  nat idx = 1;
  nat qty = cantidadEnCadena(cad);
  TCadena aux_cad = cad;
  while ( idx <= qty && natInfo((*aux_cad).par) != natural)
  {
    idx++;
    aux_cad = (*aux_cad).sig;
  }
  return (idx <= qty);
}

TCadena insertarAlInicio(nat natural, double real, TCadena cad) {
  TCadena aux_cad = cad;
  cad = new _rep_cadena;
  (*cad).par = crearInfo(natural,real);
  (*cad).sig = aux_cad;  
  return cad;
}

TInfo infoCadena(nat natural, TCadena cad) {
  nat idx = 1;
  TCadena aux_cad = cad;
  while (natInfo((*aux_cad).par) != natural)
  {
    idx++;
    aux_cad = (*aux_cad).sig;
  }
  return (*aux_cad).par;
}

TCadena removerDeCadena(nat natural, TCadena cad) {
  TCadena aux = cad;
  TCadena aux_2 = (*cad).sig;
  if (natInfo((*aux).par) == natural){
    cad = aux_2;
    liberarInfo((*aux).par);
    delete aux;
  }
  else{
    while (natInfo((*aux_2).par) != natural){
      aux = aux_2;
      aux_2 = (*aux_2).sig;
    }
    (*aux).sig = (*aux_2).sig;
    liberarInfo((*aux_2).par);
    delete aux_2;
  }
  return cad;
}

void imprimirCadena(TCadena cad) {
  nat idx = 1;
  nat qty = cantidadEnCadena(cad);
  TCadena aux_cad = cad;
  while ( idx <= qty )
  {
    idx++;
    imprimirInfo((*aux_cad).par);
    aux_cad = (*aux_cad).sig;
  }
  printf("\n");
}
