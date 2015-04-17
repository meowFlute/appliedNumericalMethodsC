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
#define NUM_POINTS 6

/*
    Variable explanations:

*/
void gauss(), gnuprint();
double pwr(),fun();

int main(void)
{
    int i, j, jj, k, m, nord, numCoef;
    double fk, gg[100], yy;
    float resolution, lowerBound, upperBound;
    double x[NUM_POINTS], y[NUM_POINTS];
    double a[10][10];
    static int no_of_data = NUM_POINTS;
    static double x_ini[] = {0.1, 0.4, 0.5, 0.7, 0.7, 0.9};
    static double y_ini[] = {0.61, 0.92, 0.99, 1.52, 1.47, 2.03};
    for( j = 0; j < no_of_data; j++)
    {
        x[j] = x_ini[j];
        y[j] = y_ini[j];
    }
    // Polynomial fitting
    printf("Type order of polynomial (maximum %d) : ", no_of_data-1);
    //nord = 5;
    scanf("%d", &nord);
    printf("\nPrint resolution? ");
    scanf("%f", &resolution);
    printf("\nPrint Lower Bound? ");
    scanf("%f", &lowerBound);
    printf("\nPrint Upper Bound? ");
    scanf("%f", &upperBound);
    double coefficients[nord+1];
    numCoef = nord+1;
    m = nord + 1;
    for(k = 0; k < m + 1; k++)
    {
        for(j = 0; j < m + 1; j++)
        {
            a[k][j] = 0.0;
        }
    }
    // Developing the matrix for polynomial fitting
    for (k = 0; k < m; k++)
    {
        for(i = 0; i < no_of_data; i++)
        {
            for(j = 0; j < m; j++)
            {
                jj = k + j;
                a[k][j] = a[k][j] + pwr(x[i], jj);
            }
            yy = pwr(x[i], k);
            a[k][m] = a[k][m] + y[i]*yy;
        }
    }
    //Printing matrix
    printf("\n\nMatrix to solve\n");
    printf("-------------------------\n");
    for( i = 0; i < m; i++)
    {
        for( j = 0; j < (m + 1); j++)
        {
            printf( " %11.4e ", a[i][j]);
        }
        printf( "\n" );
    }
    gauss( m, a);
    printf( "\n\n Power coefficients determined \n");
    printf( "-------------------------------------\n");
    printf( "   Power         Coefficient       \n" );
    printf( "--------------------------------------------\n" );
    for( i = 0; i < m; i++)
    {
        printf(" %3d             %12.5e \n", i - 1, a[i][m]);
        coefficients[i] = a[i][m];
    }
    printf( "--------------------------------------------\n" );
    for( i = 0; i < no_of_data; i++)
    {
        gg[i] = 0.0;
        for( k = 0; k < m; k++)
        {
            gg[i] = gg[i] + a[k][m]*pwr(x[i],k-1);
        }
    }
    printf( "Error evaluation\n" );
    printf( "----------------------------------------------------------\n" );
    printf( "   i   x(i)          y(i)          Curve fitted  Deviation\n" );
    printf( "----------------------------------------------------------\n" );
    for( i = 0; i< no_of_data; i++)
    {
    printf( "%4d   %11.4e   %11.4e   %11.4e   %11.4e \n", i, x[i], y[i], gg[i], y[i] - gg[i]);
    }
    printf( "----------------------------------------------------------\n" );
    gnuprint(resolution, upperBound, lowerBound, coefficients, numCoef, x_ini, y_ini);
    exit(0);
}

void gnuprint(resolution, upperBound, lowerBound, coefficients, numCoef, x_ini, y_ini)
double resolution; double upperBound; double lowerBound; double coefficients[]; int numCoef;
double x_ini[]; double y_ini[];
{
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    FILE * curveFile = fopen("curve.dat", "w");
    FILE * pointFile = fopen("points.dat", "w");

    int i;
    double currentPoint, yans;

    //Print the curve fit data to a file
    currentPoint = lowerBound;
    while(currentPoint <= upperBound)
    {
        yans = 0;
        for( i = 0; i < numCoef; i++)
        {
            yans += coefficients[i]*pwr(currentPoint,i);
        }
        fprintf(curveFile, "%lf %lf \n",currentPoint,yans);
        currentPoint += resolution;
    }
    fclose(curveFile);

    //print the sample data to a file
    for( i = 0; i < NUM_POINTS; i++)
    {
        fprintf(pointFile, "%lf %lf \n",x_ini[i],y_ini[i]);
    }
    fclose(pointFile);

    //pipe the info to gnuplot
    int numCommands = 0;
    char * title = "set title \"Polynomial Curve Fit to Sample Data\"";
    numCommands++;
    char * output = "set terminal png \nset output \"polynomialFit5.png\" \nunset key";
    numCommands++;
    char * plot = "plot 'curve.dat' with lines, 'points.dat' with points lt rgb \"black\" pt 7";
    numCommands++;
    char * commandsForGnuplot[] = {title, output, plot};
    //char * commandsForGnuplot[] = {title, plot};
    for(i = 0; i < numCommands; i++)
    {
        fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]);
    }
    pclose(gnuplotPipe);
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
    for ( i = 0; i < (n-1); i++)
    {
        ipv = i;
        for( j = i + 1; j < n; j++)
        {
            if( fabs(a[ipv][i]) < fabs(a[j][i]) )
                ipv = j;
        }
        if(ipv != i)
        {
            for( jc = 0; jc < (n+1); jc++)
            {
                tm = a[i][jc];
                a[i][jc] = a[ipv][jc];
                a[ipv][jc] = tm;
            }
        }
        for ( jr = i + 1; jr < n; jr++ )
        {
            if( a[jr][i] != 0)
            {
                if( a[i][i] == 0.0 )
                {
                    printf("Matrix is singular!\n");
                    exit(0);
                }
                r = a[jr][i]/a[i][i];
                for( kc = i + 1; kc < (n + 1); kc++)
                {
                    a[jr][kc] = a[jr][kc] - r*a[i][kc];
                }
            }
        }
    }
    if( a[n-1][n-1] == 0.0)
    {
        printf("Matrix is singular!\n");
        exit(0);
    }
    int p = n - 1;
    a[p][p+1] = a[p][p+1]/a[p][p];
    for( nv = p - 1; nv >= 0; nv--)
    {
        va = a[nv][p+1];
        for(k = nv + 1; k <= p; k++)
        {
            va = va - a[nv][k]*a[k][p+1];
        }
        a[nv][p+1] = va/a[nv][nv];
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
