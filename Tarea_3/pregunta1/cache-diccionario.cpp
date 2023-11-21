#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
using namespace std;
#define M 128
#define VACIA ""

class CacheDiccionario{
    public:

        struct Datos{
            string sig;
            int consultas = 0;
        };

        struct ranura{
            string clave;
            Datos info;
        };

        CacheDiccionario(){}
        ~CacheDiccionario(){}
        bool query(string, string&);
        void insert(string, string);
        void querystats(int&, int&, int&);
        void perfstats(int&, int&, int&, int&);
 
        int h(string a){
            int valorASCII, lugar;
            int largo = a.length();
            for(int i=0; i <= largo; i++){
                valorASCII = valorASCII + int(a[i]);
            }
            lugar = valorASCII % M;
            return lugar;
        }

        
        int h2(string b){
            int valorASCII, lugar;
            int largo = b.length();
            for(int i=0; i <= largo; i++){
                valorASCII = valorASCII + (int(b[i])*i);
            }
            lugar = valorASCII % M;
            return lugar;
        }
        

        //Hashing cerrado doble hashing
        int p(string k, int i) {
            return i*h2(k);
        }

        ranura HT[M];
        int total = 0;
        int conocidos = 0;
        int ocupado = 0;
        int desconocidos = 0;
        int accesses = 0;
        int cleanups = 0;
        int misses = 0;
        int hits = 0;

};

/*****
* bool CacheDiccionario::query
******
* Permite consultar por una definición, buscando su termino
******
* Input:
* string termino, string& significado
* .......
******
* Returns:
* bool true, bool false; verdadero si encuentra el termino y falso si no
*****/

bool CacheDiccionario::query(string termino, string& significado){
    string k = termino;
    total++;
    //for (i = 0; HT[pos].clave != VACIA && HT[pos].clave != k; i++)
        //pos = (inicio + p(k, i)) % M; // próxima ranura en la secuencia
    for(int i=0; i < M;i++){
        //int pos = (inicio + p(k, i)) % M; // próxima ranura en la secuencia
        accesses++;
        if (HT[i].clave == k){
            HT[i].info.consultas++;
            significado = HT[i].info.sig;
            if(significado == "") desconocidos++;
            else{conocidos++;}
            cout << "significado: " << significado << endl;
            hits++;
            return true;                              
        }
    }
    significado = "";
    misses++;
    cout << "significado: " << "" << endl;
    return false;
}

/*****
* void CacheDiccionario::insert
******
* Permite insertar una nueva definición, recibiendo como parámetros su termino y significado, en caso de estar llena la tabla hace una limpieza
******
* Input:
* string termino, string significado
* .......
******
* Returns:
* void, no retorna, solo inserta un termino
*****/

void CacheDiccionario::insert(string termino, string significado) {
    string k = termino, s = significado;
    int inicio;
    int pos = inicio = h(k);
    if(ocupado == M){
        for(int i = 0; i < M && ocupado != M/2; i++){
            for(int j = 0; j < M && ocupado != M/2; j++){
                if(HT[j].info.consultas == i){
                    HT[j].info.sig = "";
                    HT[j].info.consultas = 0;
                    HT[j].clave = "";
                    ocupado--;
                }
            }
        }
        cleanups++;
    }  

    for (int i = 0; HT[pos].clave != VACIA && HT[pos].clave != k; i++){ 
        pos = (inicio + p(k, i)) % M;
        abs(pos);    } // próxima ranura en la secuencia
    if (HT[pos].clave == ""){
        HT[pos].clave = k;
        HT[pos].info.sig = s;
        ocupado++;
        return;
    }
    if(HT[pos].clave == termino){
        HT[pos].info.sig = significado;
        return;
    }
}

/*****
* void CacheDiccionario::querystats
******
* Printea las variables total, conocidos y desconocidos
******
* Input:
int& total : variable entera que representa el total de consultas al diccionario
int& conocidos : variable entera que representa la cantidad total de consultas realizadas a términos con significado no vacío
int& desconocidos : variable entera que representa la cantidad total de consultas realizadas a términos con significado vacío
* .......
******
* Returns : tipo void, no retorna 
*****/

void CacheDiccionario::querystats(int& total, int& conocidos, int& desconocidos){
	cout << "total: " << total << endl;
	cout << "conocidos: " << conocidos << endl;
	cout << "desconocidos: " << desconocidos << endl;
} 

/*****
* void CacheDiccionario::perfstats
******
* Printea las variables accesses, cleanups, conocidos y desconocidos
******
* Input:
int& accesses : 
int& hits : variable entera que representa la cantidad de veces que se encontró un término consultado
int& misses : variable entera que representa la cantidad de veces que no se encontró un término consultado
int& cleanups : variable entera que representa la cantidad de veces que se tuvo que limpiar la tabla de hashing
* .......
******
* Returns : tipo void, no retorna
*****/

void CacheDiccionario::perfstats(int& accesses, int& hits, int& misses, int& cleanups){
	cout << "accesses: " << accesses << endl;
	cout << "hits: " << hits << endl;
	cout << "misses: " << misses << endl;
    cout << "cleanups: " << cleanups << endl;
}


