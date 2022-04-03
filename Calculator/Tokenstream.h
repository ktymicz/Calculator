#include <iostream>

#ifndef TOKENSTREAM_H
#define TOKENSTREAM_H

struct Token
{
	char sign;
	double value;
};
namespace constTokens
{
	const char calculation_end = ';';
	const char result = '>';
}


class Tokenstream
{
public:
	
	Token get();
	void putback(Token pt)
	{
		if (!buff)
		{
			buffer = pt;
			buff = true;
		}
		else
			std::cerr << "Tokenstream::putback(): buffer is full\n";
	}
	
	Tokenstream(std::istream& tis = std::cin)
		: is(tis)
	{}
private:
	Token buffer;
	bool buff=false;
	std::istream& is;

};

#endif // TOKENSTREAM_H




