#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "search.h"

size_t naivesearch(const unsigned char *x, const unsigned char *y) {
    size_t m = strlen((char*)x);
    size_t n = strlen((char*)y);
    size_t r = 0;

    for (size_t k = 0; k <= n - m; k++) {
        size_t j = 0;
        while (j < m && x[j] == y[k + j]) {
            j++;
        }
        if (j >= m) {
            ++r;    // OCCURENCE
        }
    }

    return r;
}

size_t naivesearch_ql(const unsigned char *x, const unsigned char *y) {
    size_t m = strlen((char*)x);
    size_t n = strlen((char*)y);
    size_t r = 0;

    unsigned char c = x[m - 1];
    for (size_t k = m - 1; k < n; k++) {
        // quick loop
        while (k < n && y[k] != c) {
            ++k;
        }

        if (k < n) {
            size_t j = m - 1;
            while (j > 0 && x[j - 1] == y[k - m + j]) {
                j--;
            }
            if (j <= 0) {
                ++r;    // OCCURENCE
            }
        }
    }

    return r;
}

// mémoire pointé par y de longueur |yx| + 1
size_t naivesearch_ql_sent(const unsigned char *x, const unsigned char *y) {
    size_t m = strlen((char*)x);
    size_t n = strlen((char*)y);
    size_t r = 0;

    unsigned char yx[n + m + 1];
    strcpy((char*)yx, (char*)y);
    strcat((char*)yx, (char*)x);

    size_t k = m - 1;
    unsigned char c = x[m - 1];
    while (true) {
        // quick loop
        while (yx[k] != c) {
            ++k;
        }

        if (k > n) {
            return r;
        }
        size_t j = m - 1;
        while (j > 0 && x[j - 1] == yx[k - j]) {
            j--;
        }
        if (j <= 0) {
            ++r;    // OCCURENCE
        }
        k++;
    }
}

size_t strnaivesearch(const unsigned char *x, const unsigned char *y) {
    size_t m = strlen((char*)x);
    size_t n = strlen((char*)y);
    size_t r = 0;

    for (size_t k = 0; k <= n - m; k++) {
        if (strncmp((char*)x, (char*)y + k, m) == 0) {
            ++r;    // OCCURENCE
        }
    }

    return r;
}

size_t strnaivesearch_ql(const unsigned char *x, const unsigned char *y) {
    size_t m = strlen((char*)x);
    size_t n = strlen((char*)y);
    size_t r = 0;

    unsigned char c = x[m - 1];
    for (size_t k = m - 1; k < n; k++) {
        // quick loop
        while (k < n && y[k] != c) {
            ++k;
        }

        if (k < n && strncmp((char*)x, (char*)y + k - m + 1, m - 1) == 0) {
            ++r;    // OCCURENCE
        }
    }

    return r;
}

// mémoire pointé par y de longueur |yx| + 1
size_t strnaivesearch_ql_sent(const unsigned char *x, const unsigned char *y) {
    size_t m = strlen((char*)x);
    size_t n = strlen((char*)y);
    size_t r = 0;

    unsigned char yx[n + m + 1];
    strcpy((char*)yx, (char*)y);
    strcat((char*)yx, (char*)x);

    size_t k = m - 1;
    unsigned char c = x[m - 1];
    while (true) {
        // quick loop
        while (yx[k] != c) {
            ++k;
        }

        if (k > n) {
            return r;
        }

        if (strncmp((char*)x, (char*)yx + k - m + 1, m - 1) == 0) {
            ++r;    // OCCURENCE
        }
        k++;
    }
}

size_t mpsearch(const unsigned char *x, const unsigned char *y) {
    size_t m = strlen((char*)x);
    size_t n = strlen((char*)y);
    size_t r = 0;

    int bon_pref[m + 1];
    bon_pref[0] = -1;
    int j = 0;
    for (int k = 1; k < (int)m; ++k) {
        bon_pref[k] = j;
        while (j >= 0 && x[j] != x[k]) {
            j = bon_pref[j];
        }
        j++;
    }
    bon_pref[m] = j;

    // for (int *p = bon_pref; p < bon_pref + m + 1; ++p) {
    //     printf("%d", *p);
    // }
    // printf("\n");

    j = 0;
    for (size_t k = 0; k <= n - 1; k++) {
        while (j >= 0 && x[j] != y[k]) {
            j = bon_pref[j];
        }
        j++;
        if (j == (int)m) {
            ++r;    // OCCURENCE
            j = bon_pref[j];
        }
    }

    return r;
}

size_t kmpsearch(const unsigned char *x, const unsigned char *y) {
    size_t m = strlen((char*)x);
    size_t n = strlen((char*)y);
    size_t r = 0;

    int meil_pref[m + 1];
    meil_pref[0] = -1;
    int j = 0;
    for (int k = 1; k < (int)m; ++k) {
        if (x[j] == x[k]) {
            meil_pref[k] = meil_pref[j];
        } else {
            meil_pref[k] = j;
            do {
                j = meil_pref[j];
            } while (j >= 0 && x[j] != x[k]);
        }
        j++;
    }
    meil_pref[m] = j;

    // for (int *p = meil_pref; p < meil_pref + m + 1; ++p) {
    //     printf("%d", *p);
    // }
    // printf("\n");

    j = 0;
    for (size_t k = 0; k <= n - 1; k++) {
        while (j >= 0 && x[j] != y[k]) {
            j = meil_pref[j];
        }
        j++;
        if (j == (int)m) {
            ++r;    // OCCURENCE
            j = meil_pref[j];
        }
    }

    return r;
}

size_t bmsearch(const unsigned char *x, const unsigned char *y) {
    return y == x;
}

size_t horspoolsearch(const unsigned char *x, const unsigned char *y) {
    return y == x;
}

size_t quicksearch(const unsigned char *x, const unsigned char *y) {
    return y == x;
}
