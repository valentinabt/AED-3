#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <list>
#include <tuple>
#include<climits>
#include<queue>
#include<unordered_set>
#include<unordered_map>
#include<functional>
#include<string>
#include<map>
#include<set>
using namespace std ;

map<tuple<long long int,long long int>,string> clasificacion ;
unordered_map<long long int,unordered_set<long long int>> treeEdges ;
unordered_map<long long int,long long int> backConExtremoSuperiorEn ;
unordered_map<long long int,long long int> backConExtremoInferiorEn ;
unordered_map<long long int,long long int> padre ;
unordered_map<long long int,int> estados;
unordered_map<long long int,long long int> visitados; //cubren quedaba en loop
unordered_map<long long int,long long int> memo ;

//Implementacion de disjoint sets utilizando maps,porque puedo indexar directamente sobre el valor de un vertice,y no tengo que
//asignarle un indice o recorrer todo el arreglo para encontrarlo.Este map es un AB 
//CREDITOS : Practica del turno noche (subido al campus)

class DisjointSET{

unordered_map<long long int,long long int> padres ;
unordered_map<long long int,long long int> rangos; 

public:
DisjointSET(unordered_map<long long int,vector<tuple<long long int,long long int>>>& aristas) {
    for(const auto& vertices : aristas) {
                padres[vertices.first] = vertices.first ;
                rangos[vertices.first] = 0 ; 
                if(!aristas[vertices.first].empty()){
                    for(const auto& ady : aristas[vertices.first]){
                        padres[get<0>(ady)] = get<0>(ady) ;
                        rangos[get<0>(ady)] = 0; //no estaba inicicializando bien esto
                    }
                }
    }
    
}

static DisjointSET disjointset(unordered_map<long long int,vector<tuple<long long int,long long int>>>& aristas){
    return DisjointSET(aristas) ; //Este es el constructor 
}



long long int findSet(long long int vertice) {
    if(padres[vertice]!=vertice) {
        padres[vertice] = findSet(padres[vertice]);
    }
    return padres[vertice] ; 
}

void unionByRank(long long int u,long long int v) {
    long long int uRepresentative = findSet(u);
    long long int vRepresentative = findSet(v);
 
        // Si tienen el mismo representante, entonces pertenece al mismo conjunto
        if (uRepresentative == vRepresentative){
             return;
        }
        // Actualizamos el representante segun el caso del rank
        if (rangos[uRepresentative] < rangos[vRepresentative]) {
            padres[uRepresentative] = vRepresentative;
        } else if(rangos[uRepresentative] > rangos[vRepresentative]) { 
            padres[vRepresentative] = uRepresentative;
        } else {
            padres[vRepresentative] = uRepresentative;
            rangos[uRepresentative]++;
        }
}


};

void inicializar(unordered_map<long long int,unordered_set<long long int>>& G){
    for(const auto& v :G ){
        memo[get<0>(v)] = -1 ;
        estados[get<0>(v)] = 0;
        backConExtremoInferiorEn[get<0>(v)] = 0 ;
        backConExtremoSuperiorEn[get<0>(v)] = 0 ;
        padre[get<0>(v)] = -1 ;
        //treeEdges[get<0>(v)] = {};
        visitados[get<0>(v)] = 0;
    }
} //inicializo todas las estructuras para el dfs
//O(|V|+|E|) 

//Retorna true si un extremo de la arista está en una componente conexa distinta al otro extremo.
bool esPuente(DisjointSET& grafo,tuple<long long int,long long int>& arista) {
    return (grafo.findSet(get<0>(arista))!= grafo.findSet(get<1>(arista)));
} 


//Voy a ordenar de menor a mayor por PESO,es decir,la tercer componente de la tupla.
//La complejidad es O(log |E| * |E|)


bool ordenarPorPeso(tuple<long long int,long long int,long long int>& a ,tuple<long long int,long long int,long long int>& b) {
    
    if(get<2>(a)!= get<2>(b)){
        return (get<2>(a)< get<2>(b));
    }
    return false;
}

vector<tuple<long long int,long long int,long long int>> ordenarAristas(vector<tuple<long long int,long long int,long long int>>& aristas) {
    sort(aristas.begin(),aristas.end(),ordenarPorPeso) ; 
    return aristas ;
}

// CREDITOS : dfs + cubren + puentes son algoritmos dados por la catedra,los adapte a las estructuras que estoy utilizando.

