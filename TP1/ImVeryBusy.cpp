#include <iostream>
#include <vector>
#include <algorithm>  
#include <tuple>
#include <string>
#include <random>
#include <cstdlib>
#include <ctime> 
using namespace std ;




bool comparacionPorFinalizacion(tuple<int,int>& a ,tuple<int,int>& b) {
    
    
    if(get<1>(a)!= get<1>(b)){
        return (get<1>(a)< get<1>(b));
    }
    else {
        return (get<1>(b)-get<0>(a)) < (get<1>(b)-get<0>(b));

    }
  }
vector<tuple<int,int>> ordenarActividadesSort(vector<tuple<int,int>>& act) {
    std::sort(act.begin(),act.end(),comparacionPorFinalizacion) ; //ordena en o log n * n el vector usando mi criterio
    return act ;
}

vector<tuple<int,int>> imVeryBusy(vector<tuple<int,int>>& act,size_t i,vector<tuple<int,int>> actividadesProgramadas) {
   
     
    if(i== act.size()) {
        return actividadesProgramadas;
    }
    if(i!=0) {
        int inicio = get<0>(act[i]) ;
        int fin = get<1>(act[i]) ;
        size_t contador = 0 ; //da error si pongo int pq es un unsigned int 
        for(size_t j = 0 ; j < actividadesProgramadas.size() ; j++) {
            if(inicio >= get<1>(actividadesProgramadas[j]) || (inicio < get<0>(actividadesProgramadas[j])&& fin <= get<0>(actividadesProgramadas[j]))) {
                contador += 1 ; 
            } 
        }
        if(contador == actividadesProgramadas.size()) {
            //se puede poner la actividad porque no se suporpone con ninguna otra

             actividadesProgramadas.push_back(act[i]) ;
              }
        
        return imVeryBusy(act,i+1,actividadesProgramadas) ;
            }



    if(i==0) {
       actividadesProgramadas.push_back(act[i]) ;
       
       return imVeryBusy(act,i+1,actividadesProgramadas) ;

    }
    return actividadesProgramadas ;
}


int main() {
       int casosDeTest; 
        std::cin >> casosDeTest; 
   
        while(casosDeTest >0) {   
       
        int cantActividades;
        std::cin >> cantActividades;
        std::vector<std::tuple<int,int>> actividades;  

        for (int i = 0; i < cantActividades; ++i) {
            int inicio ;
            std::cin >> inicio;  
            int final ;
            std::cin >> final;
            std::tuple<int,int> tarea ;
            tarea =  std::make_tuple(inicio,final) ;
            actividades.push_back(tarea) ;
        } 
        std::vector<std::tuple<int,int>> actividadesYaOrdenadas ;
        std::vector<std::tuple<int,int>> agenda; 
        vector<tuple<int,int>> agendaOrganizada ;
        int res ;
        actividadesYaOrdenadas = ordenarActividadesSort(actividades) ;
        agendaOrganizada = imVeryBusy(actividadesYaOrdenadas,0,agenda) ;
        res = (int) agendaOrganizada.size() ;
        std::cout << res << std::endl ;
        casosDeTest -- ;

         }  
         return 0; 



}


