#pragma once
#include <iostream>
class MyString
{
	char* data = nullptr;
	unsigned size = 0;
	unsigned capacity = 8;

	void free();
	void copyFrom(const MyString& other);
	void moveFrom(MyString&& other)noexcept;
	void resize();

	explicit MyString(unsigned cap);

public:
	MyString();
	MyString(const char* str);
	MyString(const MyString& other);
	MyString(MyString&& other)noexcept;
	MyString& operator=(const MyString& other);
	MyString& operator=(MyString&& other)noexcept;
	~MyString();

	unsigned lenght() const;
	const char* c_str() const;
	MyString& concat(const MyString& other);

	MyString& operator+=(const MyString& other);
	MyString& operator+=(char ch);

	friend MyString operator+(const MyString& lhs, const MyString& rhs);

	char& operator[](unsigned ind);
	char operator[](unsigned ind) const;

	friend std::istream& operator>>(std::istream& is, MyString& lhs);
};

std::ostream& operator<<(std::ostream&, const MyString& lhs);

unsigned nextPowerOfTwo(unsigned n);
