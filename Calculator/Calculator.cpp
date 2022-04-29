// Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "Tokenstream.h"
#include "Tokenmath.h"
void calculate();
double declaration(Tokenstream& ts, tokenmath::Variables& var_t);
void clean_up_mess(Tokenstream& ts);
double statement(Tokenstream& ts, tokenmath::Variables& var_t);
//extern tokenmath::;
int main()
{
	calculate();

}



void calculate()
{
	Tokenstream str(std::cin);
	Token t;
	tokenmath::Variables var_t;
	double value = 0;
	while (str) try
	{
		std::cout << constTokens::prompt;
		t = str.get();
		while (t.sign == constTokens::end_calculation) t = str.get();
		if (t.sign == constTokens::quit) return;
		str.putback(t);
		std::cout << constTokens::result << statement(str, var_t) << '\n';
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << '\n';

	}

}


void clean_up_mess(Tokenstream& ts)
{
	ts.ignore(constTokens::end_calculation);
}





double declaration(Tokenstream& ts, tokenmath::Variables& var_t)
// assume we have seen "let"
// handle: name = expression
// declare a variable called "name" with the initial value "expression"
{
	Token t = ts.get();
	if (t.sign != constTokens::variable) throw std::runtime_error("name expected in declaration");
	std::string var_name = t.name;
	Token t2 = ts.get();

	if (t2.sign != '=')
	{
		std::stringstream e;
		e << "= missing in declaration of " << var_name;
		throw std::runtime_error(e.str());
	}

	double d = tokenmath::maththree(ts, var_t);
	var_t.define_name(var_name, d);
	return d;
}

double statement(Tokenstream& ts, tokenmath::Variables& var_t)
{
	Token t = ts.get();
	switch (t.sign)
	{
	case constTokens::let:
		return declaration(ts,  var_t);
	default:
		ts.putback(t);
		return tokenmath::maththree(ts, var_t);
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
