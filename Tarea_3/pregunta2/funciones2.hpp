#include "TDA.hpp"
#include <limits>
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <stdio.h>
#define infinito 9999
using namespace std;

/*****
* int minVertex
******
* Retorna el vertice con costo minimo
******
* Input:
* Graphm& G, int* D
* .......
******
* Returns:
* int v, vertice con costo minimo
*****/

int minVertex(Graphm& G, int* D) {
    int i, v = -1;
    for (i=0; i<G.n(); i++)
        if (G.getMark(i) == NOVISITADO) { v = i; break; }
    for (i++; i<G.n(); i++)
        if ((G.getMark(i) == NOVISITADO) && (D[i] < D[v]))
            v = i; 
    return v;
}


/*****
* int grado
******
* esta funcion recorre los vertices para obtener el grado del vertice
******
* Input:
* int v: tipo entero vertice del cual quiero obtener su grado
* Graphm& G : Grafo tipo Graphm del tda
* .......
******
* Returns:
* tipo entero, numero que corresponde al grado del vertice
*****/
int grado(int v, Graphm& G){
    int g = 0;
    for(int w = G.first(v); w < G.n() - 1; w = G.next(v,w)) g++;
    return g;
}                             

/*****
* void dijkstraPeso
******
* Aplica el algoritmo dijkstra, el cual consiste en procesar los
vértices del grafo por orden de distancia al vértice origen s
******
* Input:
Graphm& G : Grafo tipo Graphm del tda
int* D : Arreglo de las distancias entre el vertice s y los demás
int s : Vertice origen tipo entero
* .......
******
* Returns : tipo void, no retorna
*****/

void dijkstraPeso(Graphm& G, int* D, int s) {
    int i, v, w;
    for(i = 0; i <G.n(); i++){
        D[i] = infinito;
    }
    D[s]= 0;
    for (i = 0; i<G.n(); i++) { 
        v = minVertex(G, D);
        if (D[v] == infinito) return; 
        G.setMark(v, VISITADO);
        for (w=G.first(v); w<G.n(); w = G.next(v,w)){
            if (D[w] > (D[v] + G.weight(v, w))){
                D[w] = D[v] + G.weight(v, w);}}
    }
}


/*****
* void dijkstraSinPeso
******
* Busca los caminos minimos pero sin los pesos asociados
******
* Input:
* Graphm& G, int* D, int s
* .......
******
* Returns:
* Void, no retorna, modifica arreglo D
*****/
void dijkstraSinPeso(Graphm& G, int* D, int s) {
    int i, v, w, peso;
    for(i = 0; i <G.n(); i++){ 
        D[i] = infinito;
    }
    D[s] = 0;
    for (i = 1; i<G.n(); i++) { 
        v = minVertex(G, D);
        if (D[v] == infinito) return; 
        G.setMark(v, VISITADO);
        for (w=G.first(v); w<G.n(); w = G.next(v,w)){ 
            peso = G.weight(v, w);
            if(peso != 0) peso = 1;
                if (D[w] > (D[v] + peso)){
                    D[w] = D[v] + peso;}}
    }
}

/*****
* int NumCombinatorio
******
* Calcula la combinatoria entre 2 numeros
******
* Input:
* int n y int r: 2 numeros de tipo entero
* .......
******
* Returns:
* int, me retorna el resultado de la combinatoria entre esos 2 numeros
*****/

int NumCombinatorio(int n, int r){
    int i, c = 1;
    for (i = 1; i <= r; i++){
        c = c*(n - i + 1) / i;
    }
    return c;
}


/*****
* int personajePrincipal
******
* recorriendo los vertices obtiene el grado de cada vertice para asi encontrar a que vertice le corresponde el mayor grado.
******
* Input:
* Graphm& G : recibe un grafo
* .......
******
* Returns:
* int, me retorna  un vertice tipo int, el cual corresponde al vertice del personaje principal
*****/
int personajePrincipal(Graphm& G){
    int pp;
    int mayor = 0;
    for(int i = 0; i<G.n(); i++){
        int g = grado(i,G);
        if(mayor < g){
            mayor = g;
            pp = i;
        }
    }
    return pp;
}

/*****
* string verticeToPersonaje
******
* esta funcion recorre el archivo miserables id to name, para que con un contador encuentre que nombre le corresponde al vertice
******
* Input:
* int V, un vertice tipo entero
* .......
******
* Returns:
* string, me retorna el nombre al que corresponde el vertice entregado 
*****/
string verticeToPersonaje(int v){
    ifstream a;
    string linea, nombre = "", id;
    int vertice = 0;
    a.open("miserables_id_to_names.csv",ios::in);
    getline(a,linea);
    while(getline(a,linea)){
        stringstream stream(linea);
        getline(stream,id,',');
        getline(stream,nombre,',');
        if(vertice == v)return nombre;
        vertice++;
    }
    a.close();
    return "error";
}

/*****
* int caminoMayor
******
* esta funcion recorre el arreglo D, el cual contiene los caminos mas cortos entre vertices, esto para obtener a que vertice le corresponde el camino mas largo.
******
* Input:
* int* D, Graphm& G
* .......
******
* Returns:
* int, me retorna el vertice al cual le corresponde el camino mayor
*****/
int caminoMayor(int* D, Graphm& G){
    int mayor = 0;
    int cont = 0;
    for(int i=0; i<G.n(); i++){
        if(D[i] > mayor){
            mayor = D[i];
            cont = i;}
    }
    return cont;
}

/*****
* float averageDistance
******
* esta funcion recorre los vertices para obtener el grado del vertice
******
* Input:
* int v: tipo entero vertice del cual quiero obtener su grado
* Graphm& G : Grafo tipo Graphm del tda
* .......
******
* Returns:
* tipo entero, numero que corresponde al grado del vertice
*****/

float averageDistance(Graphm& G){
    float sumatoriaDijkstra = 0;
    for(int i = 0; i<G.n(); i++){
        int* D = new int[G.n()];
        G.unMark(); // marca vertices como no visitados
        dijkstraSinPeso(G,D,i);
        for(int i= 0; i < G.n(); i++){
            sumatoriaDijkstra = sumatoriaDijkstra + D[i];
        }
        delete[] D;
    }
    float c = NumCombinatorio(G.n(),2);
    float resultado = sumatoriaDijkstra/c;
    return resultado/2;
}

/*****
* float averageWeightedDistance
******
* para un grafo con pesos G = (V, E, w) la longitud de
camino promedio (con pesos) está dada por la distancia promedio con pesos
******
* Input:
* Graphm& G
* .......
******
* Returns:
* float resultado, resultado de division
*****/

//averageWeightedDistance(G)
float averageWeightedDistance(Graphm& G){
    float sumatoriaPesos = 0;
    float sumatoriaDijkstra = 0;
    for(int i = 0; i<G.n(); i++){
        for(int w = G.first(i); w < G.n() - 1; w = G.next(i,w)){
            sumatoriaPesos = sumatoriaPesos + G.weight(i,w);
        }
    }
    for(int i = 0; i<G.n(); i++){
        int* X = new int[G.n()];
        G.unMark(); //marca vertices como no visitados
        dijkstraPeso(G,X,i);
        for(int i= 0; i < G.n(); i++){
            sumatoriaDijkstra = sumatoriaDijkstra + X[i];
        }
        delete[] X;
    }
    float sum = sumatoriaDijkstra/2;
    float sumpesos = sumatoriaPesos/2;
    float resultado = sum/sumpesos;

    return resultado;
} 




