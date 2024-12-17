
    public class travesiaVital1 {
        
        static int minimaVida(int i ,int j,int[][] tablero) {
            int[][] memoria = new int[tablero.length][tablero[0].length] ;
            return minimaVidaPD(0,0,tablero,memoria) ;
        }
        
        static int minimaVidaPD(int i,int j,int[][] tablero,int[][] memoria) {
            
            if(i==tablero.length-1 && j!=tablero[0].length-1) {
                memoria[i][j]= Math.max(1,minimaVidaPD(i, j+1,tablero,memoria) - tablero[i][j]);
                return memoria[i][j] ;
            }
            
            if(i!= tablero.length-1 && j == tablero[0].length-1) {
                memoria[i][j] = Math.max(1,minimaVidaPD(i+1,j,tablero,memoria) - tablero [i][j]) ;
                return memoria[i][j] ;
            }
            
            if(i == tablero.length-1 && j ==tablero[0].length-1) {
                memoria[i][j] = Math.max(1, 1 - tablero[i][j]);
                return memoria[i][j] ;
            }
                
            else {
                memoria[i][j] = Math.min(minimaVidaPD(i+1,j,tablero,memoria),minimaVidaPD(i, j+1, tablero,memoria)) - tablero[i][j] ;
                if(memoria[i][j]<=0) {
                    memoria[i][j] = 1 ;
                }
                return memoria[i][j] ;
            }
                
           }
        
        public static void main(String[] args) {
            int[][] tab = {
                {-2,-3,3},
                {-5,-10,1},
                {10,30,-5}
            } ;
            System.out.println(minimaVida(0,0,tab)) ;
        
        }
        
            
        }
        
    

