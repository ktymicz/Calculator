#pragma once
#include "Tokenstream.h"
namespace tokenmath
{
	double maththree(Tokenstream& ts); // deal with -,+
	double mathtwo(Tokenstream& ts);//  deal with /,*
	double mathone(Tokenstream& ts); // deal with (,),{,}
}

