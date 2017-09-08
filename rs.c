/*
*   by wrclark@github.com
*   this program calculates the amount of xp needed
*   to reach level B from level A
*   by increments of the last arg (xp per action)
*   outputs amount of actions required.
*
*   compilation:
*       $ gcc -o rs rs.c -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MIN_LEVEL 1
#define MAX_LEVEL 99

void usage (char *argv[]) {
    fprintf (stderr,
        "\nUsage: %s <level_start> <level_target> <xp_per_action>\n"
        "Example: `%s 75 99 43'\n"
        "    --> prints amount of actions that yield 43 xp are required\n"
        "        to go from level 75 to 99.\n"
        "\nif x actions are >1xp shy of target level,\n"
        "x + 1 will be output.\n",
    argv[0], argv[0]);

    exit (EXIT_FAILURE);
}

unsigned int get_xp_by_level (unsigned int level) {
    unsigned int i = 0, j;
    for (j=1; j<level; j++) {
        i += floor ((float)j + 300 * pow(2, ((float)j / 7)));
    }
    return floor (i/4);
}

int main (int argc, char *argv[]) {
    
    int i, l1, l2;
    if (argc < 3)
        usage (argv);

    l1 = atoi (argv[1]);
    if (l1 < MIN_LEVEL || l1 > MAX_LEVEL)
        usage (argv);

    l2 = atoi (argv[2]); 
    if (l2 < MIN_LEVEL || l2 > MAX_LEVEL)
        usage (argv);

    if (l1 > l2)
        usage (argv);

    i = atoi (argv[3]);
    if (i < 1)
        usage (argv);

    l1 = get_xp_by_level (l1);
    l2 = get_xp_by_level (l2);

    l1 = l2 - l1;
    if (!(l1 % i)) {
        printf ("%d\n", (l1 / i));
    } else {
        printf ("%d\n", (l1 / i) + 1);
    }

    return EXIT_SUCCESS;
}
