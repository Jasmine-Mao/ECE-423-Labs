#include <iostream>
#include <stdio.h>
#include "../import_files/import_files/dct_math.h"
#include "../import_files/import_files/util.h"
#include "../import_files/import_files/2D_idct.h"

#define NORMALIZE(x) (temp = (x), ( (temp < 0) ? 0 : ( (temp > 255) ? 255 : temp  ) ) )

//added what was in the idct file
//created a new header file with the function definition so we can call the function

using namespace std;

void sw_idct(pdct_block_t DCAC, pcolor_block_t block)
{
	//uint32_t total_memory = 0;

    int32_t tmp0, tmp1, tmp2, tmp3;
    int32_t tmp10, tmp11, tmp12, tmp13;
    int32_t z1, z2, z3, z4, z5;
    int32_t temp;

    DCTELEM* inptr;

    int32_t * wsptr;
    uint8_t* outptr;

    int ctr;

    int32_t workspace[DCTSIZE*DCTSIZE];	/* buffers data between passes */
    SHIFT_TEMPS

    /* Pass 1: process columns from input, store into work array. */
    /* Note results are scaled up by sqrt(8) compared to a true IDCT; */
    /* furthermore, we scale the results by 2**PASS1_BITS. */

    inptr = DCAC[0];
    wsptr = workspace;
    for (ctr = DCTSIZE; ctr > 0; ctr--) {

        /* Even part: reverse the even part of the forward DCT. */
        /* The rotator is sqrt(2)*c(-6). */

        z2 = inptr[DCTSIZE*2];
        z3 = inptr[DCTSIZE*6];

        z1 = MULTIPLY(z2 + z3, FIX_0_541196100);
        tmp2 = z1 + MULTIPLY(z3, - FIX_1_847759065);
        tmp3 = z1 + MULTIPLY(z2, FIX_0_765366865);

        z2 = inptr[DCTSIZE*0];
        z3 = inptr[DCTSIZE*4];

        tmp0 = (z2 + z3) << CONST_BITS;
        tmp1 = (z2 - z3) << CONST_BITS;

        tmp10 = tmp0 + tmp3;
        tmp13 = tmp0 - tmp3;
        tmp11 = tmp1 + tmp2;
        tmp12 = tmp1 - tmp2;

        /* Odd part per figure 8; the matrix is unitary and hence its
         * transpose is its inverse.  i0..i3 are y7,y5,y3,y1 respectively.
         */

        tmp0 = inptr[DCTSIZE*7];
        tmp1 =inptr[DCTSIZE*5];
        tmp2 = inptr[DCTSIZE*3];
        tmp3 = inptr[DCTSIZE*1];

        z1 = tmp0 + tmp3;
        z2 = tmp1 + tmp2;
        z3 = tmp0 + tmp2;
        z4 = tmp1 + tmp3;
        z5 = MULTIPLY(z3 + z4, FIX_1_175875602); /* sqrt(2) * c3 */

        tmp0 = MULTIPLY(tmp0, FIX_0_298631336); /* sqrt(2) * (-c1+c3+c5-c7) */
        tmp1 = MULTIPLY(tmp1, FIX_2_053119869); /* sqrt(2) * ( c1+c3-c5+c7) */
        tmp2 = MULTIPLY(tmp2, FIX_3_072711026); /* sqrt(2) * ( c1+c3+c5-c7) */
        tmp3 = MULTIPLY(tmp3, FIX_1_501321110); /* sqrt(2) * ( c1+c3-c5-c7) */
        z1 = MULTIPLY(z1, - FIX_0_899976223); /* sqrt(2) * (c7-c3) */
        z2 = MULTIPLY(z2, - FIX_2_562915447); /* sqrt(2) * (-c1-c3) */
        z3 = MULTIPLY(z3, - FIX_1_961570560); /* sqrt(2) * (-c3-c5) */
        z4 = MULTIPLY(z4, - FIX_0_390180644); /* sqrt(2) * (c5-c3) */

        z3 += z5;
        z4 += z5;

        tmp0 += z1 + z3;
        tmp1 += z2 + z4;
        tmp2 += z2 + z3;
        tmp3 += z1 + z4;

        /* Final output stage: inputs are tmp10..tmp13, tmp0..tmp3 */

        wsptr[DCTSIZE*0] = (int32_t) DESCALE(tmp10 + tmp3, CONST_BITS-PASS1_BITS);
        wsptr[DCTSIZE*7] = (int32_t) DESCALE(tmp10 - tmp3, CONST_BITS-PASS1_BITS);
        wsptr[DCTSIZE*1] = (int32_t) DESCALE(tmp11 + tmp2, CONST_BITS-PASS1_BITS);
        wsptr[DCTSIZE*6] = (int32_t) DESCALE(tmp11 - tmp2, CONST_BITS-PASS1_BITS);
        wsptr[DCTSIZE*2] = (int32_t) DESCALE(tmp12 + tmp1, CONST_BITS-PASS1_BITS);
        wsptr[DCTSIZE*5] = (int32_t) DESCALE(tmp12 - tmp1, CONST_BITS-PASS1_BITS);
        wsptr[DCTSIZE*3] = (int32_t) DESCALE(tmp13 + tmp0, CONST_BITS-PASS1_BITS);
        wsptr[DCTSIZE*4] = (int32_t) DESCALE(tmp13 - tmp0, CONST_BITS-PASS1_BITS);

        inptr++;			/* advance pointers to next column */
        wsptr++;
    }

    /* Pass 2: process rows from work array, store into output array. */
    /* Note that we must descale the results by a factor of 8 == 2**3, */
    /* and also undo the PASS1_BITS scaling. */

    wsptr = workspace;
    for (ctr = 0; ctr < DCTSIZE; ctr++) {
        outptr = block[ctr];

        /* Even part: reverse the even part of the forward DCT. */
        /* The rotator is sqrt(2)*c(-6). */

        z2 = (int32_t) wsptr[2];
        z3 = (int32_t) wsptr[6];

        z1 = MULTIPLY(z2 + z3, FIX_0_541196100);
        tmp2 = z1 + MULTIPLY(z3, - FIX_1_847759065);
        tmp3 = z1 + MULTIPLY(z2, FIX_0_765366865);

        tmp0 = ((int32_t) wsptr[0] + (int32_t) wsptr[4]) << CONST_BITS;
        tmp1 = ((int32_t) wsptr[0] - (int32_t) wsptr[4]) << CONST_BITS;

        tmp10 = tmp0 + tmp3;
        tmp13 = tmp0 - tmp3;
        tmp11 = tmp1 + tmp2;
        tmp12 = tmp1 - tmp2;

        /* Odd part per figure 8; the matrix is unitary and hence its
         * transpose is its inverse.  i0..i3 are y7,y5,y3,y1 respectively.
         */

        tmp0 = (int32_t) wsptr[7];
        tmp1 = (int32_t) wsptr[5];
        tmp2 = (int32_t) wsptr[3];
        tmp3 = (int32_t) wsptr[1];

        z1 = tmp0 + tmp3;
        z2 = tmp1 + tmp2;
        z3 = tmp0 + tmp2;
        z4 = tmp1 + tmp3;
        z5 = MULTIPLY(z3 + z4, FIX_1_175875602); /* sqrt(2) * c3 */

        tmp0 = MULTIPLY(tmp0, FIX_0_298631336); /* sqrt(2) * (-c1+c3+c5-c7) */
        tmp1 = MULTIPLY(tmp1, FIX_2_053119869); /* sqrt(2) * ( c1+c3-c5+c7) */
        tmp2 = MULTIPLY(tmp2, FIX_3_072711026); /* sqrt(2) * ( c1+c3+c5-c7) */
        tmp3 = MULTIPLY(tmp3, FIX_1_501321110); /* sqrt(2) * ( c1+c3-c5-c7) */
        z1 = MULTIPLY(z1, - FIX_0_899976223); /* sqrt(2) * (c7-c3) */
        z2 = MULTIPLY(z2, - FIX_2_562915447); /* sqrt(2) * (-c1-c3) */
        z3 = MULTIPLY(z3, - FIX_1_961570560); /* sqrt(2) * (-c3-c5) */
        z4 = MULTIPLY(z4, - FIX_0_390180644); /* sqrt(2) * (c5-c3) */

        z3 += z5;
        z4 += z5;

        tmp0 += z1 + z3;
        tmp1 += z2 + z4;
        tmp2 += z2 + z3;
        tmp3 += z1 + z4;

        /* Final output stage: inputs are tmp10..tmp13, tmp0..tmp3 */
        outptr[0] = NORMALIZE(DESCALE(tmp10 + tmp3, CONST_BITS+PASS1_BITS+3));
        outptr[7] = NORMALIZE(DESCALE(tmp10 - tmp3, CONST_BITS+PASS1_BITS+3));
        outptr[1] = NORMALIZE(DESCALE(tmp11 + tmp2, CONST_BITS+PASS1_BITS+3));
        outptr[6] = NORMALIZE(DESCALE(tmp11 - tmp2,CONST_BITS+PASS1_BITS+3));
        outptr[2] = NORMALIZE(DESCALE(tmp12 + tmp1,CONST_BITS+PASS1_BITS+3));
        outptr[5] = NORMALIZE(DESCALE(tmp12 - tmp1,CONST_BITS+PASS1_BITS+3));
        outptr[3] = NORMALIZE(DESCALE(tmp13 + tmp0,CONST_BITS+PASS1_BITS+3));
        outptr[4] = NORMALIZE(DESCALE(tmp13 - tmp0,CONST_BITS+PASS1_BITS+3));

        wsptr += DCTSIZE;		/* advance pointer to next row */
    }
}


