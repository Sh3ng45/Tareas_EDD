#include <iostream>
#include <conio.h>
#include <stdlib.h>
using namespace std;

typedef int tElem;

struct tNodoArbolBin{
    tElem info;
    tNodoArbolBin* izq;
    tNodoArbolBin* der;
};

class RankedABB {
    tNodoArbolBin *arbol; 

    RankedABB(){}; //Constructor RankedABB

    void insert(tElem);
    bool find(tElem);
    int rank(tElem);
};

RankedABB::RankedABB(){ //Implementacion de constructor, el cual inicializa el arbol vacio
    arbol = NULL;
}

tNodoArbolBin *crearNodo(tElem x){
    tNodoArbolBin *nuevo_nodo = new tNodoArbolBin();
    nuevo_nodo->info = x;
    nuevo_nodo->der = NULL;
    nuevo_nodo->izq = NULL;

    return nuevo_nodo;
}

void RankedABB::insert(tElem x){   
    //Dado un elemento x, hace el llamado a insertHelp() para insertar el elemneto x en el ABB 
    return insertHelp(arbol, x);
}

void insertHelp(tNodoArbolBin *&arbol, tElem x){
    //Dado un arbol y un elemento x, se inserta el elemneto x en el arbol
    if(arbol==NULL){ //si el arbol esta vacio
        tNodoArbolBin *nuevo_nodo = crearNodo(x);
        arbol = nuevo_nodo;
    }
    else{ //si el arbol tiene un nodo o mas 
        int valorRaiz = arbol->info; //obtiene el valor de la raiz
        if(x < valorRaiz){ //si el elemento es menor a la raiz, este se inserta en izq
            insertHelp(arbol->izq,x);
        }
        else{ //si el elemento es mayor a la raiz, este se inserta en der
            insertHelp(arbol->der,x);
        }
    }
}

bool RankedABB::find(tElem x) {
    //Dado un elemento x, hace el llamado a findHelp() para comprobar si el elemento se encuentra en el ABB 
    return findHelp(arbol, x); //Se retorna el resultado de findHelp()
}

bool findHelp(tNodoArbolBin *nodo, tElem x) {
    //Dado un arbol y un elemento x, se hace la busqueda de si el elemneto x esta en el arbol
    if (nodo == NULL) return false; // item no está en el ABB
    if (nodo->info == x) return true; // item encontrado
    if (x < nodo->info)
        return findHelp(nodo->izq, x); //recursividad a nodo izquierdo
    else
        return findHelp(nodo->der, x); //recursividad a nodo derecho
}

int RankedABB::rank(tElem x){
    //Dado un elemento x, hace el llamado a rankHelp() para comparar cuantos elementos del ABB son menores o iguales a x
    return rankHelp(arbol, x);
}

int size(tNodoArbolBin* arbol){
    //calcula el tamaño del arbol
    if(arbol != NULL){
        int izq = size(arbol -> izq);
        int der = size(arbol ->der);
        int r = 1;
        return izq + der + r; //retorna el tamaño del arbol
    }
    return 0;
}

int b = 0;
int& a = b;
void recorrerABB(tNodoArbolBin *arbol, int *arr, int &a){
    //recorre el arbol dado y al mismo tiempo guarda cada elemento del nodo del arbol que visita en un arreglo
    if(arbol == NULL){
        return;
    }
    else{
        arr[a] = arbol -> info;
        a++;
        recorrerABB(arbol->izq, arr, a);
        recorrerABB(arbol->der, arr, a);
    }
    a = 0;
}

int rankHelp(tNodoArbolBin *arbol, int x){
    //Dado un arbol y un elemento x, se compara todos los elementos del arbol menores o iguales a x
    int cont = 0; 
    int* arr = new int[size(arbol)]; //se crea un arreglo del tamaño de la cantidad de elementos del arbol para pasarlo como parametro a la funcion inOrden() 
    recorrerABB(arbol, arr, a);
    if(arbol == NULL){
        return cont; //si el arbol es vacio, se retorna el contador en 0
    }
    else{
        for(int i=0; i<size(arbol); i++){
            if(arr[i]<=x) cont++;
        }
    }
    return cont; //se retorna un contador con la cantidad de elementos menores o iguales a x
    delete[] arr; //se libera la memoria del arreglo de los elementos del arbol
}
