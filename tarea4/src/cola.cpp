/* 5413213 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/cola.h"

struct lista_c{
    TInfo par;
    lista_c *ant;
};

struct _rep_cola {
    lista_c *ini,*fin;
    nat qty;  
};

TCola crearCola() {
    TCola cabezal = new _rep_cola;
    cabezal->ini=cabezal->fin=NULL;
    cabezal->qty=0;
    return cabezal;
}

void liberarCola(TCola c) {//?Borra desde fin a ini
    while (c->qty>0){
        lista_c * borrar = c->fin;
        c->fin=c->fin->ant;
        liberarInfo(borrar->par);
        delete borrar;
        c->qty--;
    }
    c->ini =c->fin;
    delete c;
    c=NULL;
}

nat cantidadEnCola(TCola c) {
    return c->qty;
}

TCola encolar(TInfo info, TCola c) {//?insertoAlInicio
    lista_c * nuevo = new lista_c;
    nuevo->par = crearInfo(natInfo(info),realInfo(info));
    nuevo->ant = NULL;
    if (c->fin !=NULL){//?elementos en cola
        c->ini->ant = nuevo;
        c->ini = nuevo;
    }else{
        c->fin=c->ini=nuevo;
    }
    c->qty++;
    return c;
}

TInfo frente(TCola c) {
    return c->fin->par;
}

TCola desencolar(TCola c) {
    lista_c *borrar = c->fin;
    c->fin = c->fin->ant;
    liberarInfo(borrar->par);
    delete borrar;
    c->qty--;
    if (c->qty ==0){
        c->ini=c->fin;
    }
    return c;
}
