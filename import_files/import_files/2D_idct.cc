#include <stdio.h>
#include "dct_math.h"
#include "util.h"
//XAxiDma *InstancePtr;
//XAxiDma AxiDma;

/*
* This implementation is based on an algorithm described in
*   C. Loeffler, A. Ligtenberg and G. Moschytz, "Practical Fast 1-D DCT
*   Algorithms with 11 Multiplications", Proc. Int'l. Conf. on Acoustics,
*   Speech, and Signal Processing 1989 (ICASSP '89), pp. 988-991.
* The primary algorithm described there uses 11 multiplies and 29 adds.
* We use their alternate method with 12 multiplies and 32 adds.
* The advantage is that no data path contains more than one multiplication.
*/
/* normalize the result between 0 and 255 */
/* this is required to handle precision errors that might cause the decoded result to fall out of range */
#define NORMALIZE(x) (temp = (x), ( (temp < 0) ? 0 : ( (temp > 255) ? 255 : temp  ) ) )

void idct(int16_t DCAC[DCTSIZE][DCTSIZE], uint8_t blockout[DCTSIZE][DCTSIZE])
{
    #pragma HLS interface ap_ctrl_none port=return

    //declare streaming interfaces
    #pragma HLS INTERFACE axis register both port=DCAC
    #pragma HLS INTERFACE axis register both port=blockout

    #pragma HLS DATAFLOW //allows for pipelining??


	//temporary variables
	int16_t DCAC_temp[DCTSIZE][DCTSIZE]; //do we need to change to size 32 bit??
	uint8_t blockout_temp[DCTSIZE][DCTSIZE];

    //array reshaping to set up 32 bit interface for streaming
	#pragma HLS ARRAY_RESHAPE variable=DCAC_temp type=block factor=2 dim=2 //presume factor of 2 bc 2*16 =32
	#pragma HLS ARRAY_RESHAPE variable=blockout_temp type=block factor=8 dim=2 //presume factor of 4 bc 4*8 = 32

	//copy data to temporary to avoid unnecessary reads
	DCAC_row_copy: for(int r = 0; r < DCTSIZE; r++)
	{
		DCAC_col_copy: for(int c = 0; c < DCTSIZE; c++)
		{
			#pragma HLS_PIPELINE //pipeline the loop
				DCAC_temp[r][c] = DCAC[r][c];
		}
	}


    int32_t tmp0, tmp1, tmp2, tmp3;
    int32_t tmp10, tmp11, tmp12, tmp13;
    int32_t z1, z2, z3, z4, z5;
    int32_t temp;
    int32_t workspace[DCTSIZE*DCTSIZE];	/* buffers data between passes */
    SHIFT_TEMPS

    /* Pass 1: process columns from input, store into work array. */
    /* Note results are scaled up by sqrt(8) compared to a true IDCT; */
    /* furthermore, we scale the results by 2**PASS1_BITS. */

    idct_column_loop:for (int col = 0; col < DCTSIZE; col++) {

        /* Even part: reverse the even part of the forward DCT. */
        /* The rotator is sqrt(2)*c(-6). */

        #pragma HLS UNROLL factor=2 //loop unrolling bc single for loop with not much dependencies

        z2 = DCAC_temp[2][col];
        z3 = DCAC_temp[6][col];

        z1 	 = MULTIPLY(z2 + z3, FIX_0_541196100);
        tmp2 = z1 + MULTIPLY(z3, - FIX_1_847759065);
        tmp3 = z1 + MULTIPLY(z2, FIX_0_765366865);

        z2 = DCAC_temp[0][col];
        z3 = DCAC_temp[4][col];

        tmp0 = (z2 + z3) << CONST_BITS;
        tmp1 = (z2 - z3) << CONST_BITS;

        tmp10 = tmp0 + tmp3;
        tmp13 = tmp0 - tmp3;
        tmp11 = tmp1 + tmp2;
        tmp12 = tmp1 - tmp2;

        /* Odd part per figure 8; the matrix is unitary and hence its
         * transpose is its inverse.  i0..i3 are y7,y5,y3,y1 respectively.
         */

        tmp0 = DCAC_temp[7][col];
        tmp1 = DCAC_temp[5][col];
        tmp2 = DCAC_temp[3][col];
        tmp3 = DCAC_temp[1][col];

        z1 = tmp0 + tmp3;
        z2 = tmp1 + tmp2;
        z3 = tmp0 + tmp2;
        z4 = tmp1 + tmp3;
        z5 = MULTIPLY(z3 + z4, FIX_1_175875602); /* sqrt(2) * c3 */

        tmp0 = MULTIPLY(tmp0, FIX_0_298631336);  /* sqrt(2) * (-c1+c3+c5-c7) */
        tmp1 = MULTIPLY(tmp1, FIX_2_053119869);  /* sqrt(2) * ( c1+c3-c5+c7) */
        tmp2 = MULTIPLY(tmp2, FIX_3_072711026);  /* sqrt(2) * ( c1+c3+c5-c7) */
        tmp3 = MULTIPLY(tmp3, FIX_1_501321110);  /* sqrt(2) * ( c1+c3-c5-c7) */
        z1   = MULTIPLY(z1, - FIX_0_899976223);  /* sqrt(2) * (c7-c3) */
        z2   = MULTIPLY(z2, - FIX_2_562915447);  /* sqrt(2) * (-c1-c3) */
        z3   = MULTIPLY(z3, - FIX_1_961570560);  /* sqrt(2) * (-c3-c5) */
        z4   = MULTIPLY(z4, - FIX_0_390180644);  /* sqrt(2) * (c5-c3) */

        z3 += z5;
        z4 += z5;

        tmp0 += z1 + z3;
        tmp1 += z2 + z4;
        tmp2 += z2 + z3;
        tmp3 += z1 + z4;

        /* Final output stage: inputs are tmp10..tmp13, tmp0..tmp3 */

        workspace[col+DCTSIZE*0] = (int32_t) DESCALE(tmp10 + tmp3, CONST_BITS-PASS1_BITS);
        workspace[col+DCTSIZE*7] = (int32_t) DESCALE(tmp10 - tmp3, CONST_BITS-PASS1_BITS);
        workspace[col+DCTSIZE*1] = (int32_t) DESCALE(tmp11 + tmp2, CONST_BITS-PASS1_BITS);
        workspace[col+DCTSIZE*6] = (int32_t) DESCALE(tmp11 - tmp2, CONST_BITS-PASS1_BITS);
        workspace[col+DCTSIZE*2] = (int32_t) DESCALE(tmp12 + tmp1, CONST_BITS-PASS1_BITS);
        workspace[col+DCTSIZE*5] = (int32_t) DESCALE(tmp12 - tmp1, CONST_BITS-PASS1_BITS);
        workspace[col+DCTSIZE*3] = (int32_t) DESCALE(tmp13 + tmp0, CONST_BITS-PASS1_BITS);
        workspace[col+DCTSIZE*4] = (int32_t) DESCALE(tmp13 - tmp0, CONST_BITS-PASS1_BITS);
    }

    /* Pass 2: process rows from work array, store into output array. */
    /* Note that we must descale the results by a factor of 8 == 2**3, */
    /* and also undo the PASS1_BITS scaling. */

    idct_row_loop:for (int row = 0; row < DCTSIZE; row++) {

        /* Even part: reverse the even part of the forward DCT. */
        /* The rotator is sqrt(2)*c(-6). */

        #pragma HLS UNROLL factor=2 //loop unrolling bc single for loop with not much dependencies

        z2 = (int32_t) workspace[row*DCTSIZE+2];
        z3 = (int32_t) workspace[row*DCTSIZE+6];

        z1 = MULTIPLY(z2 + z3, FIX_0_541196100);
        tmp2 = z1 + MULTIPLY(z3, - FIX_1_847759065);
        tmp3 = z1 + MULTIPLY(z2, FIX_0_765366865);

        tmp0 = ((int32_t) workspace[row*DCTSIZE+0] + (int32_t) workspace[row*8+4]) << CONST_BITS;
        tmp1 = ((int32_t) workspace[row*DCTSIZE+0] - (int32_t) workspace[row*8+4]) << CONST_BITS;

        tmp10 = tmp0 + tmp3;
        tmp13 = tmp0 - tmp3;
        tmp11 = tmp1 + tmp2;
        tmp12 = tmp1 - tmp2;

        /* Odd part per figure 8; the matrix is unitary and hence its
         * transpose is its inverse.  i0..i3 are y7,y5,y3,y1 respectively.
         */

        tmp0 = (int32_t) workspace[row*DCTSIZE+7];
        tmp1 = (int32_t) workspace[row*DCTSIZE+5];
        tmp2 = (int32_t) workspace[row*DCTSIZE+3];
        tmp3 = (int32_t) workspace[row*DCTSIZE+1];

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

        blockout_temp[row][0] = NORMALIZE(DESCALE(tmp10 + tmp3, CONST_BITS+PASS1_BITS+3));
        blockout_temp[row][2] = NORMALIZE(DESCALE(tmp12 + tmp1, CONST_BITS+PASS1_BITS+3));
        blockout_temp[row][3] = NORMALIZE(DESCALE(tmp13 + tmp0, CONST_BITS+PASS1_BITS+3));
        blockout_temp[row][4] = NORMALIZE(DESCALE(tmp13 - tmp0, CONST_BITS+PASS1_BITS+3));
        blockout_temp[row][5] = NORMALIZE(DESCALE(tmp12 - tmp1, CONST_BITS+PASS1_BITS+3));
        blockout_temp[row][6] = NORMALIZE(DESCALE(tmp11 - tmp2, CONST_BITS+PASS1_BITS+3));
        blockout_temp[row][7] = NORMALIZE(DESCALE(tmp10 - tmp3, CONST_BITS+PASS1_BITS+3));
    }

	//copy data
    //do we need to resize the for loops??
	Blockout_row_copy: for(int r = 0; r < DCTSIZE; r++)
	{
		Blockout_col_copy: for(int c = 0; c < DCTSIZE; c++)
		{
			#pragma HLS_PIPELINE
				blockout[r][c] = blockout_temp[r][c];
		}
	}

}


