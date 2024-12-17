class ejercicio6 {
    
//priorizo que el exceso ea menor a que tener menor cantidad de billetes
static int[] minimo(int[]a,int[]b) {

    if(a[1] > b[1]) {
        return b ;

    }
    if(a[1]<b[1]) {
        return a ;
    }
    else {
        if(a[0]>b[0]) {
            return b ;
        }
        else {
            return a ;
        }
    }
  

}
static int[] optiPagoBT(int[]conj,int i,int j) {
    if(j<0) {
        int[] res = new int[2] ;
        res[0] = 0 ;
        res[1] = -j ;
        return res ;
    }
    if(j>0 && i == conj.length) {
        int[] res = new int[2] ;
        res[0] = Integer.MAX_VALUE;
        res[1] = Integer.MAX_VALUE;
        return res ;
    }
    if(j==0 ) {
        int[] res = new int[2] ;
        res[0] = 0 ;
        res[1] = 0 ;
        return res ;
    } 


    else {
        int[] usar = optiPagoBT(conj, i+1, j-conj[i]) ;
        usar[0]++ ;
        int[] noUsar = optiPagoBT(conj, i+1, j) ;
        return minimo(usar,noUsar) ;
    }

}

static int[] optiPago(int[]conj,int n,int k) {
    int[][][] matriz = new int[conj.length][k+1][] ;
    for(int l= 0;l<conj.length;l++) {
        for(int p = 0; p<matriz[0].length ; p++) {
            matriz[l][p] = new int[2] ;
            matriz[l][p][0] = -1 ;
            matriz[l][p][1] = -1;
        }
    }
    return optiPagoPD(conj, n, k, matriz) ;
    }
    static int[] optiPagoPD(int[]conj,int i,int j,int[][][]matriz) {
        if(j<0) {
            int[] res = new int[2] ;
            res[0] = 0 ;
            res[1] = -j ;
            
            return res ;
        }
        if(j>0 && i == conj.length) {
            int[] res = new int[2] ;
            res[0] = Integer.MAX_VALUE;
            res[1] = Integer.MAX_VALUE;
           
            return res ;
        }
        if(j==0 ) {
            int[] res = new int[2] ;
            res[0] = 0 ;
            res[1] = 0 ;
            
            return res ;
        } 
    
    
        else { 
           if(matriz[i][j][0] != -1 && matriz[i][j][1] != -1) {
            return matriz[i][j] ;
        }else {
            int[] usar = optiPagoPD(conj, i+1, j-conj[i],matriz) ;
            usar[0]++ ;
            //aca tmb modifico la matriz!
           // matriz[i][Math.abs(j-conj[i])][0]++ ;
           
            int[] noUsar = optiPagoPD(conj, i+1, j,matriz) ;
            //matriz[i][Math.abs(j-conj[i])][0]++ ;

            int[] res1 = minimo(usar,noUsar) ;
            matriz[i][j][0] = res1[0];
            matriz[i][j][1] = res1[1];
            return res1 ;
        }
    }
    
    }

public static void main(String[] args) {
    int[] prueba = {1,2,3,5,10,20,20} ;
    int[] res = optiPago(prueba,0,14) ;
    System.out.println(res[0]);
    System.out.println(res[1]);

}
    
}
