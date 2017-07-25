/*************************************************************************
	> File Name: BigNumberPlus.java
	> Author: 
	> Mail: 
	> Created Time: 2017年07月25日 星期二 17时38分09秒
 ************************************************************************/
import java.util.Scanner;
import java.math.BigInteger;
public class BigNumberPlus{
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        int n;
        BigInteger x,y,c;
        n = sc.nextInt(); 
        for(int i = 1;i<=n;i++){
            x = new BigInteger(sc.next());
            y = new BigInteger(sc.next());
            System.out.println("Case " + i+":");
            System.out.println(x+" + "+y+" = "+x.add(y));
            if(i != n){
                System.out.println();
            }
        }
        sc.close();
    }
}