int test_0(int &error_count){
	//this will be based off of TB1 provided on learn
	uint8_t sample_blockout[DCTSIZE][DCTSIZE];

	int16_t sample_DCAC[DCTSIZE][DCTSIZE] = {
			{100,0,0,0,0,0,0,0},
			{0,100,0,0,0,0,0,0},
			{0,0,100,0,0,0,0,0},
			{0,0,0,100,0,0,0,0},
			{0,0,0,0,100,0,0,0},
			{0,0,0,0,0,100,0,0},
			{0,0,0,0,0,0,100,0},
			{0,0,0,0,0,0,0,100}
	};

	uint8_t expected_blockout[DCTSIZE][DCTSIZE] = {
			{100,0,0,0,0,0,0,0},
			{0,100,0,0,0,0,0,0},
			{0,0,100,0,0,0,0,0},
			{0,0,0,100,0,0,0,0},
			{0,0,0,0,100,0,0,0},
			{0,0,0,0,0,100,0,0},
			{0,0,0,0,0,0,100,0},
			{0,0,0,0,0,0,0,100}
	};

	//calculate the hw result
	idct(sample_DCAC, sample_blockout);

	//check to see if they match
	for(int i = 0; i < DCTSIZE; i++){
		for(int k = 0; k < DCTSIZE; k++){
			if(sample_blockout[i][k] != expected_blockout[i][k]){
				error_count++;
			}
		}
	}
	return error_count;
}

