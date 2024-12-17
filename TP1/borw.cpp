#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;
int minimo(int a,int b) {
    if(a<b) {
        return a;
    }
    return b;
}


int borw(vector<int>& s,vector<vector<vector<int>>>& memoria,size_t i,size_t ultB,size_t ultN) {
    int res;
    int blanco = INT_MAX;
    int negro = INT_MAX ;
    int noPinto = INT_MAX ;
    if(i== s.size()) { 
        return 0;
    } 
  
    if(memoria[i][ultB][ultN]!= -1 ) {
        return memoria[i][ultB][ultN] ;
    }

        if((ultB == 0 && ultN == 0) || (s[i]<s[ultB-1] && s[i]>s[ultN-1])) {
            negro = borw(s,memoria,i+1,ultB,i+1) ; //pinto de negro
            blanco = borw(s,memoria,i+1,i+1,ultN) ; //pinto de blanco
       
        }
        if(ultB == 0 || s[i]<s[ultB-1] ) {
             blanco = borw(s,memoria,i+1,i+1,ultN) ; //pinto de blanco
     
        }
        if(ultN == 0 || s[i]>s[ultN-1]) {
            negro = borw(s,memoria,i+1,ultB,i+1) ; //pinto de negro
    
        }
        noPinto = 1 + borw(s,memoria,i+1,ultB,ultN) ; 
        res = minimo(minimo(blanco,negro),noPinto) ;
        memoria[i][ultB][ultN] = res;
   
        return res ;
    }



int pintar(vector<int>& s) {
   vector<vector<vector<int>>> memoria(s.size(),vector<vector<int>>(s.size()+1,vector<int>(s.size()+1, 0)));
  //complejdiad espacial O(n*n*n)
  for(size_t i = 0;i< memoria.size();i++) {  
    for(size_t j= 0 ; j < memoria[i].size() ; j++) {
        for(size_t k = 0 ; k < memoria[i][j].size() ;k++) {
            memoria[i][j][k] = -1 ;
        }
    }
  }
  int res;
  res = borw(s,memoria,0,0,0) ;
  return res ;
   
}



int main() {
   bool termina = false;
    while (termina!=true) {
        int n; //dato de la longitud de la list que me pasan 
        std::cin >> n; 

        if (n == -1) {
            termina = true;  
             break ;
        }

        std::vector<int> numeros(n,0);  

        for (int i = 0; i < n; ++i) {
            std::cin >> numeros[i];  
        }  
      
      int res = pintar(numeros) ;
      std::cout << res << std::endl ; 
   

        } 
        return 0; 

       /* vector<int> vector1 = {131, 102, 75, 124, 182, 74, 86, 139, 18, 145, 32, 124, 52, 133, 77, 23, 137, 38, 123, 52, 42, 48, 93, 162, 195, 53, 30, 37, 168, 103};
        int res = pintar(vector1) ;
        std::cout << res << std::endl ;
        return 0;  */
}
