public class Main {
    static int maximo(int a,int b,int c) {
        if(a>=b) {
            return Math.max(a,c) ;
        }
        else {
            return Math.max(b,c) ;
        }
    }
    static int astroTrade(int c,int j,int[]p) {
     int[][] memoria = new int[p.length][p.length] ;
    for(int n = 0 ; n<p.length ;n++) {
        for(int m=0 ; m<p.length ; m++) {
            memoria[n][m] = Integer.MIN_VALUE; 
        }
    }
    return mgn(c,j,p,memoria) ;
}
  
    
    static int mgn(int c,int j,int[] p,int[][]memoria) {
        if(c<0||c>j) {
            return Integer.MIN_VALUE;
        }
        if(j==p.length) {
            return 0;
        }
        else {
            if(c==0) {
                int comproAsteroide = mgn(c+1,j+1,p,memoria)-p[j] ;
                
                int sigoPobre = mgn(c,j+1,p,memoria) ;
                
                int res =Math.max(comproAsteroide,sigoPobre) ;
                memoria[c][j] = res ;
                return res ;
            }
           else {
            if(memoria[c][j] != Integer.MIN_VALUE) {
                return memoria[c][j] ;
            }
            int comproAsteroide = mgn(c+1,j+1,p,memoria)-p[j] ;
            int sigoPobre = mgn(c,j+1,p,memoria) ;
            int vendoAsteroide = mgn(c-1,j+1,p,memoria)+p[j];
            int res = maximo(comproAsteroide,sigoPobre,vendoAsteroide) ;
            memoria[c][j] = res ;
            return res ;
        }
    }}
  
  public static void main(String[] args) {
        int[] p = {3,2,5,6} ;
        int prueba = astroTrade(0,0,p) ;
        System.out.println(prueba);

    } 
}
