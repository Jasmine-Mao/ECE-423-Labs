#include <iostream>
#include <stdio.h>
#include "../import_files/import_files/dct_math.h"
#include "../import_files/import_files/util.h"
#include "../import_files/import_files/2D_idct.h"
//added what was in the idct file
//created a new header file with the function definition so we can call the function

using namespace std;

int test_0(int &error_count){
	//this will be based off of TB1 provided on learn
	int16_t sample_DCAC[DCTSIZE][DCTSIZE];
	uint8_t sample_blockout[DCTSIZE][DCTSIZE];

	//set the sample DCAC to the one on learn
	for(int i = 0; i < DCTSIZE; i++){
		for(int k = 0; k < DCTSIZE; k++){
			if(i == k){
				sample_DCAC[i][k] = 100;
			}
			else sample_DCAC[i][k] = 0;
		}
	}

	//calculate the hw result
	idct(sample_DCAC, sample_blockout);

	//check to see if they match
	for(int i = 0; i < DCTSIZE; i++){
		for(int k = 0; k < DCTSIZE; k++){
			if(sample_blockout[i][k] != sample_DCAC[i][k]){
				error_count++;
			}
		}
	}
	return error_count;
	//NOTE THAT THIS IS ONLY FOR THE FIRST TB SAMPLE
	//THE OUTPUT WILL NOT ALWAYS BE THE SAME AS THE INPUT DCAD, THIS WAS JUST A COINCIDENCE
}

int test_1(int &error_count){
	//this will be based off of TB2 provided on learn
	return 0;
}

int test(int &error_count){
	//we can make different test functions and call them in main

	//generate a randomized 8*8 element array that we can use as input and output

	//generate the expected results

	//compare the generated results with the expected results
	return 0;
}

int main(int argc, char **argv){
	int error_count = 0;
	//increments every time a part of the calculation is wrong
	test_0(error_count);
}
