#pragma once
#include "Tokenstream.h"
#include <exception>
#include <sstream>
#include <vector>
namespace tokenmath
{
	// 
	struct Variables
	{
		std::vector<Variable> var_table;
		double  get_value(std::string s);
		void set_value(std::string s, double d);

		double define_name(std::string var, double val);
		bool is_declared(std::string var);


	};

	double maththree(Tokenstream& ts, tokenmath::Variables& var_t); // deal with -,+
	double mathtwo(Tokenstream& ts, tokenmath::Variables& var_t);//  deal with /,*
	double mathone(Tokenstream& ts, tokenmath::Variables& var_t); // deal with (,),{,}
	




	const std::string error_mathone_default("error: number or parenthises expected,  Tokenmath::mathone\n");
	const std::string error_mathone_curly_brackets("error '}' is expected\n");
}

