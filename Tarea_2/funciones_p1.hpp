#include <iostream>
using namespace std;

typedef char tElemLista; //tElemLista se define como tipo char

class lista
{
private:
    typedef struct nodo{  //struct nodo que contiene 
        struct nodo *sig;   // el puntero que apunta al siguiente
        tElemLista dato;    //el dato que almacena el nodo
    }tNodo;
    tNodo *cabeza; //puntero cabeza
    int largo; //largo de la lista
    tNodo *curr; //puntero actual
    tNodo *tail; //puntero tail
    int pos; // posicion actual
public:
    lista(){  //constructor lista, que la inicializa como vacia
        cabeza = NULL;  
        largo = 0;
        curr = NULL;
        tail = NULL;
        pos = 0;
    }
    ~lista(){  //destructor lista, libera memoria
        delete[] cabeza;
        delete[] tail;
        delete[] curr;
    };
    void clear();
    int length();
    void insert(tElemLista a);
    void next();
    void prev();
    void moveToStart();
    void moveToEnd();
    tElemLista getValue();
    void archivoLista(string archivo);
};

void lista::clear(){  //funcion clear que no retorna nada, solo hace los cambios en la lista.
    tNodo *N;
    while(cabeza != NULL){
        N = cabeza;
        if(cabeza == NULL) break;
        cabeza = cabeza->sig;             //crea un nodo auxiliar, y recorre todos los nodos de la lista asignandole cabeza y NULL a cada uno 
        delete N;                           // también les asigna largo 0 y pos 0.
        N = NULL;
    }
    largo = 0;
    cabeza = NULL;
    pos = 0;
    curr = NULL;
}


void lista::archivoLista(string archivo){ 
    //esta funcion recibe un string con el nombre del archivo a crear y recorre la lista agregando cada nodo al archivo de texto.
    moveToStart(); //move to start para asegurar que recorre la lista desde el inicio
    tNodo* N = cabeza;
    ofstream b;
    b.open(archivo, ios::app); //abre el archivo
    while(N != NULL){ // con el while recorre cada nodo de la lista
        b << N->dato;
        N = N->sig;
    }
     b << endl;
    b.close();
};// la funcion no tiene retorno, ya que lo unico que hace es crear o abrir el archivo y trabajar en el.

void lista::insert(tElemLista a){
    //inserto un elemento Y comprueba si va enla cabeza o va en el medio o al final.
    if(cabeza==NULL){  //si la cabeza es null es por que la lista está vacia
        tNodo *N = new tNodo;
        cabeza = N;
        N->dato = a;                // recibe como parametro un elemento tElemLista el cual será el dato almacenado en el nodo a insertar en la lista
        largo++;
        pos = 0;
        curr = N;
        tail = N;
        N->sig = NULL;
        return;
    }
    else if(pos==0 && largo != 1){  //comprueba si el actual es la cabeza pero no es null
    tNodo *N = new tNodo;
    N->dato = a;
    cabeza = N;
    cabeza->sig=curr;
    largo++;
    pos++;
    curr=N;
    return;
    }
    else{ // está en cualquier otra posición 
        tNodo *N = new tNodo;
        N->dato = a;
        N ->sig = curr->sig;
        curr->sig = N;
        if(curr==tail){
            N ->sig = NULL;
            tail->sig = N;
            tail = N;
            }
        largo++;
        pos++;
        curr = N;
        return;
    }
}

void lista::next(){
    if(curr->sig != NULL){  //funcion que no recibe ningun parametro ni retorna nada, solo edita los punteros de la lista en la cual se asigna la funcion para que apunte al nodo siguiente.
        curr = curr->sig;
        pos++;
    }
}

void lista::prev(){
    if(curr != cabeza){
        tNodo * N = cabeza;
        while(N->sig != curr){
            N = N->sig;         //funcion que no recibe ningun parametro ni retorna nada, solo edita los punteros de la lista en la cual se asigna la funcion para que apunte al nodo anterior.
        }                   
        curr = N;
        pos--;
    }
}

void lista::moveToStart(){
    curr = cabeza;   //funcion que no recibe ningun parametro ni retorna nada, solo edita los punteros de la lista en la cual se asigna la funcion para que apunte al inicio de la lista, al nodo cabeza.
    pos = 0;
}

void lista::moveToEnd(){
    curr = tail; //funcion que no recibe ningun parametro ni retorna nada, solo edita los punteros de la lista en la cual se asigna la funcion para que apunte al final de la lista, al nodo tail.
    pos = largo;
}


tElemLista lista::getValue(){
    return curr->dato; //no recibe ningun parametro, la funcion retorna el valor del dato asignado al nodo actual
}