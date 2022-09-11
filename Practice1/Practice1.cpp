
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
	setlocale(LC_ALL, "");
	int ex_num;
	unsigned int DEFAULT;
	unsigned int NUMBER_FOR_2;
	unsigned int NUMBER_FOR_3;
	unsigned int NUMBER_FOR_4;
	unsigned int NUMBER_FOR_5;
	short bite_number;
	std::cout << "Практическая работа номер 1 \"Побитовые операции и их применение\"\nПреподаватель: Филатов Александр Сергеевич\nРаботу выполнил: Власов Владислав Витальевич ИКБО-10-21\n\n";
	std::cout << "Введите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Перевести нечетные биты в 1\n2)Перевести 4 бита с 5-го слева\n3)Умножить число на 32\n4)Разделить число на 32\n5)Перевести заданный бит в 1\n\n";
	std::cin >> ex_num;
	while (ex_num) {
		switch (ex_num) {
		case 1:
			//First
			//DEFAULT = 0, A=10, B=11, C=12, D=13, E=14, F=15
			//    0000 0000 0000
			std::cout << "Ex.1\n";
			DEFAULT = 3;
			std::cout << "Mask :                   ";
			coutp(0xAAAAAAAA);
			std::cout << "Number before operation: ";
			
			coutp(DEFAULT);
			Ex_1_change_bit_to_1(DEFAULT);
			std::cout << "Number after operation:  ";
			coutp(DEFAULT);
			std::cout << std::endl;
			break;

		case 2:
			//Second
			//User input
			std::cout << "Ex.2\n";
			std::cout << "Input number for ex.2\n";
			std::cin >> NUMBER_FOR_2;
			std::cout << "Mask :                   ";
			coutp(0xFFFFFC3F);
			std::cout << "Number before operation: ";
			coutp(NUMBER_FOR_2);
			std::cout << "Number after operation:  ";
			Ex_2_change_bit_to_0(NUMBER_FOR_2);
			coutp(NUMBER_FOR_2);
			std::cout << std::endl;
			break;
			
		case 3:
			//Third
			//User input
			std::cout << "Ex.3\n";
			std::cout << "Input number for ex.3\n";
			std::cin >> NUMBER_FOR_3;
			std::cout << "Number before operation: ";
			coutp(NUMBER_FOR_3);
			Ex_3_multiply_by_32(NUMBER_FOR_3);
			std::cout << "Number after operation:  ";
			coutp(NUMBER_FOR_3);
			std::cout << "Result decimal: " << NUMBER_FOR_3;
			std::cout << std::endl;
			break;

		case 4:
			//Fouth
			//User input
			std::cout << "Ex.4\n";
			std::cout << "Input number for ex.4\n";
			std::cin >> NUMBER_FOR_4;
			std::cout << "Number before operation: ";
			coutp(NUMBER_FOR_4);
			Ex_4_divide_by_32(NUMBER_FOR_4);
			std::cout << "Number after operation : ";
			coutp(NUMBER_FOR_4);
			std::cout << "Result decimal: " << NUMBER_FOR_4 << std::endl;
			break;

		case 5:
			//Fifth
			//User input
			std::cout << "Ex.5\n";
			std::cout << "Input number and bite position,which u want to change\n";
			std::cin >> NUMBER_FOR_5 >> bite_number;
			std::cout << "Number before operation: ";
			coutp(NUMBER_FOR_5);
			Ex_5(NUMBER_FOR_5, bite_number);
			std::cout << "Number after operation:  ";
			coutp(NUMBER_FOR_5);
			break;
		default:
			return 0;
			break;
		}
		std::cout << "\n\nВведите номер задания, которое хотите протестировать: \n0)Выход из программы\n1)Перевести нечетные биты в 1\n2)Перевести 4 бита с 5-го слева\n3)Умножить число на 32\n4)Разделить число на 32\n5)Перевести заданный бит в 1\n\n";
		std::cin >> ex_num;

	}
	
	

}


//Функция для установки нечетных битов в 1
void Ex_1_change_bit_to_1(unsigned int & number) {
	// We need change uneven bits to 1
	// Mask will be 1010 1010 1010
	const unsigned int mask1 = 0x55555555;
	number = number & mask1;
	const unsigned int mask = 0xAAAAAAAA;
	number = number | mask;
}

//Устанавливает нечетные биты 4 бита слева от 5-ого в 0
void Ex_2_change_bit_to_0(unsigned int& number) {
	//We need reset 4 bits from 5 to the left
	// 1111 .... 1111 1100 0011 1111
	// F... F C 3 F
	const unsigned int mask = 0xFFFFFC3F;
	number = number & mask;
}


//Функция умножает число на 32
void Ex_3_multiply_by_32(unsigned int& number) {
	// number << 5 is equals number * 32
	number = number << 5;
}

//Функция делит число на 32
void Ex_4_divide_by_32(unsigned int& number) {
	// number >> 5 is equals number / 32
	number = number >> 5;
}


//Функция для установки заданного бита в 1
void Ex_5(unsigned int& number, short bite_number) {
	//We have mask 1000000...0...00000
	//Should get mask 0000000...1...00000. Use >> 
	
	int mask = INT_MAX - (INT_MAX >> 1);
	short shift_to_right = sizeof(int) * 8 - bite_number - 2; //sizeof(int) = 4, 4 * 8 =32
	int shifted_mask = mask >> shift_to_right;
	number = number & (~shifted_mask);
	number = number | shifted_mask;

}


//Функция для вывода двоичной записи заданного числа
void coutp(unsigned int x)
{
	int n = sizeof(int) * 8;
	unsigned  maska = (1 << (n - 1));
	for (int i = 1; i <= n; i++)
	{
		std::cout << ((x & maska) >> (n - i));
		maska = maska >> 1;
	}
	std::cout << std::endl;
}


