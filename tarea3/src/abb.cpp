/* 5413213 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/abb.h"

struct _rep_abb {
    TInfo par;
    TAbb izq,der;
};

TAbb crearAbb() {
    return NULL; 
}

void liberarAbb(TAbb abb) {
    if (abb != NULL)
    {
        liberarAbb(abb->izq);
        liberarAbb(abb->der);
        liberarInfo(abb->par);
        delete abb;
    } 
    abb=NULL;
}

bool esVacioAbb(TAbb abb) { 
    return (abb ==NULL); 
}

TAbb buscarSubarbol(nat clave, TAbb abb) {//?es ordenado mismo caso que buscar en lista lineal
    while (abb !=NULL && natInfo(abb->par)!=clave)
    {
        if (natInfo(abb->par) > clave)//?la clave es menor entonces buscar por el lado izq
        {
            abb = abb->izq;
        }else{
            abb = abb->der;
        }
    }
    return abb;
    
}

TInfo raiz(TAbb abb) {
    return abb->par;
}

TAbb izquierdo(TAbb abb) {
    return abb->izq;
}

TAbb derecho(TAbb abb) {
    return abb->der;
}

TInfo menorEnAbb(TAbb abb){//?el menor es aquel que esta más a la izq del árbol
    while (abb !=NULL && abb->izq!=NULL){
        abb = abb->izq;
    }
    return abb->par;
}

TInfo mayorEnAbb(TAbb abb) {
    while (abb !=NULL && abb->der!=NULL){
        abb = abb->der;
    }
    return abb->par;
}

TAbb consAbb(TInfo dato, TAbb izq, TAbb der) {
    TAbb new_abb = new _rep_abb;
    new_abb->par = dato;
    new_abb->izq = izq;
    new_abb->der = der;
    return new_abb;
}

static void insAbbRec(TInfo dato, TAbb &abb){//?procedimiento aux
    if (abb == NULL){
        abb = new _rep_abb;
        abb->par = dato;
        abb->izq = abb->der = NULL; 
    }
    else{ 
        if (natInfo(dato) > natInfo(abb->par)){
            insAbbRec(dato,abb->der);//?recorrer der
    }   
        else if (natInfo(dato) < natInfo(abb->par)){
            insAbbRec(dato,abb->izq);//?recorrer izq
    }
    }
}

TAbb insertarEnAbb(TInfo dato, TAbb abb) {//?siempre se inserta como hoja
    insAbbRec(dato,abb);
    return abb;
}

static void remAbbRec(nat clave, TAbb &abb){
    if(clave == natInfo(abb->par)){
        TAbb borrar = abb;
        if(abb->izq == NULL ){
            abb = abb->der;
            liberarInfo(borrar->par);
            delete borrar;
        }
        else if (abb->der == NULL){
            abb = abb->izq;
            liberarInfo(borrar->par);
            delete borrar;
        }else{//?ambos nodos izq y der no son nulos
            liberarInfo(borrar->par);
            borrar->par = copiaInfo(mayorEnAbb(abb->izq));//?se sustituye la info del nodo a eliminar
            remAbbRec(natInfo(borrar->par),abb->izq);//?se elimina el nodo q se sustituyo (el maxEnAbb(abb->izq))
        }
    }
    else if(clave > natInfo(abb->par)){//?si es mayor q el nodo a disposicion
        remAbbRec(clave,abb->der);
    }else{//?debe ser menor, ya que es prec que exista el nodo a eliminar
        remAbbRec(clave,abb->izq);
    }
}

TAbb removerDeAbb(nat clave, TAbb abb) {
    remAbbRec(clave,abb);
    return abb;
}

TAbb copiaAbb(TAbb abb) {
    if (abb == NULL){
        return NULL;
    }
    TAbb new_abb = new _rep_abb; //?arbol copia, reservar nuevo espacio
    new_abb->par = copiaInfo(abb->par);//?copiar el nodo a disposicion
    new_abb->izq = copiaAbb(abb->izq);//?configurar subarboles de la copia
    new_abb->der = copiaAbb(abb->der);
    return new_abb;
}
