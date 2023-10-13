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
    TCadena primero = cad;
    if (primero !=NULL){
        cad = cad->sig;
        while (cad !=NULL && cad != primero){
            liberarInfo(cad->par);//?eliminar info del primero en cola
            cad->ant->sig = cad->sig;
            cad->sig->ant = cad->ant;
            TCadena a_delete = cad;
            cad = cad->sig;
            delete a_delete;
        }
        liberarInfo(cad->par);//?eliminar info del primero en cola
        delete cad;
        cad = NULL;
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

bool estaEnCadena(nat natural, TCadena cad){
    if (cad == NULL){
        return false;
    }else{
        TCadena primero = cad;
        if (natInfo(primero->par) != natural){  
            cad = cad->sig;      
            while (cad != primero && natInfo(cad->par) != natural) {
                cad = cad->sig;
            }
        }
        return (natInfo(cad->par)==natural);
    } 
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
    while (natInfo(cad->par) != natural){
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
    TCadena aux = cad;
    while (natInfo(cad->par) != natural)//!prec: estaEnCadena(natural)
    {
      cad = cad->sig;
    }
    if (cad->sig ==cad){//?hay solo un elem
        liberarInfo(cad->par);
        delete cad;
        cad = NULL;
        return cad;
    }
    liberarInfo(cad->par);
    cad->ant->sig = cad->sig;
    cad->sig->ant = cad->ant;
    if (cad == aux){//?es el primer elem
        aux = cad->sig;
    }
    delete cad;
    return aux;
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

TCadena insertarAlFinal(nat natural, double real, TCadena cad) {
    TCadena aux = new _rep_cadena;
    aux->par = crearInfo(natural,real);
    if (cad != NULL){
        aux->sig = cad;
        aux->ant = cad->ant;
        cad->ant->sig = aux;
        cad->ant = aux;
        return cad;
    }else{
        aux->sig=aux->ant = aux;
        return aux;
    }
}

TCadena removerPrimero(TCadena cad) {
    return removerDeCadena(natInfo(primeroEnCadena(cad)),cad);
}

TCadena copiaCadena(TCadena cad) {
   TCadena aux=NULL;  
    for (nat i=0; i<cantidadEnCadena(cad);i++){
        aux = insertarAlFinal(natInfo(primeroEnCadena(cad)),realInfo(primeroEnCadena(cad)),aux);
        cad = cadenaSiguiente(cad);
  }
  return aux;
}
