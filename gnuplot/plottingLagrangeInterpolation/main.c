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
    float resolution, yans, z, bounds[2];
    static n = 3; //for 4 data points
    //data points defined on next two lines
    static float x[4] = {1.0, 2.0, 3.0, 4.0};
    static float f[4]= {0.671, 0.620, 0.567, 0.671};

    //RUN THAT SOULDJA BOI
    printf("-------Lagrange Interpolation-------\n\n");
    printf("Function Table Used:\n");
    printf("i     |  x(i)    |  f(i)\n");
    printf("--------------------------\n");
    for( i = 0; i <= n; i ++)
    {
        printf("%d     |  %g       |  %g\n", i, x[i], f[i]);
    }
    //get resoluiton of point calculations
    //printf("\nResolution?  ");
    //scanf( "%f", &resolution);
    resolution = 0.1;
    //determine bounds
    //printf("\nLower Bound?  ");
    //scanf( "%f", &bounds[0]);
    bounds[0] = 0.5;
    //printf("\nUpper Bound?  ");
    //scanf( "%f", &bounds[1]);
    bounds[1] = 4.5;
    if(!(x[0] <= bounds[0] && bounds[1] <= x[n]))
        printf("(WARNING: EXTRAPOLATION CAN BE UNACCURATE)\n");

    FILE * data = fopen("data.dat", "w");
    for(i = 0; i < 4; i++)
    {
        fprintf(data, "%lf %lf \n", x[i], f[i]);
    }
    fclose(data);

    FILE * points = fopen("points.dat", "w");
    float currentPoint = bounds[0] - resolution;
    while(currentPoint < (bounds[1] - resolution))
    {
        currentPoint += resolution;
        yans = 0;
        //INTERPOLATION FOR SINGLE POINT OCCURS HERE
        for( i = 0; i <= n; i++)
        {
            z = 1.0;
            for(j = 0; j <= n; j++)
            {
                if( i != j )
                    z = z*(currentPoint - x[j])/(x[i] - x[j]);
            }
            yans = yans + z*f[i];
        }
        printf("Answer: g( %g ) = %g \n", currentPoint, yans);
        fprintf(points, "%lf %lf \n",currentPoint,yans);
    }
    fclose(points);

    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    int numCommands = 0;
    char * title = "set title \"Lagrange Interpolation of Data Points\"";
    numCommands++;
    char * output = "set terminal png \nset output \"interpolation.png\" \nunset key";
    numCommands++;
    char * plot = "plot 'points.dat' with lines, 'data.dat' with points lt rgb \"black\" pt 7";
    numCommands++;
    char * commandsForGnuplot[] = {title, output, plot};
    for(i = 0; i < numCommands; i++)
    {
        fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]);
    }
    return 0;
}
