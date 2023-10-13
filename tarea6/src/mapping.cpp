/* 5413213 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/mapping.h"
#include "../include/cadena.h"

struct _rep_mapping {
    TCadena * hash;//*arreglo de punteros
    nat limite;
    nat qty;
};

TMapping crearMap(nat M) {
    TMapping mapa = new _rep_mapping;
    mapa->hash = new TCadena[M];
    mapa->limite=M;
    mapa->qty=0;
    for (nat i = 0; i < M; i++){
        mapa->hash[i] = NULL;
    }
    return mapa;
}

void liberarMap(TMapping map){
    for (nat i = 0; i < map->limite; i++){
        liberarCadena(map->hash[i]);
    }
    delete [] map->hash;
    delete map;
}

TMapping asociarEnMap(nat clave, double valor, TMapping map) {
    map->hash[clave % map->limite] = insertarAlInicio(clave,valor,map->hash[clave % map->limite]);
    map->qty++;
    return map;
}

TMapping desasociarEnMap(nat clave, TMapping map) {
    map->hash[clave % map->limite]= removerDeCadena(clave,map->hash[clave % map->limite]);
    map->qty--;
    return map;
}

bool esClaveEnMap(nat clave, TMapping map) {
    return estaEnCadena(clave,map->hash[clave % map->limite]);
}

double valorEnMap(nat clave, TMapping map) {
    return realInfo(infoCadena(clave,map->hash[clave % map->limite]));
}

bool estaLlenoMap(TMapping map) {
    return (map->qty==map->limite);
}