int test_1(int &error_count){
	//this will be based off of TB2 provided on learn
	uint8_t sample_blockout[DCTSIZE][DCTSIZE];

	//set the sample DCAC to the one on learn
	int16_t sample_DCAC[DCTSIZE][DCTSIZE] = {
			{1240,0,-10,0,0,0,0,0},
			{-24,-12,0,0,0,0,0,0},
			{-14,-13,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0},
			{0,0,0,0,0,0,0,0}
	};

	uint8_t expected_blockout[DCTSIZE][DCTSIZE] = {
			{141,143,146,149,151,153,153,153},
			{145,147,149,151,153,153,153,153},
			{152,153,154,155,155,155,153,152},
			{157,158,158,159,158,156,154,152},
			{160,160,161,160,159,157,154,153},
			{160,160,161,161,159,157,155,154},
			{157,158,159,159,159,158,156,155},
			{155,156,158,158,159,158,156,155}
	};

	//calculate the hw result
	idct(sample_DCAC, sample_blockout);

	//check to see if they match
	for(int i = 0; i < DCTSIZE; i++){
		for(int k = 0; k < DCTSIZE; k++){
			if(sample_blockout[i][k] != expected_blockout[i][k]){
				error_count++;
			}
		}
	}
	return error_count;
}

int test_general(int &error_count){
	//generate random DCAC
	int16_t DCAC[DCTSIZE][DCTSIZE];
	for(int i = 0; i < DCTSIZE; i++){
		for(int k = 0; k < DCTSIZE; k++){
			DCAC[i][k] = rand() % 256;
		}
	}
	uint8_t expected_blockout[DCTSIZE][DCTSIZE];
	uint8_t sample_blockout[DCTSIZE][DCTSIZE];

	sw_idct(DCAC, expected_blockout);

	idct(DCAC, sample_blockout);

	for(int i = 0; i < DCTSIZE; i++){
		for(int k = 0; k < DCTSIZE; k++){
			if(sample_blockout[i][k] != expected_blockout[i][k]){
				error_count++;
			}
		}
	}
	return error_count;
}

int main(int argc, char **argv){
	int error_count = 0;
	//increments every time a part of the calculation is wrong

	cout << "Running test 1..." << endl;
	test_0(error_count);
	cout << "Count: " << error_count << endl;

	cout << "Running test 2..." << endl;
	test_1(error_count);
	cout << "Count: " << error_count << endl;

	cout << "Running test 3..." << endl;
	test_general(error_count);
	cout << "Count: " << error_count << endl;

	cout << "Running test 4..." << endl;
	test_general(error_count);
	cout << "Count: " << error_count << endl;

	cout << "Running test 5..." << endl;
	test_general(error_count);
	cout << "Count: " << error_count << endl;

	cout << "Running test 6..." << endl;
	test_general(error_count);
	cout << "Count: " << error_count << endl;
}