void dfs(long long int v,unordered_map<long long int,unordered_set<long long int>>& gprima) {
    estados[v] = 1;
    for (long long int u : gprima[v]) {
        if (estados[u] == 0) {
            treeEdges[v].insert(u);
            padre[u]= v;
            dfs(u,gprima);
        }
        else if(u != padre[v]) {
           if(estados[u]==1){
                backConExtremoSuperiorEn[v]++ ;
            }  
            else{
                backConExtremoInferiorEn[v]++ ;
            } 
           
        }
    }
    estados[v] = 2;
}
long long int cubren(long long int v,long long int p)  { //estos no los puedo pasar por referencia porque son claves en un hash-map -> no se pueden modificar los valores
    if(memo[v] != -1) {
       
		return memo[v];
	}
	long long int res = 0 ; 
    //esto te dicen cuantas backedges "pasan" por v
    if(!treeEdges[v].empty()){ 
       
	   for(const auto&  hijo : treeEdges[v]) {
            if(hijo != p) {  
                res += cubren(hijo,v);
			}
       }
    } 
       res += backConExtremoInferiorEn[v] ; 
       res -= backConExtremoSuperiorEn[v] ;
       memo[v] = res ; 
       return res ; 
}



void hallarPuentes(map<tuple<long long int,long long int>,long long int>& gprimaAdy,vector<tuple<long long int,long long int>>& aristasDelMismoPeso,DisjointSET& cc ){
    vector<tuple<long long int,long long int>> puentes ;
    for(auto& arista : aristasDelMismoPeso){
        long long int u = get<0>(arista);
        long long int v = get<1>(arista);
        long long int urep = cc.findSet(u);
        long long int vrep = cc.findSet(v);
        if(cubren(urep,-1)==0){
            if(padre[urep]==vrep){
                tuple<long long int,long long int> aristaRep = make_tuple(vrep,urep);
                tuple<long long int,long long int> aristaRepInversa = make_tuple(urep,vrep);
                if((gprimaAdy[aristaRep]==1 && gprimaAdy[aristaRepInversa]==0)||(gprimaAdy[aristaRep]==0 && gprimaAdy[aristaRepInversa]==1)){ 
                      clasificacion[arista] = "any" ;
                }  
            }
        }
        if(cubren(vrep,-1)==0){ //si cubren = 0,(v,padre) es puente,pero no se si existe esa arista en G' o no,
            if(padre[vrep]==urep){
                tuple<long long int,long long int> aristaRep = make_tuple(vrep,urep);
                tuple<long long int,long long int> aristaRepInversa = make_tuple(urep,vrep);
                if((gprimaAdy[aristaRep]==1 && gprimaAdy[aristaRepInversa]==0)||(gprimaAdy[aristaRep]==0 && gprimaAdy[aristaRepInversa]==1)){ //si la arista es multiple claramente no es puente
                      clasificacion[arista] = "any" ;
                }  
            }

        }
    }
    
  
} //O(n+m+|c|) donde c es el vector de aristas del mismo peso.


void recorrer(unordered_map<long long int,unordered_set<long long int>>& gprima){
    for(const auto& v : gprima){
        if(estados[get<0>(v)]==0){
           dfs(get<0>(v),gprima);
        }
    } //recorro todas las componentes conexas del grafo G'
} //O(n+m)


