/*************************************************************************
	> File Name: 升起气球.java
	> Author: 
	> Mail: 
	> Created Time: 2017年08月07日 星期一 08时24分55秒
 ************************************************************************/
import java.util.Scanner;
import java.util.HashMap;


public class 升起气球{
    public static void main(String args[]){
        int n;
        HashMap<String,Integer> hp = new HashMap<String,Integer>();
        Scanner sc = new Scanner(System.in);
        n = sc.nextInt();
        String s;
        int max;
        while(n != 0){
            hp.clear();
            for(int i = 0;i<n;i++){
                s = sc.next();
                if(hp.containsKey(s)){
                    hp.put(s,hp.get(s)+1);
                }else{
                    hp.put(s,1);
                }
            }
            max = 0;
            for (Integer value : hp.values()) {
                if(value > max){
                    max = value;
                }
            }
            for(String key : hp.keySet()){
                if(hp.get(key) == max){
                    System.out.println(key);
                    break;
                }
            }
            n = sc.nextInt();
        }
        sc.close();
    }
}
