#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <x86intrin.h>

int main(void)
{
    char a[16];
    int i;
    volatile char* addr;
    unsigned long long cycle_before, cycle_after;
    unsigned junk;

    srand(time(NULL));
    for (i = 0; i < 16; i++)
        a[i] = rand() % 100;

    _mm_clflush(a);

    addr = &a[2];
    cycle_before = __rdtscp(&junk);
    (void)*addr;
    cycle_after = __rdtscp(&junk);

    printf("Access time: %lld cycles\n", cycle_after - cycle_before);

    addr = &a[2];
    cycle_before = __rdtscp(&junk);
    (void)*addr;
    cycle_after = __rdtscp(&junk);

    printf("Access time: %lld cycles\n", cycle_after - cycle_before);

    return 0;
}
