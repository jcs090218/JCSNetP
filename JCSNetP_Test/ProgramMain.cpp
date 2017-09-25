/**
 * $File: ProgramMain.cpp $
 * $Date: 2017-04-09 20:27:37 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */


#include <iostream>

#include <JCSNetP.h>

#ifdef _DEBUG
#pragma comment(lib, "JCSNetPd.lib")
#else
#pragma comment(lib, "JCSNetP.lib")
#endif


/**
 * @func main
 * @brief Program Entry Point
 * @param argc : argument count
 * @param argv : argument vector
 * @return int : program exception code.
 */
int main(int argc, char* argv[])
{
	JCSNetP::JCSNetP_Util util;

	int32_t test = 0x12345678;
	float floatTest = 1.f;

	printf("swapped 0x%x is 0x%x\n", test, JCSNetP::ByteSwap(test));
	printf("swapped %f is %f\n", floatTest, JCSNetP::ByteSwap(floatTest));
	printf(
		"swapped 0x%x is 0x%x\n", 
		JCSNetP::TypeAliaser<float, uint32>(floatTest).Get(), 
		JCSNetP::TypeAliaser<float, uint32>(JCSNetP::ByteSwap(floatTest)).Get());

    JCSNetP_OutputMemoryBitStream mbs;

    mbs.WriteBits(11, 5);
    mbs.WriteBits(52, 6);

    // --------------------
	std::cin.get();
	return 0;
}
