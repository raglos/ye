
#include <stdio.h>
#include <string.h> /* strlen() */

typedef struct DIGIT {
    unsigned int v : 7;
} digit_t;


void print_row_1(const digit_t *d);
void print_row_2(const digit_t *d);
void print_row_3(const digit_t *d);
void print_roof (const unsigned int i);
void print_floor(const unsigned int i);
void print_usage(char *argv[]);

/* add ,|. - ((blank)) in future */
const digit_t D0 = { .v = 0x7E /* 1111110 */ };
const digit_t D1 = { .v = 0x06 /* 0000110 */ };
const digit_t D2 = { .v = 0x5B /* 1011011 */ };
const digit_t D3 = { .v = 0x4F /* 1001111 */ };
const digit_t D4 = { .v = 0x27 /* 0100111 */ };
const digit_t D5 = { .v = 0x6D /* 1101101 */ };
const digit_t D6 = { .v = 0x7D /* 1111101 */ };
const digit_t D7 = { .v = 0x46 /* 1000110 */ };
const digit_t D8 = { .v = 0x7F /* 1111111 */ };
const digit_t D9 = { .v = 0x67 /* 1100111 */ };
const digit_t *DL[10] = {&D0, &D1, &D2, &D3, &D4, &D5, &D6, &D7, &D8, &D9};

int main (int argc, char *argv[]) {
    
    if (argc < 2 || strlen(argv[1]) < 1) {
        print_usage(argv);
        return 1;
    }

    unsigned int i, j;
    signed   int k;
    i = strlen(argv[1]);
    unsigned int buf[i];

    print_roof(i);

    for(j=0; j<i; j++) {
        k = argv[1][j] - '0';
        if (k > 9 || k < 0) k = 0;
        buf[j] = k;
    }

    /* start/end each row w/ NULL to print fencing */

    print_row_1(NULL);
    for(j=0; j<i; j++) print_row_1(DL[buf[j]]);
    print_row_1(NULL);

    print_row_2(NULL);
    for(j=0; j<i; j++) print_row_2(DL[buf[j]]);
    print_row_2(NULL);

    print_row_3(NULL);
    for(j=0; j<i; j++) print_row_3(DL[buf[j]]);
    print_row_3(NULL);

    print_floor(i);

    return 0;    
}

void print_usage(char *argv[]) {
    fprintf(stderr, "usage: %s <string of digits>\n", argv[0]);
}


void print_roof(const unsigned int i) {
    unsigned int j = i * 5 + 4;
    if ((j&1)) j++;
    while(j--)
        putchar((j&1) ? ' ' : '_');
    putchar('\n');
}

void print_floor(const unsigned int i) {
    unsigned int j = i * 5 + 3;
    unsigned int k = j;
    if (!(j&1)) j--;
    putchar('|');
    while(j--)
        putchar((j&1) ? ' ' : '_');
    if (!(k&1)) putchar(' ');
    puts("|");
}

void print_row_1(const digit_t *d) {
    static int x = 0;
    if (!d) {
        if (!x) {
            printf("|  ");
            x++;
            return;
        }
        printf(" |\n");
        return;
    } 
    printf("%s", ((d->v & 0x40) == 0x40) ? " __ " : "    ");
    printf(" ");
}

void print_row_2(const digit_t *d) {
    static int x = 0;
    if (!d) {
        if (!x) {
            printf("|  ");
            x++;
            return;
        }
        printf(" |\n");
        return;
    }
    printf("%s", ((d->v & 0x20) == 0x20) ? "|" : " ");
    printf("%s", ((d->v & 0x1) == 0x1) ? "__" : "  ");
    printf("%s", ((d->v & 0x2) == 0x2) ? "|" : " ");
    printf(" ");
}

void print_row_3(const digit_t *d) {
    static int x = 0;
    if (!d) {
        if (!x) {
            printf("|  ");
            x++;
            return;
        }
        printf(" |\n");
        return;
    }
    printf("%s", ((d->v & 0x10) == 0x10) ? "|" : " ");
    printf("%s", ((d->v & 0x8) == 0x8) ? "__" : "  ");
    printf("%s", ((d->v & 0x4) == 0x4) ? "|" : " ");
    printf(" ");
}


