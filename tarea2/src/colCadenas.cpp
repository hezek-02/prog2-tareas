/* 5413213 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colCadenas.h"

struct _rep_colCadenas {
  TCadena ArrayCad[CANT_CADS];
};

TColCadenas crearColCadenas() {
  TColCadenas col_chain = new _rep_colCadenas;
  for (nat i=0;i<CANT_CADS;i++){
    col_chain->ArrayCad[i] = crearCadena();
  }
  return col_chain;
}

void liberarColCadenas(TColCadenas col) {
  for (nat i = 0; i<CANT_CADS;i++){ 
    liberarCadena(col->ArrayCad[i]);
  }
  delete col;
}

TCadena cadenaDeColCadenas(nat pos, TColCadenas col) {
  return col->ArrayCad[pos];
}

nat cantidadColCadenas(nat pos, TColCadenas col) {
  return cantidadEnCadena(col->ArrayCad[pos]);
}

bool estaEnColCadenas(nat natural, nat pos, TColCadenas col) {
  return estaEnCadena(natural,col->ArrayCad[pos]);
}

TColCadenas insertarEnColCadenas(nat natural, double real, nat pos,
                                 TColCadenas col) {
  col->ArrayCad[pos] = insertarAlInicio(natural,real,col->ArrayCad[pos]);
  return col;
}

TInfo infoEnColCadenas(nat natural, nat pos, TColCadenas col) {
  return infoCadena(natural,col->ArrayCad[pos]);
}

TColCadenas removerDeColCadenas(nat natural, nat pos, TColCadenas col) {
  col->ArrayCad[pos] = removerDeCadena(natural,col->ArrayCad[pos]);
  return col;
}
