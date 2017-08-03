/*************************************************************************
	> File Name: BigNumberPlus.java
	> Author: 
	> Mail: 
	> Created Time: 2017年07月25日 星期二 17时38分09秒
 ************************************************************************/
import java.util.Scanner;
import java.math.BigDecimal;
public class IsEqual{
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        int n;
        BigDecimal x,y,c;
        while(sc.hasNext()){
            x = new BigDecimal(sc.next());
            y = new BigDecimal(sc.next());
            if(x.compareTo(y) == 0){
                System.out.println("YES");
            }else{
                System.out.println("NO");
            }
        }
        sc.close();
    }
}
