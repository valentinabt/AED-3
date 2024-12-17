
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <list>
#include <tuple>
#include <unordered_map>

using namespace std ;

unordered_map<long long int,long long int> conjA ;
unordered_map<long long int,long long int> conjB ;
//dfs visto en la practica del turno tarde + idea de chequear bipartitud pero usandola para bipartir el grafo o "pintarlo"
void dfsBipartir(long long int s,unordered_map<long long int,vector<long long int>>& aristas, unordered_map<long long int,bool>& visitados,unordered_map<long long int,int>& colores) {

   // if (visitados[s])
     //return;
    //else { 
        visitados[s] = true;
        // procesar s
        for (int i = 0 ;i< aristas[s].size();i++) {
            if(colores[aristas[s][i]] ==-1 ){
                colores[aristas[s][i]] = 1 - colores[s] ;
            }
            if(colores[aristas[s][i]] ==0) {
                conjA[aristas[s][i]] = 1 ;
            }
             if(colores[aristas[s][i]] ==1) {
                conjB[aristas[s][i]] = 1 ;
            }

            if(!visitados[aristas[s][i]]){
            dfsBipartir(aristas[s][i],aristas,visitados,colores);
    }}

    //}

}

  


  


int main() {
long long int nodosDelArbol; 
long long int contador;
unordered_map<long long int,vector<long long int>> aristas ;
//unordered map es un diccionario.Utilice esta estructura porque sino no puedo indexar sobre los vertices,necesito un indice.

cin >> nodosDelArbol; 
contador = nodosDelArbol ;
long long int primerNodo ;
while(contador-1 >0) {   
    
    long long int v;
    long long int u ;
    cin >> v;
    cin >> u;
    primerNodo = v ;
    aristas[u].push_back(v);
    aristas[v].push_back(u) ;
    contador -- ;

    }  
 unordered_map<long long int,bool> visitados ;
    for(pair<long long int,vector<long long int>> vertices : aristas) {
        visitados[vertices.first] = false ;
    }
    unordered_map<long long int,int> colores ;
    for(pair<long long int,vector<long long int>> vertices : aristas) {
        colores[vertices.first] = -1 ;
    }
    colores[primerNodo] = 0 ; //si esta pintado de 0 va en A,si está de 1 va en B.Si no esta pintado no va en niguno
    conjA[primerNodo] = 1 ;
    
  dfsBipartir(primerNodo,aristas,visitados,colores) ;
  long long int res ;
  res = (conjA.size()*conjB.size())-(nodosDelArbol-1) ; 
    cout << res << endl ;
    return 0;
     
}
//caso de falla : 10,20,30,40,50,60,70,80,90,100,110.Si las aristas eran :
/* 10 20,10 30,20 40,20 50,30 60,30 70,50 80,60 90,70 100 y 70 110 depende del orden en que las pusiera pintaba del mismo color una arista completa
o reasignaba colores,entonces o tenia conjuntos que tenian elementos iguales,o bien habia una arista que tenia elementos del mismo conjunto.





*/