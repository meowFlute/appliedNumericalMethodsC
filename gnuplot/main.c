#include <stdlib.h>
#include <stdio.h>
#define NUM_POINTS 5
#define NUM_COMMANDS 2
int main()
{
    char * title = "set title \"special plot\"";
    char * plot = "plot exp(-0.2*x)*sin(x)";
    char * commandsForGnuplot[NUM_COMMANDS] = {title, plot};
    FILE * gnuplotPipe = _popen ("gnuplot -persistent", "w");

    int i;
    //plot that souldja boi
    for (i=0; i < NUM_COMMANDS; i++)
    {
        fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
    }
    return 0;
}
