#include <stdio.h>
#include <math.h>
#define TRUE 1
/*
    n           :   last point number (n+1 number of data points
    f[i], x[i]  :   data points
    yans        :   final result
    xa          :   x value of input for interpolation
*/

int main(int argc, char *argv[])
{
    //VARIABLE DECLARATIONS
    int i, j, kk = 1;
    float xa, yans, z;
    static n = 3; //for 4 data points
    //data points defined on next two lines
    static float x[11] = {1.0, 2.0, 3.0, 4.0};
    static float f[11]= {0.671, 0.620, 0.567, 0.512};

    //RUN THAT SOULDJA BOI
    printf("-------Lagrange Interpolation-------\n\n");
    printf("Function Table Used:\n");
    printf("i     |  x(i)    |  f(i)\n");
    printf("--------------------------\n");
    for( i = 0; i <= n; i ++)
    {
        printf("%d     |  %g       |  %g\n", i, x[i], f[i]);
    }
    while(kk != 0)
    {
        printf("\nInput?  ");
        scanf( "%f", &xa);
        if(!(x[0] <= xa && xa <= x[n]))
            printf("(WARNING: EXTRAPOLATION CAN BE UNACCURATE)\n");
        yans = 0;

        //INTERPOLATION OCCURS HERE
        for( i = 0; i <= n; i++)
        {
            z = 1.0;
            for(j = 0; j <= n; j++)
            {
                if( i != j )
                    z = z*(xa - x[j])/(x[i] - x[j]);
            }
            yans = yans + z*f[i];
        }
        printf("Answer: g( %g ) = %g \n", xa, yans);
        printf("type 1 to continue, 0 to stop: ");
        scanf("%d", &kk);
    }
    return 0;
}
