/* 5413213 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colCadenas.h"
#include "../include/cadena.h"


struct _rep_colCadenas {
  TCadena * ArrayCad; //?Arreglos de TCadenas
  nat cota;
  nat tope;
};

TColCadenas crearColCadenas(nat tamanio) {
  TColCadenas colCadenas = new _rep_colCadenas;//?def tamanio del arreglo
  colCadenas->ArrayCad = new TCadena[tamanio];
  for (nat i=0;i<tamanio;i++){
    colCadenas->ArrayCad[i] = crearCadena();//?borrar las cadenas individuales
  }
  colCadenas->cota = tamanio;
  colCadenas->tope = 0;
  return colCadenas;
}

void liberarColCadenas(TColCadenas col) {
  for (nat i = 0; i<col->cota;i++){ 
    liberarCadena(col->ArrayCad[i]);
  }
  delete [] col->ArrayCad;
  delete col;
}

nat tamanioColCadenas(TColCadenas col) {
  return col->tope;
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
  if(col->ArrayCad[pos] == NULL){
    col->tope++;
  }
  col->ArrayCad[pos] = insertarAlInicio(natural,real,col->ArrayCad[pos]);
  return col;
}

TInfo infoEnColCadenas(nat natural, nat pos, TColCadenas col) {
  return infoCadena(natural,col->ArrayCad[pos]);
}

TColCadenas removerDeColCadenas(nat natural, nat pos, TColCadenas col) {
  col->ArrayCad[pos]= removerDeCadena(natural,col->ArrayCad[pos]);
  return col;
}
