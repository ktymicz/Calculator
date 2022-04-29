#include "Tokenstream.h"

Token Tokenstream::get()
{
	if (buff)
	{
		buff = false;
		return buffer;
	}
	char sign;
	Token t;
	is >> sign;
	// digits
	if (isdigit(sign) || sign == '.')
	{
		is.putback(sign);
		if (!(is >> t.value))
		{
			std::cerr << " error when dot is first sign, it is expected to be digit after dot\n";
			is.clear();
			is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		t.sign = 'n';
		return t;
	}


	switch (sign)
	{
	//correct signs 
	case'-': case'+': case'*': case'/':
	case'(': case')': case'{': case'}': case '=':
	case constTokens::quit: case constTokens::end_calculation:
		t.sign = sign;
		t.value = 0;
		return t;
	default:
		// alpha
		if (isalpha(sign))
		{
			std::string s;
			s+=sign;		
			while (is.get(sign) && isalpha(sign) || isdigit(sign)) s += sign;
			is.putback(sign);
			if (s == constTokens::dec_key) return Token{ constTokens::let };
			return Token{constTokens::variable, s};
		}
		std::stringstream e;
		e << "error no sign: " << sign << '\n';
		throw std::runtime_error(e.str());
	}

}

void Tokenstream::ignore(char c)
{
	// look into buffer
	if (buff && buffer.sign == c)
	{
		buff = false;
		return;
	}
	buff = false;

	// search input for c
	char ch;
	while (is >> ch)
		if (ch == c) return;
}
