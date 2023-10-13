/* 5413213 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/iterador.h"

struct cadNats{
  nat elem;//?natural de la cadena
  struct cadNats * sig;//?enlace a la siguiente lista col_nat
};

typedef struct cadNats * TNats;

struct _rep_iterador {
    TNats nat_l;//?puntero a Cadena de naturales
    TNats actual_l;//?apuntara a un colNat 
    TNats final_l; //?final de nat_l
};

TIterador crearIterador() {
    TIterador cadena = new _rep_iterador;//?direccion válida para el iter
    cadena->nat_l =  NULL;
    cadena->actual_l = NULL;
    cadena->final_l = NULL;
    return cadena;
}

void liberarIterador(TIterador iter) {
    if (iter != NULL){
        while (iter->nat_l != NULL){
            TNats a_delete = iter->nat_l;//?guardar nodo a borrar
            iter->nat_l = a_delete->sig;//?configurar siguiente nodo
            delete a_delete;//?eliminar nodo
    }
        delete iter;//?eliminar iter;
    }
    iter = NULL;
}

bool estaDefinidaActual(TIterador iter) {
    if (iter == NULL){
        return false;
    }else{
        return (iter->actual_l !=NULL);
    }
}

void agregarAIterador(nat elem, TIterador const iter) {
    TNats new_elem = new cadNats;//?espacio en mem para nuevo natural
    new_elem->elem = elem;//?setear nuevo elemento
    new_elem->sig = NULL;//?siguiente null, (es el ultimo elem)
    if (iter->nat_l != NULL){
        iter->final_l->sig = new_elem;//?disponerlo al final de la cadena
        iter->final_l = new_elem; //?que final apunte al ultimo nodo(el nuevo)
    }else{
        iter->nat_l = iter->final_l = new_elem;//?enlazar los punteros
    }
}

void reiniciarIterador(TIterador const iter) {
  if (iter->nat_l != NULL){
    iter->actual_l = iter->nat_l;//actual a primero de la lista
  }
}

void avanzarIterador(TIterador const iter) {
  if(estaDefinidaActual(iter)){
    iter->actual_l = iter->actual_l->sig;//actual al siguiente
  }
}

nat actualEnIterador(TIterador iter) {
  return iter->actual_l->elem;//retornar elem de actual
}
