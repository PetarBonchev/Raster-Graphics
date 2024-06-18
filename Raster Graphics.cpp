#include <iostream>
#include "MyString.h"
#include "BitSet.h"

int main()
{
	BitSet b(2, 5);
	b.add(0);
	b.setNumber(2, 10);
	std::cout << b.getNumber(2);
}