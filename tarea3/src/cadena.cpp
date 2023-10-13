/* 5413213 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/cadena.h"

struct _rep_cadena {
  TInfo par;
  _rep_cadena * sig;
  _rep_cadena * ant;
};

TCadena crearCadena() {
  return NULL;
}


void liberarCadena(TCadena cad) {
  nat i = 0;
  nat qty_nodos = cantidadEnCadena(cad);
  while (i < qty_nodos)
  {
    i++;
    liberarInfo(cad->par);//eliminar info del primero en cola
    cad->ant->sig = cad->sig;
    cad->sig->ant = cad->ant;
    TCadena a_delete = cad;
    cad = cad->sig;
    delete a_delete;
  }
}

nat cantidadEnCadena(TCadena cad) {
  nat idx = 0;
  if (cad == NULL){//?si la lista es vacía
    return idx;
  }
  else{
    TCadena aux_cad = cad;
    idx++; 
    while (aux_cad->sig != cad )//?recorrer los sig punteros, hasta encontrar de nuevo el primero
    {
      idx++;
      aux_cad = aux_cad->sig;
    }
  }
  return idx;
}


bool estaEnCadena(nat natural, TCadena cad) {
  nat idx = 1;
  nat qty_nodos = cantidadEnCadena(cad);
  while ( idx <= qty_nodos && natInfo(cad->par) != natural)
  {
    idx++;
    cad = cad->sig;
  }
  return (idx <= qty_nodos);
}

TCadena insertarAlInicio(nat natural, double real, TCadena cad) {
  TCadena aux_cad = cad;
  cad = new _rep_cadena;
  cad->par = crearInfo(natural,real);//?put info
  if (aux_cad !=NULL){
    cad->sig = aux_cad;//?setear siguiente  del nuevo puntero
    cad->ant = aux_cad->ant;//?setear anterior del nuevo puntero
    aux_cad->ant->sig = cad;//?setear siguiente del ultimo puntero
    aux_cad->ant = cad;//?setear el anterior del siguiente puntero
  }else{
    cad->sig = cad;
    cad->ant = cad;
  }
  
  return cad;
}

TInfo infoCadena(nat natural, TCadena cad) {
  nat idx = 1;
  while (natInfo(cad->par) != natural)
  {
    idx++;
    cad = cad->sig;
  }
  return cad->par;
}

TInfo primeroEnCadena(TCadena cad) {
  return cad->par;
}

TCadena cadenaSiguiente(TCadena cad) {
  if (cad !=NULL){
    return cad->sig;
  }
  return NULL;
}

TCadena removerDeCadena(nat natural, TCadena cad) {
  if (cantidadEnCadena(cad) ==1){
    liberarInfo(cad->par);
    delete cad;
    cad = NULL;
    return cad;
  }else{
    TCadena aux = cad;
    while (natInfo(cad->par) != natural)//!prec: estaEnCadena(natural)
    {
      cad = cad->sig;
    }
    if (aux == cad){
      aux = cad->sig;
    }
    liberarInfo(cad->par);
    cad->ant->sig = cad->sig;
    cad->sig->ant = cad->ant;
    delete cad;
    return aux;
  }
}

void imprimirCadena(TCadena cad) {
  nat idx = 0;
  nat qty = cantidadEnCadena(cad);
  while ( idx < qty )
  {
    idx++;
    imprimirInfo(cad->par);
    cad = cad->sig;
  }
  printf("\n");
}