void clasificar(vector<tuple<long long int,long long int,long long int>>& aristasOrdenadas,DisjointSET& cc) {
    size_t i = 0;
    while(i<aristasOrdenadas.size()){
        tuple<long long int,long long int,long long int> arista = aristasOrdenadas[i] ;
        long long int v = get<0>(arista) ;
        long long int u = get<1>(arista) ;
        long long int w = get<2>(arista);
        tuple<long long int,long long int> aristaSinPeso = make_tuple(v,u) ;
      
        if(i==aristasOrdenadas.size()-1){ //este es un caso especial,pq su peso no puede ser repetido
          
            if(esPuente(cc,aristaSinPeso)){
                clasificacion[aristaSinPeso] = "any" ;
                cc.unionByRank(u,v);
            }
            else {
                clasificacion[aristaSinPeso] = "none" ;
            }
            i++;
        }
        else {
            if(w<get<2>(aristasOrdenadas[i+1])){
                if(esPuente(cc,aristaSinPeso)) {
                    clasificacion[aristaSinPeso] = "any" ;
                    cc.unionByRank(u,v) ;
                }
                else {
                    clasificacion[aristaSinPeso] = "none" ;
                }
                i++;
            }
            if(w == get<2>(aristasOrdenadas[i+1])){
                vector<tuple<long long int,long long int>> aristasDelMismoPeso ;
                //caso aristas de igual peso,quiero todas las aristas de igual peso seguidas,pq las tengo que tratar aparte
                size_t j = i ;
                while(j<aristasOrdenadas.size() && get<2>(aristasOrdenadas[j])==w){
                    tuple<long long int,long long int> aristaPesada = make_tuple(get<0>(aristasOrdenadas[j]),get<1>(aristasOrdenadas[j]));
                    aristasDelMismoPeso.push_back(aristaPesada) ;
                    j++ ;
                }
                 map<tuple<long long int,long long int>,long long int> gprimaAristas;
                 unordered_map<long long int,unordered_set<long long int>> gprima;
                 for(auto& aristas : aristasDelMismoPeso){
                    if(!esPuente(cc,aristas)){
                        clasificacion[aristas] = "none" ; //estas aristas forman un ciclo con las del AGM 
                    }
                    else {
                    long long int c1 = cc.findSet(get<0>(aristas)) ; //estas no,pero no sabmeos si forman un ciclo entre ellas
                    long long int c2 = cc.findSet(get<1>(aristas)) ;
                    
                   //en vez de conectar una arista a cada vertice,conecto dos componentes conexas
                    gprima[c1].insert(c2);
                    gprima[c2].insert(c1); 
                    gprimaAristas[make_tuple(c1,c2)] ++;
                    clasificacion[aristas] = "at least one" ; //clasificacion temporal
                    }
                }
               inicializar(gprima); //O(n+m)
               recorrer(gprima);
               hallarPuentes(gprimaAristas,aristasDelMismoPeso,cc) ;
                 
               for(tuple<long long int,long long int>& aristas : aristasDelMismoPeso){
                    if(clasificacion[aristas]=="any"){
                        cc.unionByRank((get<0>(aristas)),(get<1>(aristas)));
                    }
                 } 
                    

                 for(tuple<long long int,long long int>& aristas : aristasDelMismoPeso){
                    if(clasificacion[aristas]== "at least one"){ 
                        if(esPuente(cc,aristas)){
                            cc.unionByRank(get<0>(aristas),get<1>(aristas));
                           //antes solo agregaba una arista at least one,pero tengo que agregar todas las que conectas cc conexas pero forman ciclos todas
                           //juntas 
                           //ir uniendo por rango me asegura que no agregue más de una que conecte dos componentes conexas distintas 
                        }
                    } 
                 }  
                  i = j ;
                 
                   
                }
            }
        }
    }
 



int main() {

long long int cantAristas; 
long long int cantVertices ;
long long int cantLineas ;
unordered_map<long long int,vector<tuple<long long int,long long int>>> aristas ;
cin >> cantVertices; 
cin >> cantAristas; 

cantLineas = 0;
vector<tuple<long long int,long long int,long long int>> aristasOrdenRelativo = vector<tuple<long long int,long long int,long long int>>(cantAristas);

while(cantLineas<cantAristas) {   
    
    long long int v;
    long long int u ;
    long long int w;
    cin >> v;
    cin >> u;
    cin >> w;  
   
    aristas[v].push_back(make_tuple(u,w));
    aristas[u].push_back(make_tuple(v,w));
    aristasOrdenRelativo[cantLineas] = make_tuple(v,u,w);
    clasificacion[(make_tuple(v,u))] = "empty" ;
    cantLineas ++ ;

    }  
vector<tuple<long long int,long long int,long long int>> vectorAristas = aristasOrdenRelativo; //hago una copia del vector de aristas
vectorAristas = ordenarAristas(vectorAristas); //ordeno la copia  //O(log |E| *|E|)
DisjointSET d1 = DisjointSET(aristas);
clasificar(vectorAristas,d1) ; 

for(size_t i = 0;i < aristasOrdenRelativo.size();i++) {
    tuple<long long int,long long int> arista = make_tuple(get<0>(aristasOrdenRelativo[i]),get<1>(aristasOrdenRelativo[i]));
    cout << clasificacion[arista] << endl ;
}
return 0; 
     
} 
