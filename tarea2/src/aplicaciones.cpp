/* 5413213 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"
#include "../include/cadena.h"
#include "../include/iterador.h"


TCadena insertarAlFinal(nat natural, double real, TCadena cad) {
  cad = insertarAlInicio(natural,real,cad);
  if(cad != NULL){
   cad = cadenaSiguiente(cad);
  }
  return cad;
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
static void reversoDeIteradorRec(TIterador iter,TIterador rever_iter){
  if(estaDefinidaActual(iter)){
    nat natural = actualEnIterador(iter);//?toma el natural a insertar
    avanzarIterador(iter);//?siguiente de acutal
    reversoDeIteradorRec(iter,rever_iter);//?recursión
    agregarAIterador(natural,rever_iter);//?agrega el ultimo natural de iter, por pila(el ultimo es el primero)
  }
}
TIterador reversoDeIterador(TIterador iter) {
  TIterador rever_iter = crearIterador();
  if (iter == NULL ){
    return NULL;
  }else{
    reiniciarIterador(iter);//?iter->actual apunta al primer elem
    reversoDeIteradorRec(iter,rever_iter);
  }
  return rever_iter;
}




