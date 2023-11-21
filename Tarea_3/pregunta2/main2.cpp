#include "funciones2.hpp"
#define infinito 9999
using namespace std;


int main(){
    ifstream a;
    a.open("miserables.csv",ios::in);
    int v1 = 0; //contador que va asignando el vertice 
    string linea, v;
    getline(a,linea); //me salto la primera linea
    Graphm grafo(77); //inicializo el grafo

    while(getline(a,linea)){  //recorro el excel
        stringstream stream(linea);
        int v2 = 0; //contador que va asignando el vertice 
        getline(stream,v,';');// me salto la primera informacion de cada linea
        while( getline(stream,v,';')){ //recorro la linea para obtener los pesos
                stringstream str;
                int peso;
                str << v;
                str>> peso;
                if(peso != 0){
                    grafo.setEdge(v1,v2,peso); //asigno peso a los vertices
                }  
                v2++;
        }
        v1++;
    }
    a.close();

    //personaje principal
    int pp = personajePrincipal(grafo);
    string nombre = verticeToPersonaje(pp);
    cout << nombre << endl;

    //personaje secundario
    int* D = new int[grafo.n()];
    dijkstraPeso(grafo, D, pp);
    int ps = caminoMayor(D,grafo);
    string nombreps = verticeToPersonaje(ps);
    cout << nombreps << endl;
    delete[] D;

    //Diametro
    
    float diametro = averageDistance(grafo);

    cout << "Diametro: " << diametro << endl;

    //Diametro con peso

    float diametroconpeso = averageWeightedDistance(grafo);

    cout << "Diametro con pesos: " << diametroconpeso << endl;




    return 0;      
}
