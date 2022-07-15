#include "Tokenmath.h"
#include <vector>

namespace tokenmath
{

	
	
	double maththree(Tokenstream& ts, Variables& var_t) // deal with -,+
	{
		double value = mathtwo(ts, var_t);
		Token t;
		while (true)
		{
			t = ts.get();
			switch (t.sign)
			{
			case '-':
			{
				double value2 = mathtwo(ts, var_t);
				value -= value2;
				break;
			}
			case '+':
			{
				double value2 = mathtwo(ts, var_t);
				value += value2;
				break;
			}
			default:
				ts.putback(t);
				return value;
			}
		}
	}

	double mathtwo(Tokenstream& ts, Variables& var_t)   //  deal with /,*
	{
		double value = mathone(ts, var_t);
		Token t;
		while (true)
		{
			t = ts.get();
			switch (t.sign)
			{
			case '/':
			{
				double value2 = mathone(ts, var_t);
				if (value2 == 0)
					throw std::runtime_error ("error: divided by zero\n");
				value /= value2;
				break;
			}

			case '*':
			{
				double value2 = mathone(ts, var_t);
				value *= value2;
				break;
			}
			
			default:
				ts.putback(t);
				return value;
				
			}
		}
	}
	double mathone(Tokenstream& ts, Variables& var_t)   // deal with (,),{,} and -,+ as first sings of value
	{
		Token t = ts.get();
		switch (t.sign)
		{
		case 'n':
			return t.value;
		case '-':
			return -mathone(ts, var_t);
		case '+':
			return +mathone(ts, var_t);
		case '(':
		{		
			 double value = maththree(ts, var_t);
			 t = ts.get();
			 if (t.sign != ')')
				 throw std::runtime_error( "error ')' is expected\n");
			 return value;
		}
		case '{':
		{
			double value = maththree(ts, var_t);
			t = ts.get();
			if (t.sign != '}')
				throw std::runtime_error( "error '}' is expected\n");
			return value;
		}
		case constTokens::variable:
		{
			if(var_t.is_declared(t.name))
				return var_t.get_value(t.name);
			throw std::runtime_error("variable expected\n");
		}
		
		default:
			std::stringstream e;
			e << "error: number or opening brackets expected,  Tokenmath::mathone\n wrong sign:" << t.sign;
			throw std::runtime_error(e.str());
		}
	
	}

	bool Variables::is_declared(std::string var)
		// is var already in var_table?
	{
		for (const Variable& v : var_table)
			if (v.name == var) return true;
		return false;
	}

	double Variables::define_name(std::string var_name, double val)
		// add(var_name,val) to var_table
	{
		if (is_declared(var_name))
		{
			std::stringstream e;
			e << var_name << " declared twice";
			throw std::runtime_error(e.str());
		}
		var_table.push_back(Variable(var_name, val));
		return val;
	}

	void Variables::set_value(std::string s, double d)
		// set the Variable named s to d
	{
		for (Variable& v : var_table)
			if (v.name == s) {
				v.value = d;
				return;
			}
		std::stringstream e;
		e << "set: undefined variable " << s;
		throw std::runtime_error(e.str());
	}

	double Variables::get_value(std::string s)
		// return the value of the Variable named s
	{
		for (const Variable& v : var_table)
			if (v.name == s)  return v.value;
		std::stringstream e;
		e << "get: undefined variable " << s;
		throw std::runtime_error(e.str());
	}

}


