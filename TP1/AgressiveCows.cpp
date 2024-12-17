
/*podria empezar con k = mitad,acomodo las vacas y me fijo si me sobra mucho espacio
si me sobra,k+1,sino,retorno k= k-1*/
//la distancia minima más larga no es el mayor k que encuentre,sino,recorriendo el arreglo ver cual es el minimo
#include <iostream>
#include <vector>
#include <algorithm>
#include <climits> 

using namespace std;

vector<int> ordenarEstablos(vector<int>& establos) {
     std::sort(establos.begin(),establos.end()) ; //ordena en o log n * n el vector de menor a mayor 
    return establos ;
}

int redondearEnteros(int a) {
    return (a+1)/2;
 }



bool asignarVacasConK(vector<int>& s,int vacas,int k) { //me fijo si puedo usar k 
    //asigno la primer vaca a la izquierda de todo         
    vacas-- ;
    size_t ultEstabloAsignado = 0 ;
    for(size_t i = 1;i<= s.size()-1;i++) {
        if(s[i]-s[ultEstabloAsignado]>= k) {
            vacas -= 1;
            ultEstabloAsignado = i ; //le asigno la vaca al establo mas a la izquierda

        }
        if(vacas==0) {
            return true ;
        }
    }
    return false; // no puedo colocar las c vacas a k distancia
} //O(N)

int asignarVacas(vector<int>& s,int vacas,int inicio,int final) {
   int mejorKHastaAhora = 0;
   
   while(inicio<= final) {
        int k = redondearEnteros(inicio+final) ;
        if(asignarVacasConK(s,vacas,k)) { //es como un algoritmo de bsuqeda binaria pero estamos buscando el k mas grande 
        inicio = k+1; 
        if(k>mejorKHastaAhora) {
            mejorKHastaAhora = k ;
        }
        //puedo probar con un k mas grande
        
    }
    else {
        final = k-1 ; //me pase y ese k no funciona
  
    }}
    return mejorKHastaAhora ; //no puedo retornar final,a veces funciona pero no siempre


}


int main() {
int casosDeTest; 
std::cin >> casosDeTest; 
while(casosDeTest >0) {   
    
    int N;
    std::cin >> N;
    int C ;
    
    std::cin >> C;
    vector<int> establos;
    vector<int> establosOrdenados;
    int vacasAsignadas ;
    for (int i = 0; i < N; ++i) {
        int establo;
        std::cin >> establo;  
        establos.push_back(establo) ;
        } 
    //ordeno los establos
   
    establosOrdenados = ordenarEstablos(establos) ;
     
    
    int sizeEstablos = (int) establos.size()-1;
    
    vacasAsignadas = asignarVacas(establosOrdenados,C,establosOrdenados[0],establosOrdenados[sizeEstablos]);
    
    
    std::cout << vacasAsignadas << std::endl ;
    

    casosDeTest -- ;

    }  
    return 0; 
     
}
