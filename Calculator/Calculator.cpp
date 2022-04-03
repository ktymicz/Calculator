// Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Tokenstream.h"
#include "Tokenmath.h"

int main()
{
    Tokenstream str(std::cin);
	Token t;
	double value=0;
	while (true)
	{
		t = str.get();
		/*while (t.sign == ';')
			t = str.get();*/
		if (t.sign != ';') {
			str.putback(t);
			value = tokenmath::maththree(str);
			t = str.get();
			if (t.sign == ';')
				std::cout << constTokens::result << value << '\n';
			else
				std::cerr << "error no sign: " << constTokens::calculation_end << '\n';
		}
		else if (t.sign == ';')
			continue;
		else
			std::cerr << "error : no result term\n";
		
	}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
