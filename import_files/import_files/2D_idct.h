#include <stdio.h>
#include "dct_math.h"
#include "util.h"

using namespace std;

void idct(int16_t DCAC[DCTSIZE][DCTSIZE], uint8_t blockout[DCTSIZE][DCTSIZE]);
