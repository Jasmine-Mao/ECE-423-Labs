#include <iostream>
#include <stdio.h>
#include "../import_files/import_files/dct_math.h"
#include "../import_files/import_files/util.h"
#include "../import_files/import_files/2D_idct.cc"

//added what was in the idct file
//created a new header file with the function definition so we can call the function

using namespace std;

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

//	for(int i = 0; i < DCTSIZE; i++){
//		for(int k = 0; k < DCTSIZE; k++){
//			cout << (int)sample_blockout[i][k] << " ";
//		}
//		cout << endl;
//	}

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

//	for(int i = 0; i < DCTSIZE; i++){
//		for(int k = 0; k < DCTSIZE; k++){
//			cout << (int)sample_blockout[i][k] << " ";
//		}
//		cout << endl;
//	}

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
	//we can make different test functions and call them in main

	//generate a randomized 8*8 element array that we can use as input and output

	//generate the expected results

	//compare the generated results with the expected results
	return 0;
}

int main(int argc, char **argv){
	int error_count = 0;
	//increments every time a part of the calculation is wrong

	cout << "Running test 1..." << endl;
	test_0(error_count);
	cout << "Error Count: " << error_count << endl;

	cout << "Running test 2..." << endl;
	test_1(error_count);
	cout << "Error Count: " << error_count << endl;
}
