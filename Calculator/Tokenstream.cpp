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
	case'-': case'+': case'*': case'/':
	case'(': case')': case'{': case'}':
	case';':
		t.sign = sign;
		t.value = 0;
		return t;
	
	default:
		std::cerr << "error no sign: " << sign << '\n';
		t.sign = 'e';
		t.value = 2.71;
		return t;
	}

}
