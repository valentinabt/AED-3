#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <list>
#include <tuple>
#include <unordered_map>
#include<climits>
#include<queue> 
#include<functional>

//pruebo con bfs !!

using namespace std;

vector<long long int> reconstruirBFS(unordered_map<long long int,long long int>& bfsres){
    vector<long long int> distancias = vector<long long int>(bfsres.size()-1);
    for(int i = 0;i< distancias.size() ; i++) {
        distancias[i] = bfsres[i+1] ;
    }
    return distancias;
}
//paso el res de bfs a otro vector


//algoritmo visto en la clase práctica de recorridos del turno tarde...
unordered_map<long long int,long long int> bfs(long long int s, unordered_map<long long int,unordered_map<long long int,long long int>>& caminos) {
  
  unordered_map<long long int,long long int> distancias ;
  for(const pair<long long int,unordered_map<long long int,long long int>>& vertices : caminos) { 
        distancias[vertices.first] = INT_MAX ;
  }
  
  distancias[s] = 0;
  queue<long long int> enEspera ;
  enEspera.push(s) ;
  while(!enEspera.empty()) {
    long long  u = enEspera.front() ;
    enEspera.pop();
    for(const pair<long long int,long long int>& ady : caminos[u]) {
         if(distancias[ady.first]==INT_MAX){
            distancias[ady.first] = distancias[u]+1 ;
          
            enEspera.push(ady.first) ;
        }

    }
  }
 return distancias ;
} //O(|caminos|+|vertices|)

int main() {
long long int aulas;
long long int atajos;
unordered_map<long long int,unordered_map<long long int,long long int>> caminos;


cin >> aulas;
atajos = aulas ;
long long int i = 1 ;
while(i<=atajos) {   
    
    long long int aulaDestino ;
    cin >> aulaDestino;
    caminos[i][aulaDestino] = 1 ;

    i ++ ;
      
    }
 

 for(const pair<long long int,unordered_map<long long int,long long int>>&  aula : caminos) {
     if(aula.first ==1) {
        caminos[aula.first][aula.first+1] = 1 ; //la distancia desde un aula al aula contigua
        caminos[aula.first][aula.first] = 0; //la distancia desde un aula hacia ella misma 

     }
     if(aula.first == aulas) {
        caminos[aula.first][aula.first-1] = 1 ; //la distancia desde la ult aula hacia el aula de atrás 
        caminos[aula.first][aula.first] = 0;
     }
     else {
        caminos[aula.first][aula.first-1] = 1 ; //distancias del resto de aulas,pq puedo ir hacia atras o adelante
        caminos[aula.first][aula.first+1] = 1 ;
        caminos[aula.first][aula.first] = 0;
     }
 }
 
     unordered_map<long long int,long long int> resbfs = bfs(1,caminos) ;
     vector<long long int> res = reconstruirBFS(resbfs) ;
     for(int i = 0;i<res.size() ; i++) {
        cout<< res[i] ;
        if(i<res.size()-1) {
            cout << " " ;
        }
     }
    cout << endl ;
    return 0;
     
}
