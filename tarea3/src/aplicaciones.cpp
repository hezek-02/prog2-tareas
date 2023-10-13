/* 5413213 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"

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

static nat cantNodosAbb(TAbb abb){
  if(abb == NULL){
    return 0;
  }
  return (cantNodosAbb(derecho(abb)) + cantNodosAbb(izquierdo(abb)) + 1 );
}

static nat altura(TAbb abb){
  if (abb == NULL){
    return 0;
  }
  nat prof_izq = altura(izquierdo(abb)) + 1;
  nat prof_der = altura(derecho(abb)) + 1;
  if (prof_der > prof_izq){
    return prof_der;
  }
  else{
    return prof_izq;
  }
    
}

bool esPerfecto(TAbb abb) {//?dada la altura-1 y  la cant de elem se puede determinar
  nat qty = altura(abb);
  nat multi = 1;
  for (nat i = 0; i < qty; i++)//?2^altura
  {
    multi = 2*multi;
  }

  return (cantNodosAbb(abb) == multi-1);
}

TAbb menores(double limite, TAbb abb) {
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
