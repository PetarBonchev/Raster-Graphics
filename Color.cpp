#include "Color.h"

Color::Color(BitSet data) : data(data) {}

Color::Color(unsigned r, unsigned g, unsigned b)
{
	data.setNumber(Utility::RED_POITION, r);
	data.setNumber(Utility::GREEN_POSITION, g);
	data.setNumber(Utility::BLUE_POSITION, b);
}

unsigned Color::r() const
{
	return data.getNumber(Utility::RED_POITION);
}

unsigned Color::g() const
{
	return data.getNumber(Utility::GREEN_POSITION);
}

unsigned Color::b() const
{
	return data.getNumber(Utility::BLUE_POSITION);
}
