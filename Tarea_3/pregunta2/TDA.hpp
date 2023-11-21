#include <iostream>
#include <assert.h>
using namespace std;
#define NOVISITADO 0
#define VISITADO 1

class Graphm{
    private:
        int numVertex, numEdge; 
        int **matrix; 
        int *mark; 
    public:
        Graphm(int numVert) 
        { Init(numVert); }
        ~Graphm() { 
        delete [] mark; 
        for (int i=1; i<numVertex; i++)
            delete [] matrix[i];
        delete [] matrix;
        }
        void Init(int n) { 
            int i;
            numVertex = n;
            numEdge = 0;
            mark = new int[n]; 
            for (i=0; i<numVertex; i++)
                mark[i] = NOVISITADO;
            matrix = (int**) new int*[numVertex]; 
            for (i=0; i<numVertex; i++){
                matrix[i] = new int[numVertex];
                for (int j=0; j<numVertex; j++)
                    matrix[i][j] = 0;}
        }
        int n() { return numVertex; } 
        int e() { return numEdge; } 

        int first(int v) {
            for (int i=0; i<numVertex; i++)
                if (matrix[v][i] != 0) return i;
            return numVertex; 
        }

        int next(int v, int w) {
            for(int i=w+1; i<numVertex; i++)
                if (matrix[v][i] != 0)
                    return i;
            return numVertex; 
        }

        void setEdge(int v1, int v2, int peso) {
            if (matrix[v1][v2] == 0) numEdge++;
            matrix[v1][v2] = peso;
            //matrix[v2][v1] = peso;

        }

        void delEdge(int v1, int v2) { 
            if (matrix[v1][v2] != 0) numEdge--;
            matrix[v1][v2] = 0;
        }

        bool isEdge(int i, int j) 
        { return matrix[i][j] != 0; }

        int weight(int v1, int v2) { return matrix[v1][v2]; }
        int getMark(int v) { return mark[v]; }
        void setMark(int v, int val) { mark[v] = val; }
        void resetnumEdge(){numEdge = 0;}
        void print(){
            for(int i=1; i<numVertex; i++){
                for(int j=1;j<numVertex; j++){
                    cout<<matrix[i][j]<<" ";
                }
                cout<<endl;
            }
        }
        void unMark(){
            for (int i=0; i<numVertex; i++)
                setMark(i,NOVISITADO);
        }
};
