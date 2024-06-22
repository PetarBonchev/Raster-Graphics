#include "Color.h"

Color::Color(const BitSet& bitData) : data(bitData) {
}

Color::Color(unsigned r, unsigned g, unsigned b, unsigned maxValue) : data(2, Utility::minimumBitsToStore(maxValue))
{
	data.setNumber(Utility::RED_POSITION, r);
	data.setNumber(Utility::GREEN_POSITION, g);
	data.setNumber(Utility::BLUE_POSITION, b);
}

void Color::check() const
{
	std::cout << "data:\n";
	std::cout << data.getMaxNumber() << std::endl;
	std::cout << data.getNumber(0) << " ";
	std::cout << data.getNumber(1) << " ";
	std::cout << data.getNumber(2) << std::endl;
}

unsigned Color::r() const
{
	return data.getNumber(Utility::RED_POSITION);
}

unsigned Color::g() const
{
	return data.getNumber(Utility::GREEN_POSITION);
}

unsigned Color::b() const
{
	return data.getNumber(Utility::BLUE_POSITION);
}

void Color::negative(unsigned maxValue)
{
	unsigned newR = maxValue - r();
	unsigned newG = maxValue - g();
	unsigned newB = maxValue - b();

	data.setNumber(Utility::RED_POSITION, newR);
	data.setNumber(Utility::GREEN_POSITION, newG);
	data.setNumber(Utility::BLUE_POSITION, newB);
}
