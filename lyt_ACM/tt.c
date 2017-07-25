#include <stdio.h>  
      
int gcd( int x, int y )  
{  
    if( y == 0 )  
        return x;  
    else  
        return gcd( y, x % y );      
}  
      
int lcm( int x, int y )  
{  
    return x / gcd( x, y ) * y;      
}  
      
int main()  
{  
    int T;  
    scanf( "%d", &T );  
    while( T-- )  
    {  
        int a, b, c, d, rx, ry;  
        scanf( "%d/%d", &a, &b );  
        scanf( "%d/%d", &c, &d );  
        int t = gcd( a, b );  
        a /= t, b /= t;  
        t = gcd( c, d );   
        c /= t, d /= t;   
        if( gcd( b, d ) == 1 )  
        {  
            printf( "%d\n", lcm( a, c ) );  
        }  
        else  
        {  
            printf( "%d/%d\n", lcm( a, c ), gcd( b, d ) );  
        }  
    }  
    return 0;  
}  
