/*  Program: decimal - binary converter
    By: mscottchristensen
*/

#include "stdio.h"
#include "math.h"

main(int argc, char *argv[])
{
	int a[255], i, k, l, m_expnt, n;
	float pwr_of_2, s, decimal, y;
	printf("---decimal to binary converter---\n");
	do{
        printf("Decimal Value Input?"); scanf("%f", &decimal);
        l = 0;
        k = 1;
        i = log(decimal)/log(2.0) + 3;
        do{
            i = i - 1;
            if( i < -200 ) break;
            pwr_of_2 = pow(2.0, (float)(i-1));
            if(decimal >= pwr_of_2)
            {
                a[k] = 1;
                decimal = decimal - pwr_of_2;
                if( l == 0 )
                {
                    m_expnt = i;
                    l = 1;
                }
            }
            else
            {
                if( k > 1 ) a[k] = 0;
            }
            if( l > 0 ) k = k + 1;
        }while(k<25);
        printf("\n-----------------------\n");
        printf("Binary\n Mantissa = .");
        for(k=l; k<=24; k++)
        {
            printf("%d", a[k]);
            if(k/4*4 == k) printf(" ");
        }
        printf("\n Exponent = %d \n", m_expnt);
        printf("----------------------------------\n");
        printf("\n Type 1 to continue, 0 to stop.\n");
        scanf("%d", &n);
	}while(n>0);
	return 0;
}
