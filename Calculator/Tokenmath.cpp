#include "Tokenmath.h"

namespace tokenmath
{
	double maththree(Tokenstream& ts) // deal with -,+
	{
		double value = mathtwo(ts);
		Token t;
		while (true)
		{
			t = ts.get();
			switch (t.sign)
			{
			case '-':
			{
				double value2 = mathtwo(ts);
				value -= value2;
				break;
			}
			case '+':
			{
				double value2 = mathtwo(ts);
				value += value2;
				break;
			}
			default:
				ts.putback(t);
				return value;
			}
		}
	}

	double mathtwo(Tokenstream& ts)   //  deal with /,*
	{
		double value = mathone(ts);
		Token t;
		while (true)
		{
			t = ts.get();
			switch (t.sign)
			{
			case '/':
			{
				double value2 = mathone(ts);
				if (value2 == 0)
					std::cerr << "error: divided by zero\n";
				value /= value2;
				break;
			}

			case '*':
			{
				double value2 = mathone(ts);
				value *= value2;
				break;
			}
			
			default:
				ts.putback(t);
				return value;
				
			}
		}
	}
	double mathone(Tokenstream& ts)   // deal with (,),{,} and -,+ as first sings of value
	{
		Token t = ts.get();
		switch (t.sign)
		{
		case 'n':
			return t.value;
		case '-':
			return -mathone(ts);
		case '+':
			return +mathone(ts);
		case '(':
		{		
			 double value = maththree(ts);
			 Token t2 = ts.get();
			 if (t2.sign != ')')
				 std::cerr << "error ')' is expected\n";
			 return value;
		}
		case '{':
		{
			double value = maththree(ts);
			Token t2 = ts.get();
			if (t2.sign != '}')
				std::cerr << "error '}' is expected\n";
			return value;
		}
		
		default:
			std::cerr << "error: number or parenthises expected,  Tokenmath::mathone\n";
			break;
		}
	
	}
}


