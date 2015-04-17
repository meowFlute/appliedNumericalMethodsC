/*
    Adapted from Applied Numerical Methods in C
        by Soichiro Nakamura

    curveFit.c
    Linear and higher order polynomial curve fitting by
        least squares regression

    By M. Scott Christensen (meowFlute)
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
    Variable explanations:

*/
void gauss();
double pwr(),fun();

int main(void)
{
    int i, j, jex, jj, k, k_, lp, m, n, nord, _i, _r;
    double fk, gg[100], yy, fljj;
    double x[100], y[100];
    double a[10][10], power;
    static no_of_data = 6;
    static int _aini = 1;
    static double x_ini[] = {0.1, 0.4, 0.5, 0.7, 0.7, 0.9};
    static double y_ini[] = {0.61, 0.92, 0.99, 1.52, 1.47, 2.03};
    L_10:
        for( j = 1; j<= no_of_data; j++)
        {
            x[j] = x_ini[j-1];
            y[j] = y_ini[j-1];
        }
        printf("\nCSL/C8-1       Curve Fitting by Least Square \n");
        printf("Type 0 for polynomial fitting\n");
        printf("     1 for linear combination");
        scanf("%d", &lp );
        // Polynomial fitting
        if( lp == 0)
        {
            printf("Type order of polynomial\n");
            scanf("%d", &nord);
            m = nord + 1;
            for(k = 1; k <= m; k++)
            {
                for(j = 1; j <= m + 1; j++)
                {
                    a[k][j] = 0.0;
                }
            }
            // Developing the matrix for polynomial fitting
            for (k = 1; k <= m; k++)
            {
                for(i = 1; i <= no_of_data; i++)
                {
                    for(j = 1; j <= m; j++)
                    {
                        jj = k - 1 + j - 1;
                        a[k][j] = a[k][j] + pwr(x[i], jj);
                    }
                    yy = pwr(x[i], k-1);
                    a[k][m + 1] = a[k][m + 1] + y[i]*yy;
                }
            }
        }
        else
        {
            printf("Type the number of functions in linear combination\n");
            printf("   (currently only four functions are available)\n");
            //m is the number of functions linearly combined
            scanf("%d", &m);
            for(k = 1; k <= m; k++)
            {
                for(j = 1; j <= m + 1; j++)
                {
                    a[k][j] = 0.0;
                }
            }
            for (k = 1; k <= m; k++)
            {
                for(i = 1; i <= no_of_data; i++)
                {
                    fk = fun( k, x[i]);
                    for(j = 1; j <= m; j++)
                    {
                        a[k][j] = a[k][j] + fk*fun(j, x[i]);
                    }
                    a[k][m + 1] = a[k][m + 1] + y[i]*fk;
                }
            }
        }
        //Printing matrix
        for( i = 1; i <= m; i++)
        {
            for( j = 1; j <= (m + 1); j++)
            {
                printf( " %11.4e ", a[i][j]);
            }
            printf( "\n" );
        }
        n = m;
        gauss( m, a);
        printf( "\n Power coefficients determined \n");
        printf( "-------------------------------------\n");
        if( lp == 1)
        {
            printf( "   Function      Coefficient       \n" );
        }
        else
        {
            printf( "   Power         Coefficient       \n" );
        }
        printf( "--------------------------------------------\n" );
        for( i = 1; i <= m; i++)
        {
            if( lp == 1)
            {
                printf(" %3d             %12.5e \n", i, a[i][m+1]);
            }
            else
            {
                printf(" %3d             %12.5e \n", i - 1, a[i][m+1]);
            }
        }
        printf( "--------------------------------------------\n" );
        for( i = 1; i <= no_of_data; i++)
        {
            gg[i] = 0.0;
            for( k = 1; k <= m; k++)
            {
                if( lp == 1 )
                {
                    gg[i] = gg[i] + a[k][m+1]*fun(k, x[i]);
                }
                else
                {
                    gg[i] = gg[i] + a[k][m+1]*pwr(x[i],k-1);
                }
            }
        }
        printf( "Error evaluation\n" );
        printf( "----------------------------------------------------------\n" );
        printf( "   i   x(i)          y(i)          Curve fitted  Deviation\n" );
        printf( "----------------------------------------------------------\n" );
        for( i = 1; i<= no_of_data; i++)
        {
        printf( "%4d   %11.4e   %11.4e   %11.4e   %11.4e \n", i, x[i], y[i], gg[i], y[i] - gg[i]);
        }
        printf( "----------------------------------------------------------\n" );
        printf( "\n Type 0 to stop, 1 to continue.\n"); scanf("%d", &k);
        if(k != 0)
            goto L_10;
        exit(0);
}

double pwr(x,n)
double x; int n;
{
    double f; int i;
    f = 1.0;
    if (n > 0)
    {
        for(i = 1; i <= n; i++)
        {
            f = f*x;
        }
    }
    return f;
}

void gauss(n, a)
int n; double a[][10];
{
    int i, ipv, j, jc, jr, k, kc, nv;
    double r, tm, va;
    for ( i = 1; i <= (n-1); i++)
    {
        ipv = i;
        for( j = i + 1; j <= n; j++)
        {
            if( fabs(a[ipv][i]) < fabs(a[j][i]) )
                ipv = j;
        }
        if(ipv != i)
        {
            for( jc = 1; jc <= (n+1); jc++)
            {
                tm = a[i][jc];
                a[i][jc] = a[ipv][jc];
                a[ipv][jc] = tm;
            }
        }
        for ( jr = i + 1; jr <= n; jr++ )
        {
            if( a[jr][i] != 0)
            {
                if( a[i][i] == 0.0 )
                {
                    printf("Matrix is singular!\n");
                    exit(0);
                }
                r = a[jr][i]/a[i][i];
                for( kc = i + 1; kc <= (n + 1); kc++)
                {
                    a[jr][kc] = a[jr][kc] - r*a[i][kc];
                }
            }
        }
    }
    if( a[n][n] == 0.0)
    {
        printf("Matrix is singular!\n");
        exit(0);
    }
    a[n][n+1] = a[n][n+1]/a[n][n];
    for( nv = n - 1; nv >= 1; nv--)
    {
        va = a[nv][n+1];
        for(k = nv + 1; k <= n; k++)
        {
            va = va - a[nv][k]*a[k][n+1];
        }
        a[nv][n+1] = va/a[nv][nv];
    }
    return;
}

double fun(k, x)
int k; double x;
{
    double f;
    if(k == 1) f = 1;
    if(k == 2) f = x;
    if(k == 3) f = sin(x);
    if(k == 4) f = exp(x);
    return f;
}
