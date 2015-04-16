#include <stdlib.h>
#include <stdio.h>
#define NUM_POINTS 5
#define NUM_COMMANDS 2
int main()
{
    char * commandsForGnuplot[] = {"set title \"special plot\"", "plot exp(-0.2*x)*sin(x)"};
    FILE * gnuplotPipe = _popen ("gnuplot -persistent", "w");

    int i;
    //plot that souldja boi
    for (i=0; i < NUM_COMMANDS; i++)
    {
        fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
    }
    return 0;
}
