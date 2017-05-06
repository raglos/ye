/*
* this program takes a word and makes a cube out of it. ASCII only.
* wrclark @ github
* $ ./wordcube TEEMO
* T E E M O 
* E       M
* E       E
* M       E
* O M E E T
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NEWLINE puts ("")

int main (int argc, char *argv[]) {

    int i, j, k;
    char *c;

    if (argc != 2 || (j = strlen (argv[1])) < 3) {
        (void) fprintf (stderr, "usage %s (3+ letter word)\n", argv[0]);
        return 1;
    }

    c = malloc (j*2+1);
    if (!c) return 1;

    memset (c, ' ', j*2);

    for (i=0; i<j; i++) (void) printf ("%c ", argv[1][i]);
    NEWLINE;

    for (i=1,k=j-1; i<j-1; i++) {
        (void) printf ("%c%.*s%c\n", argv[1][i], (j*2-3), c, argv[1][--k]);
    }
    
    free (c);

    c = &argv[1][j-1];
    while (c >= argv[1]) {
        (void) printf ("%c ", *(c--));
    }
    NEWLINE;
    return 0;
}
