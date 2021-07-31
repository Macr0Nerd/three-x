#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ARR_SIZE 100000

int comp(const void * elem1, const void * elem2) {
    uint32_t f = *((uint32_t *)elem1);
    uint32_t s = *((uint32_t *)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

bool search(uint32_t num, uint32_t *arr, int l, int r) {
    if (l > r) return false;

    int mid = l + (r-l)/2;

    if (num == arr[mid]) return true;
    if (num < arr[mid]) return search(num, arr, l, mid - 1);
    if (num > arr[mid]) return search(num, arr, mid + 1, r);
}

bool collatz(uint32_t num, uint32_t *arr, uint32_t start, bool first) {
    if (!first && num == start) return false;

    if ((num == 4) || search(num, arr, 0, ARR_SIZE)) return true;

    bool odd = num % 2;

    if (odd) return collatz((3 * num) + 1, arr, start, false);
    return collatz(num / 2, arr, start, false);
}

int main(int argc, char **argv) {
    //uint32_t set = 1ull << 31; //Set the most significant bit with `x |= set`
    //uint32_t clear = ~flag; //Clear the most significant bit with `x &= clear`.
    //printf("%u\n", flag);
    
    uint32_t list[ARR_SIZE];
    memset(list, 0, 1000);

    list[0] = 3;

    bool tst = false;
    int ind = 1;
    uint32_t cnt = 5;

    while (true) {
        if (ind < ARR_SIZE) qsort(list, sizeof(list)/sizeof(*list), sizeof(*list), comp);
        tst = collatz(cnt, list, cnt, true);

        if (tst) {
            if (ind < ARR_SIZE) {
                list[0] = cnt;
                printf("Added %u to the list\n", cnt);
                ind++;
            } else {
                printf("%u meets the conjecture...\n", cnt);
            }
        } else {
            printf("\n\n\n%u disproves the conjecture!\n\n\n", cnt);
            break;
        }

        cnt++;
    }

    return 0;
}
