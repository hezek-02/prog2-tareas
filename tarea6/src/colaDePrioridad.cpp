/* 5413213 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colaDePrioridad.h"

struct claveValor{
  nat elem;
  double clave;
};
struct _rep_colaDePrioridad {
  claveValor * heap;
  nat limite;
  nat maximo;
  bool invCriterio;
  nat * valuePos;
};

TColaDePrioridad crearCP(nat N) { 
  TColaDePrioridad colaP = new _rep_colaDePrioridad;
  colaP->maximo = 0;
  colaP->limite = N;
  colaP->invCriterio = false;
  colaP->heap = new claveValor[N+1];
  colaP->valuePos = new nat[N+1];
  for (nat i = 0; i < colaP->limite+1; i++){
    colaP->valuePos[i] = 0;
    colaP->heap[i]={0,0};
  }
  return colaP;
}

static TColaDePrioridad filtradoDescendente(TColaDePrioridad cp,nat pos){
  claveValor elemClaveIni = cp->heap[pos];
  nat swap = 2*pos;
  if (cp->invCriterio){
    if (swap+1<=cp->maximo && cp->heap[swap+1].clave > cp->heap[swap].clave)//?prioritario el der
      swap++;
    while (swap <= cp->maximo && elemClaveIni.clave < cp->heap[swap].clave){//?hay al menos un hijo (izq)
      cp->heap[pos]=cp->heap[swap];
      cp->valuePos[cp->heap[pos].elem]=pos;
      pos=swap;
      swap = 2*pos;
      if (swap+1<=cp->maximo && cp->heap[swap+1].clave > cp->heap[swap].clave)//?prioritario el izq
        swap++;
    }
  }else{
    if (swap+1<=cp->maximo && cp->heap[swap+1].clave < cp->heap[swap].clave)//?prioritario el der
      swap++;
    while (swap <= cp->maximo && elemClaveIni.clave > cp->heap[swap].clave){//?hay al menos un hijo (izq)
      cp->heap[pos]=cp->heap[swap];
      cp->valuePos[cp->heap[pos].elem]=pos;
      pos=swap;
      swap = 2*pos;
      if (swap+1<=cp->maximo && cp->heap[swap+1].clave < cp->heap[swap].clave)//?prioritario el izq
        swap++;
    }
  }
  cp->heap[pos]=elemClaveIni;
  cp->valuePos[elemClaveIni.elem]=pos;
  return cp;
}

static TColaDePrioridad filtradoAscendente(TColaDePrioridad cp,nat pos){
  claveValor elemClaveIni = cp->heap[pos];//?pos del elem del heap
  if (cp->invCriterio){
    while (pos > 1 &&  elemClaveIni.clave > cp->heap[pos/2].clave){//?si el hijo posee mayor prioridad
      cp->heap[pos] = cp->heap[pos/2];//?degradar prioridad del padre
      cp->valuePos[cp->heap[pos].elem] = pos;//?actualizar mapa de valores;
      pos/=2;//?subir los niveles
    }
  }else{
    while (pos > 1 &&  elemClaveIni.clave < cp->heap[pos/2].clave){//?si el hijo posee mayor prioridad
    cp->heap[pos] = cp->heap[pos/2];//?degradar prioridad del padre
    cp->valuePos[cp->heap[pos].elem] = pos;//?actualizar mapa de valores;
    pos/=2;//?subir los nivele
    }
  }
  cp->heap[pos]=elemClaveIni;
  cp->valuePos[elemClaveIni.elem]=pos;
  return cp;
}

TColaDePrioridad invertirPrioridad(TColaDePrioridad cp) {
  cp->invCriterio = !cp->invCriterio;
  nat n = cp->maximo;
  for (nat i = n/2; i >= 1; i--)
    cp = filtradoDescendente(cp,i);
  return cp;
}
  
void liberarCP(TColaDePrioridad cp) {
  delete [] cp->heap;
  delete [] cp->valuePos;
  delete cp;
  cp = NULL;
}

TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp) {
  if (elem >= 1 && elem <= cp->limite){//?si elem pertenece al rango
    nat posInHash = cp->valuePos[elem];    
    if (posInHash!=0){//?actualizar valor
      double vPrioridad = cp->heap[posInHash].clave;
      cp->heap[posInHash].clave = valor;
      if (valor > vPrioridad && !cp->invCriterio)//?baja la prioridad
        cp = filtradoDescendente(cp,posInHash);
      else if (!cp->invCriterio)
        cp = filtradoAscendente(cp,posInHash);
      else{
        if (valor > vPrioridad)//?sube la prioridad
          cp = filtradoAscendente(cp,posInHash);
        else 
          cp = filtradoDescendente(cp,posInHash);
      }
    }else{//?insertar, hay lugar vacante porque no se encontro
      cp->maximo++;
      cp->heap[cp->maximo]= {elem,valor};
      cp = filtradoAscendente(cp,cp->maximo);
    }
  }
  return cp;
}

bool estaVaciaCP(TColaDePrioridad cp) {
  return (cp->maximo==0);
}

nat prioritario(TColaDePrioridad cp){
  return (cp->heap[1].elem);
}

TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp){
  if (cp->maximo>0){
    cp->valuePos[cp->heap[1].elem]=0;
    cp->heap[1] = cp->heap[cp->maximo];
    cp->maximo--;
    if (cp->maximo >= 1)
      cp = filtradoDescendente(cp,1);
  }
  return cp;
}

bool estaEnCP(nat elem, TColaDePrioridad cp){
  if (elem>=1 && elem<=cp->limite)
    return (cp->valuePos[elem]!=0);
  else
    return false;
}

double prioridad(nat elem, TColaDePrioridad cp){
  return (cp->heap[cp->valuePos[elem]].clave);
}
