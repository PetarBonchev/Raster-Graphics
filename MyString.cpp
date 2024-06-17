#include "MyString.h"
#include <cstring>
#include <cmath>
#pragma warning (disable : 4996)

void MyString::free()
{
	delete[] data;
	data = nullptr;
	size = capacity = 0;
}

void MyString::copyFrom(const MyString& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new char[capacity + 1];
	strcpy(data, other.data);
}

void MyString::moveFrom(MyString&& other)noexcept
{
	size = other.size;
	other.size = 0;

	capacity = other.capacity;
	other.capacity = 0;

	data = other.data;
	other.data = nullptr;
}

void MyString::resize()
{
	unsigned newCap = (capacity + 1) * 2;
	char* newData = new char[newCap];
	capacity = newCap - 1;

	strcpy(newData, data);
	delete[] data;
	data = newData;
}

MyString::MyString(unsigned cap)
{
	size = 0;
	capacity = cap;
	data = new char[capacity + 1];
}

MyString::MyString() : MyString("")
{
}

MyString::MyString(const char* str)
{
	if (str == nullptr) {
		size = 0;
		capacity = Utility::DEFAULT_CAPACITY;
		data = new char[capacity + 1];
		strcpy(data, "");
		return;
	}
	size = strlen(str);
	capacity = std::max((int)Utility::nextPowerOfTwo(size), (int)Utility::DEFAULT_CAPACITY) - 1;
	data = new char[capacity + 1];
	strcpy(data, str);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString::MyString(MyString&& other)noexcept
{
	moveFrom(std::move(other));
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

MyString& MyString::operator=(MyString&& other)noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

MyString::~MyString()
{
	free();
}

unsigned MyString::lenght() const
{
	return size;
}

const char* MyString::c_str() const
{
	return data;
}

MyString& MyString::concat(const MyString& other)
{
	if (size + other.size <= capacity) {
		size += other.size;
		strcat(data, other.data);
		return *this;
	}

	size += other.size;
	capacity = Utility::nextPowerOfTwo(size) - 1;
	char* buff = new char[capacity + 1];
	strcpy(buff, data);
	strcat(buff, other.data);

	delete[] data;
	data = buff;
	return *this;
}

MyString& MyString::operator+=(const MyString& other)
{
	return concat(other);
}

MyString& MyString::operator+=(char ch)
{
	if (size == capacity) {
		resize();
	}
	data[size++] = ch;
	data[size] = Utility::TERMINATE_SYMBOL;
	return *this;
}

char& MyString::operator[](unsigned ind)
{
	return data[ind];
}

char MyString::operator[](unsigned ind) const
{
	return data[ind];
}

MyString operator+(const MyString& lhs, const MyString& rhs)
{
	unsigned size = lhs.size + rhs.size;
	unsigned capacity = Utility::nextPowerOfTwo(size) - 1;

	MyString res(capacity);
	res.size = size;
	strcpy(res.data, lhs.data);
	strcat(res.data, rhs.data);

	return res;
}

std::istream& operator>>(std::istream& is, MyString& str)
{
	char buff[1024];
	is >> buff;

	delete[] str.data;
	str.size = strlen(buff);
	str.capacity = std::max((int)Utility::nextPowerOfTwo(str.size), 16) - 1;
	str.data = new char[str.capacity + 1];
	strcpy(str.data, buff);

	return is;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	os << str.c_str();
	return os;
}