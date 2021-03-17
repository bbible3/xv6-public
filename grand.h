//static unsigned random_seed = 1;
//A small change for linking
#ifndef GRAND_H
#define GRAND_H

#define RANDOM_MAX ((1u << 31u) - 1u)

unsigned lcg_parkmiller(unsigned *state);
unsigned next_random();
unsigned rand_range(int low, int high);
#endif
