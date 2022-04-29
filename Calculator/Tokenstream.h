#include <iostream>
#include <sstream>
#include <exception>
#ifndef TOKENSTREAM_H
#define TOKENSTREAM_H



struct Token
{
public:
	Token(char c='0') :sign(c) {};
	Token(char c, double v) :sign(c), value(v){};
	Token(char c, std::string n) :sign(c), name(n) {};

	char sign;
	double value=0.0;
	std::string name;
};
class Variable {
public:
	std::string name;
	double value;
	Variable(std::string n, double v) :name(n), value(v){}
};




namespace constTokens
{
	const char end_calculation = ';';
	const char result = '=';
	const char prompt = '>';
	const char quit = 'q';
	const char variable = 'v';
	const char let = 'l';
	const std::string dec_key="let";
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
	void ignore(char c);
	operator bool() const { return is.operator bool(); }

private:
	Token buffer;
	bool buff=false;
	std::istream& is;
	
};

#endif // TOKENSTREAM_H




