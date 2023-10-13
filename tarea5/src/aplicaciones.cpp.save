/* 5413213 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"
#include "../include/mapping.h"
#include <math.h>

int nivelesAvl(TAbb abb,bool &res){
  if (abb == NULL || !res)
    return 0;
  else{ 
    int nIzq =nivelesAvl(izquierdo(abb),res) + 1;
    int nDer =nivelesAvl(derecho(abb),res) + 1; 
    if(abs(nIzq-nDer) > 1)
      res=false;
    if (nIzq>nDer)
      return nIzq;
    else
      return(nDer);
  }
}
bool esAvl(TAbb abb) {
  bool res=true;
  nivelesAvl(abb,res);
  return (res);
  
}

static TAbb avlFibonacci(nat h,int &qtyNodosIzq){
  TAbb avl = crearAbb();
  if (h==1){//?Cb
    avl = insertarEnAbb(crearInfo(qtyNodosIzq+1,0.0),avl);
    qtyNodosIzq++;
  }else if(h>1){
    TAbb subI = avlFibonacci(h-1,qtyNodosIzq);
    qtyNodosIzq++;
    nat root = qtyNodosIzq;
    avl = consAbb(crearInfo(root,0.0),subI,avlFibonacci(h-2,qtyNodosIzq));
  }
  return avl;
}

TAbb avlMin(nat h) {
  int qtyNodos = 0;
  return avlFibonacci(h,qtyNodos);
}

TCadena filtradaOrdenada(TCadena cad, TIterador it) {
  reiniciarIterador(it);
  TCadena res=crearCadena();
  if (cad==NULL || !estaDefinidaActual(it))
    return res;
  nat qtyCad = cantidadEnCadena(cad);
  TMapping mapa = crearMap(qtyCad);
  for (nat i = 0; i < qtyCad; i++){//?setear mapping
    nat clave = natInfo(primeroEnCadena(cad));
    if (!esClaveEnMap(clave,mapa))
      mapa = asociarEnMap(clave,realInfo(primeroEnCadena(cad)),mapa);
    else{
      double valorAnt =  valorEnMap(clave,mapa);
      mapa = desasociarEnMap(clave,mapa);
      mapa = asociarEnMap(clave,valorAnt + realInfo(primeroEnCadena(cad)),mapa);
    }
    cad = cadenaSiguiente(cad);
  }
  while (estaDefinidaActual(it)){
    nat claveIter =actualEnIterador(it);
    if (esClaveEnMap(claveIter,mapa))
      res = insertarAlFinal(claveIter,valorEnMap(claveIter,mapa),res);
    avanzarIterador(it);
  }
  liberarMap(mapa);
  return res;
}

bool estaOrdenada(TCadena cad) {
  nat largo_cad = cantidadEnCadena(cad);
  if (largo_cad <= 1){
    return true;
  }else{
    nat i = 1;
    while (i<largo_cad && natInfo(primeroEnCadena(cad))<natInfo(primeroEnCadena(cadenaSiguiente(cad))) ){
      i++;
      cad=cadenaSiguiente(cad);
    }
    return (i==largo_cad);
  }  
}

TCadena mezclaCadenas(TCadena cad1, TCadena cad2) {
  TCadena res = crearCadena();
  nat largoC1 = cantidadEnCadena(cad1);
  nat largoC2 = cantidadEnCadena(cad2);
  if (cad1 == NULL && cad2 == NULL){
    return res;
  }else{
    while (largoC1 > 0 && largoC2 >0){
      if (natInfo(primeroEnCadena(cad1))<natInfo(primeroEnCadena(cad2))){
        res = insertarAlFinal(natInfo(primeroEnCadena(cad1)),realInfo(primeroEnCadena(cad1)),res);
        largoC1--;
        cad1 = cadenaSiguiente(cad1);
      }
      else if (natInfo(primeroEnCadena(cad1))>natInfo(primeroEnCadena(cad2))){
        res = insertarAlFinal(natInfo(primeroEnCadena(cad2)),realInfo(primeroEnCadena(cad2)),res);
        largoC2--;
        cad2 = cadenaSiguiente(cad2);
      }else{
        res = insertarAlFinal(natInfo(primeroEnCadena(cad1)),realInfo(primeroEnCadena(cad1)),res);
        largoC1--;
        cad1 = cadenaSiguiente(cad1);
        largoC2--;
        cad2 = cadenaSiguiente(cad2);
      }
    }
    while(largoC1>0){
      res = insertarAlFinal(natInfo(primeroEnCadena(cad1)),realInfo(primeroEnCadena(cad1)),res);
      largoC1--;
      cad1 = cadenaSiguiente(cad1);
    }
    while(largoC2>0){
      res = insertarAlFinal(natInfo(primeroEnCadena(cad2)),realInfo(primeroEnCadena(cad2)),res);
      largoC2--;
      cad2 = cadenaSiguiente(cad2);
    }
   return res; 
  }
}

static TAbb balanceo(TInfo *arreglo,nat cotInf,nat n){
  TAbb res = crearAbb();
  if (n>cotInf){
    nat medio =(n-1+cotInf)/2;
    res = consAbb(copiaInfo(arreglo[medio]),balanceo(arreglo,cotInf,medio),balanceo(arreglo,medio+1,n));//?PI
  }
  return res;
}

TAbb crearBalanceado(TInfo *arreglo, nat n) {
  if (n==0){
    return NULL;
  }else{
    nat cotInf = 0;
    nat medio =(n-1+cotInf)/2;
    TAbb resD = balanceo(arreglo,medio+1,n);
    TAbb resI = balanceo(arreglo,cotInf,medio); 
    TAbb res = consAbb(copiaInfo(arreglo[medio]),resI,resD);
    return res;
  }
}

TAbb unionAbbs(TAbb abb1, TAbb abb2) {
  TCadena cad1 = linealizacion(abb1);
  TCadena cad2 = linealizacion(abb2);
  TCadena cadenaDefinitiva = mezclaCadenas(cad1,cad2);
  liberarCadena(cad1);
  liberarCadena(cad2);
  nat largoA = cantidadEnCadena(cadenaDefinitiva);
  TInfo arrDefinitivo[largoA];
  for (nat i = 0; i < largoA; i++){
    arrDefinitivo[i] = primeroEnCadena(cadenaDefinitiva);
    cadenaDefinitiva = cadenaSiguiente(cadenaDefinitiva);
  }
  TAbb abbDefinitivo = crearBalanceado(arrDefinitivo,largoA);
  liberarCadena(cadenaDefinitiva);//?elimina tmb la info del arreglo
  return abbDefinitivo;
}

TCola ordenadaPorModulo(nat p, TCadena cad) {
  TCola cRes = crearCola();
  if (cad == NULL){
    return cRes;
  }else{
    nat largoCad = cantidadEnCadena(cad);
    TCadena arr[p];
    for (nat j = 0; j < p; j++){//?defino el arr de cads
      arr[j]=crearCadena();
    }
    for (nat i = 0; i < largoCad; i++){//?inserto los elems del arreglo de cads
      nat natural = natInfo(primeroEnCadena(cad));
      double real = realInfo(primeroEnCadena(cad));
      nat pos = natural % p;
      arr[pos] = insertarAlFinal(natural,real,arr[pos]);
      cad = cadenaSiguiente(cad);
    }
    nat cont = 0;
    while (cont<p){
      if (arr[cont]!=NULL){
        cRes = encolar(primeroEnCadena(arr[cont]),cRes);
        arr[cont] = removerPrimero(arr[cont]);
      }else
        cont++;
    }
    return cRes;
  } 
}  

TPila menoresQueElResto(TCadena cad, nat cantidad) {
  TPila pRes = crearPila();
  if (cad == NULL){
    return pRes;
  }else{
    pRes = apilar(primeroEnCadena(cad),pRes);
    cad = cadenaSiguiente(cad);
    cantidad --;
    while (cantidad > 0){
      if (natInfo(primeroEnCadena(cad)) > natInfo(cima(pRes))){
        pRes = apilar(primeroEnCadena(cad),pRes); 
      }else{ 
        while ( cantidadEnPila(pRes) > 0 && natInfo(primeroEnCadena(cad)) <= natInfo(cima(pRes))){
          pRes = desapilar(pRes);
          
        }
        pRes = apilar(primeroEnCadena(cad),pRes);
      }
      cantidad--;
      cad = cadenaSiguiente(cad);
    }
    
    return pRes;
  }
}

static void linearRec(TAbb abb,TCadena &cad){//?por parametro modifica la cadena directamente
  if(esVacioAbb(abb)){
    return;
  }
  linearRec(derecho(abb),cad);//?recorrer ramas derechas
  cad = insertarAlInicio(natInfo(raiz(abb)),realInfo(raiz(abb)),cad);//?insertar las ramas segun orden descendente
  linearRec(izquierdo(abb),cad);//?recorrer ramas izq
}

TCadena linealizacion(TAbb abb) {
  TCadena cad = crearCadena();//?cad nula
  linearRec(abb,cad);//?proc rec
  return cad;
}

static void printAuxAbb(TAbb abb, nat profundidad){
  if (abb != NULL){
    profundidad++;
    printAuxAbb(derecho(abb),profundidad);
    profundidad--;
    for (nat i = 0; i < profundidad; i++)
    {
      printf("-");
    }
    imprimirInfo(raiz(abb));
    printf("\n");
    profundidad++;
    printAuxAbb(izquierdo(abb),profundidad);
  }
}

void imprimirAbb(TAbb abb) {
  nat profundidad = 0;
  printAuxAbb(abb,profundidad);
}

nat nivelesPerfectos(TAbb abb,bool &res){
  if (abb == NULL){
    return 0;
  }else if(res && ((izquierdo(abb) !=NULL && derecho(abb) !=NULL) || (izquierdo(abb)==NULL && derecho(abb)==NULL))){
    return(nivelesPerfectos(izquierdo(abb),res)+nivelesPerfectos(derecho(abb),res) + 1 );
  }else{
    res = false;
    return 0;
  }
}
bool esPerfecto(TAbb abb) {
  if (abb == NULL){
    return true;
  }else{
    bool res = true;
    int pI =nivelesPerfectos(izquierdo(abb),res);
    int pD =nivelesPerfectos(derecho(abb),res);
    return (res && pI==pD);
  }
}

TAbb menores(double limite, TAbb abb){
  TAbb res;
  if (abb == NULL){//?CB
    res = NULL;
  }else{
    TAbb res_left = menores(limite,izquierdo(abb));//?filtrar subarbol izq
    TAbb res_right = menores(limite,derecho(abb));//?filtrar subarbol der
    if(realInfo(raiz(abb)) < limite ){//?condicion de filtro
      res = consAbb(copiaInfo(raiz(abb)),res_left,res_right);//?construccion de menores
    }else if (res_left == NULL){//?condicion de ancestros filtro
      res = res_right;
    }else if (res_right == NULL){
      res = res_left;
    }else{//?los subarboles cumplen der e izq entonces
      TInfo res_root = copiaInfo(mayorEnAbb(res_left));//?copiar info del maxclave(subA izq)
      res_left = removerDeAbb(natInfo(res_root),res_left);//?eliminar maxClave (subA izq)
      res = consAbb(res_root,res_left,res_right);
    }
  }
  return res;
}

static void camAscRec(nat clave, nat &k, TAbb abb,TIterador iter) {
  if (clave > natInfo(raiz(abb))){//?condicion de filtro
    camAscRec(clave,k,derecho(abb),iter);//?recorre subA der
  }else if (clave < natInfo(raiz(abb))){
    camAscRec(clave,k,izquierdo(abb),iter);//?recorre subA izq
  }
  if (k > 0){
    k--;//?modifica el contador globalmente independiente de su valor en recursion local
    nat elem = natInfo(raiz(abb));
    agregarAIterador(elem,iter);
  }  
}

TIterador caminoAscendente(nat clave, nat k, TAbb abb) {
  TIterador iter = crearIterador();
  if (k==0){
    return iter;//?ahorrar procesamiento
  }
  else{
    camAscRec(clave,k,abb,iter);//?auxrec
    return iter;
  }
}

static void impPalabrasCortasAuxRec(nat k, TPalabras palabras,ArregloChars words,nat largo){
  if (k>0){
    if (letra(palabras) == '\0'){//?CB
      words[largo] = '\0';
      printf("%s\n", words);
    }else{//?es letra valida
      words[largo] = letra(palabras);
      impPalabrasCortasAuxRec(k-1,subarboles(palabras),words,largo+1);//?pasarle el pH como siguiente en la cadena 
    }if (siguientes(palabras) != NULL){//?verifica el nivel de hermanos 
      impPalabrasCortasAuxRec(k,siguientes(palabras),words,largo);
    }
  }  
}

void imprimirPalabrasCortas(nat k, TPalabras palabras) {//?con largo y dado un AG
  if (palabras == NULL){
    return;
  }
  char concatenacion_pal[k+1];//?para el final de linea;
  impPalabrasCortasAuxRec(k+1,subarboles(palabras),concatenacion_pal,0);
}

static void FinPreRec(ArregloChars prefijo,TPalabras palabras,TPalabras &res,nat indx_char){
  if (prefijo[indx_char] != '\0'){//?se llega al fina de linea  
    if (prefijo[indx_char] == letra(palabras)){//?PI si la primera letra es igual a la primera del arbol (Ph)
      res=palabras;
      FinPreRec(prefijo,subarboles(palabras),res,indx_char+1);//?recorrer demas hijos
    }else if (siguientes(palabras) !=NULL){//?si el hijo(la letra) no es igual a la letra del prefijo que le sigue
      FinPreRec(prefijo,siguientes(palabras),res,indx_char);//?probar con sus hermanos
    }else{
      res=NULL;//?si ninguno de sus hermanos cumple con la letra entonces no existe ese prefijo en el arbol
    }
  }
}

TPalabras buscarFinPrefijo(ArregloChars prefijo, TPalabras palabras) {
  TPalabras res = NULL;//?auxiliar, subarbol que comparte mem con palabras a retornar
  if (palabras == NULL){
    return res;
  }
  FinPreRec(prefijo,subarboles(palabras),res,0);
  return res;
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

