/* 5413213 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/pila.h"

struct lista_p{
    TInfo par;
    lista_p *sig;
};

struct _rep_pila {
    lista_p *ini,*fin;
    nat qty;    
};
//?Tpila es un puntero al cabezal el cual ini a punta al inicio de lista pilas;
TPila crearPila() {
    TPila cabezal = new _rep_pila;
    cabezal->ini=cabezal->fin=NULL;
    cabezal->qty=0;
    return cabezal;
}

void liberarPila(TPila p) {
    while (p->qty>0){
        lista_p * borrar = p->ini;
        p->ini=p->ini->sig;
        liberarInfo(borrar->par);
        delete borrar;
        p->qty--;
    }
    p->fin =p->ini;
    delete p;
    p=NULL;
}

nat cantidadEnPila(TPila p) {
    return p->qty;
}

TPila apilar(TInfo info, TPila p) {//?inserta al inicio
    lista_p *nuevo = new lista_p;
    nuevo->par = crearInfo(natInfo(info),realInfo(info));
    nuevo->sig = p->ini;
    if (p->ini!=NULL){
        p->ini = nuevo;
    }else{
        p->ini=p->fin=nuevo;
    }
    p->qty++;
    return p;
}

TInfo cima(TPila p) {
    return p->ini->par;
}

TPila desapilar(TPila p) {
    lista_p *borrar = p->ini;
    p->ini = p->ini->sig;
    liberarInfo(borrar->par);
    delete borrar;
    p->qty--;
    if (p->qty ==0){
        p->fin=p->ini;
    }
    return p;
}
