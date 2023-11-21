#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include "funciones_p1.hpp"
using namespace std;  
int main(){
    string linea;
    lista L; //lista L para almacenar las lineas del texto de entrada
    lista Final; // lista Final para almacenar las lineas del texto de salida
    ifstream a; //archivo de entrada
    ofstream b; //archivo de salida
    a.open("teclado-entrada.txt",ios::in); //abre el archivo de entrada
    b.open("teclado-salida.txt", ios::out); //abre el archivo de salida con un ios::out para que en el caso de probar con otro archivo de entrada el archivo de salida esté vacio.
    b.close();
    while(!a.eof()){ //recorro el archivo hasta que llegue al final
        int len = 0;
        L.clear(); // reinicializo la lista al repetirse el ciclo, para eliminar los datos anteriores
        getline(a,linea);  //guardo la linea en el string linea
        len = linea.length(); //largo de la linea para recorrerla mas tarde
        L.moveToStart();
        for(int i = 0; i < len; i++){ //for para recorrer el string linea
            L.insert(linea[i]); //e insertar en la lista cada char del string como un nodo
        }
        L.moveToStart(); //me muevo al inicio de la lista para trabajar con ella desde el nodo cabeza.
        Final.clear(); //reinicializo la lista Final

        for(int i = 0; i < len; i++){ //for para recorrer la lista L y dependiendo del condicional agrego a lista Final
            char h = L.getValue(); //en el char h guardo el valor del Nodo actual de L
            if (h=='<'){  // si el char es < 
                L.next(); // avanzo en la lista L por que no quiero agregar ese caracter
                Final.prev();} //y en la lista Final me muevo uno atrás
            else if (h=='>'){ 
                L.next(); // avanzo en la lista L por que no quiero agregar ese caracter
                Final.next();}// avanzo en la lista L por que no quiero agregar ese caracter
            else if (h=='['){ 
                Final.moveToStart();// debido al "[" me muevo al inicio de la lista Final
                L.next();} // avanzo en la lista L por que no quiero agregar ese caracter
            
            else if (h==']'){
                Final.moveToEnd(); // debido al "]" me muevo al final de la lista Final
                L.next();// avanzo en la lista L por que no quiero agregar ese caracter
                }
            else{
                Final.insert(h); //el caracter es valido, por lo que lo inserto en la lista Final
                L.next(); //apunto al siguiente para continuar con el for
            }
        }
        Final.archivoLista("teclado-salida.txt");
    } 
    a.close(); //cierro el archivo cuando termino de trabajar con el.
    Final.~lista(); //destructor de la lista para liberar la memoria
    L.~lista(); //destructor de la lista para liberar la memoria
    return 0;
};