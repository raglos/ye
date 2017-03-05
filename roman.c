
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    
    int i, j, k;
    i = j = k = 0;

    if (!(argc >= 2)) {
	    fprintf(stderr, "usage %s <int>\n", argv[0]);
	    return 1;
    }

    i = atoi(argv[1]);

    const int   c[] = {1000, 900, 500, 400, 100, 50, 40, 10, 9, 5, 4, 1};
    const char *v[] = {"M", "CM", "D", "CD", "C", "L", "XL", "X", "IX",
	               "V", "IV", "I"};
   
    while (i) {
START:
        if (i >= c[j]) {
            i -= c[j];
            k++;
            goto START; /* this works but continue does not.. */
        }
        if (k)
		while (k--)
			printf("%s", v[j]);
        k = 0;
        j++;
    }
 
    puts("");
    
    return 0;
}
