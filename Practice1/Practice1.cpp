
//VARIANT 4
#include <iostream>
void Ex_1_change_bit_to_1(unsigned int & number);
void Ex_2_change_bit_to_0(unsigned int& number);
void Ex_3_multiply_by_32(unsigned int& number);
void Ex_4_divide_by_32(unsigned int& number);
void Ex_5(unsigned int& number, short bite_number);

void coutp(unsigned int x);




int main()
{
	//First
	//DEFAULT = 0, A=10, B=11, C=12, D=13, E=14, F=15
	//    0000 0000 0000
	std::cout << "Ex.1\n";
	unsigned int DEFAULT = 0x000;
	Ex_1_change_bit_to_1(DEFAULT);

	std::cout << std::endl;


	//Second
	//User input
	std::cout << "Ex.2\n";
	std::cout << "Input number for ex.2\n";
	unsigned int NUMBER_FOR_2;
	std::cin >> NUMBER_FOR_2;
	Ex_2_change_bit_to_0(NUMBER_FOR_2);


	std::cout << std::endl;

	//Third
	//User input
	std::cout << "Ex.3\n";
	unsigned int NUMBER_FOR_3;
	std::cout << "Input number for ex.3\n";
	std::cin >> NUMBER_FOR_3;
	Ex_3_multiply_by_32(NUMBER_FOR_3);
	std::cout << NUMBER_FOR_3;


	std::cout << std::endl;

	//Fouth
	//User input
	std::cout << "Ex.4\n";
	unsigned int NUMBER_FOR_4;
	std::cout << "Input number for ex.4\n";
	std::cin >> NUMBER_FOR_4;
	Ex_4_divide_by_32(NUMBER_FOR_4);
	std::cout << NUMBER_FOR_4;
	

	//Fifth
	//User input
	std::cout << "Ex.5\n";
	unsigned int NUMBER_FOR_5;
	short bite_number;
	std::cout << "Input number and bite position,which u want to change\n";
	std::cin >> NUMBER_FOR_5 >> bite_number;
	Ex_5(NUMBER_FOR_5, bite_number);
	
	

}

/*params
	
*/
//Bit is 0
void Ex_1_change_bit_to_1(unsigned int & number) {
	// We need change uneven bits to 1
	// Mask will be 1010 1010 1010
	const unsigned int mask = 0xAAA;
	number = number | mask;
	coutp(number);
}

void Ex_2_change_bit_to_0(unsigned int& number) {
	//We need reset 4 bits from 5 to the left
	// 1111 .... 1111 1100 0011 1111
	// F... F C 3 F
	const unsigned int mask = 0xFFFFFFFFFFFFFC3F;
	number = number & mask;
	coutp(number);
}


void Ex_3_multiply_by_32(unsigned int& number) {
	// number << 5 is equals number * 32
	number = number << 5;
}

void Ex_4_divide_by_32(unsigned int& number) {
	// number >> 5 is equals number / 32
	number = number >> 5;
}


//Use if bite on position bite_number is not 1
void Ex_5(unsigned int& number, short bite_number) {
	//We have mask 1000000...0...00000
	//Should get mask 0000000...1...00000. Use >> 
	
	int mask = INT_MAX - (INT_MAX >> 1);
	short shift_to_right = sizeof(int) * 8 - bite_number - 2; //sizeof(int) = 4, 4 * 8 =32
	number = number | (mask >> shift_to_right);
	coutp(number);

}

void coutp(unsigned int x)
{
	int n = sizeof(int) * 8;
	unsigned  maska = (1 << (n - 1));

	for (int i = 1; i <= n; i++)
	{
		std::cout << ((x & maska) >> (n - i));
		maska = maska >> 1;
	}
}


