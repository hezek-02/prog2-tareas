/* 5413213 */
/*
  Módulo de implementación de `asignacion_residencias'.

  Laboratorio de Programación 3.
  InCo-FIng-UDELAR
 */

#include "../include/asignacion_residencias.h"
#include "../include/pila.h"
#include <cstddef>

Asignacion asignarResidencias(nat m, nat* C, nat n, nat** hPrefs, nat** ePrefs){
  Asignacion emparejamiento = crear_asignacion();
  Pila hFrees= crear_pila();//*pila de hospitales lbres
  nat * next = new nat[m];//*arreglo de preferencia siguiente
  int * current = new int[n];//*arreglo de emparejamiento actual de e
  nat ** ranking = new nat*[n];//*matriz ranking

  for (nat hos = 0; hos < m ; hos++){//?recorrer los hospitales para setear estructuras
    apilar(hos,hFrees);//?pila con hospitales con cupo
    next[hos]=0;//?prioritario siguiente
  }

  for (nat est = 0; est < n; est++){//?recorrer estudiantes para setear estructuras
    current[est]=-1;//?pareja actual de estudiante
    ranking[est] = new nat[m];//?setear matriz dinamica segunda componente
    nat pref = 0;
    for (nat hos = 0; hos < m; hos++){//?recorrer hospitales
      ranking[est][ePrefs[est][pref]] = pref;//?segun el preferente menor el valor de pref
      pref++;
    }
  }
  nat qty=0;
    while (!es_vacia_pila(hFrees)){
      nat hAct = cima(hFrees);
      nat estudianteAct = hPrefs[hAct][next[hAct]];
      if (current[estudianteAct]==-1){//?no tenia pareja
        qty++;
        current[estudianteAct]=hAct;
        next[hAct]++;
        C[hAct]--;
        if (C[hAct]==0)
          desapilar(hFrees);
      }else{//?ya tenia pareja
        if (ranking[estudianteAct][current[estudianteAct]]>ranking[estudianteAct][hAct]){//?prefiere al actual
          nat hAnt = current[estudianteAct];
          current[estudianteAct]=hAct;//?actualizar pareja actual
          next[hAct]++;//?avanzar preferencia del hospital
          C[hAct]--;
          if (C[hAct]==0)
            desapilar(hFrees);
          C[hAnt]++;//*se libera un cupo
          apilar(hAnt,hFrees);//*hospital libre posee cupo
        }else
          next[hAct]++;
      }
    }
    nat est = 0;
    while(qty>0){
      if(current[est]!=-1){
        nat hos = current[est];
        insertar_par({est,hos},emparejamiento);
        qty--;
      }est++;  
    }
    

    destruir_pila(hFrees);
    delete [] current;
    delete [] next;
    for (nat est = 0; est < n; est++)//?eliminar matriz
      delete [] ranking[est];
    delete [] ranking;
    
    return emparejamiento; // se debe retornar algo de tipo asignacion
}
