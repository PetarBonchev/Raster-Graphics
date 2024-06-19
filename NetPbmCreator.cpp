#include "NetPbmCreator.h"

NetPbm* NetPbmCreator::readPbm(const MyString& filename)
{
	std::ifstream ifs(filename.c_str());
	if (!ifs.is_open())
		throw std::logic_error("invalid file location");

	char buffer[Utility::BUFFER_SIZE];
	ifs.getline(buffer, Utility::BUFFER_SIZE);

	char magicNumber = buffer[Utility::MAGIC_NUMBER_POSITION_ON_ROW_1];
	Vector<MyString> header;
	Vector<unsigned> dataNumbers;

	header.pushBack(std::move(MyString(buffer)));

	unsigned expectedNumbersCount = (magicNumber == Utility::BITMAP_NORMAL_MAGIC_NUMBER || magicNumber == Utility::BITMAP_BINARY_MAGIC_NUMBER) ? 
													Utility::EXPECTED_NUMBERS_BITMAP : Utility::EXPECTED_NUMBERS_OTHERS;
	while (dataNumbers.getSize() < expectedNumbersCount)
	{
		if (ifs.eof())
			throw std::logic_error("insufficent information in file");

		ifs.getline(buffer, Utility::BUFFER_SIZE);

		MyString line(buffer);
		
		if (line.lenght() == 0)
			continue;
		if (line[0] == Utility::COMMENT_SIGN)
		{
			header.pushBack(std::move(line));
			continue;
		}

		Vector<unsigned> numbers = strToVector(line);
		unsigned len = numbers.getSize();
		for (unsigned i = 0; i < len; i++)
			dataNumbers.pushBack(numbers[i]);

		header.pushBack(std::move(line));

	}
	bool comment = true;
	while (comment)
	{
		if (ifs.eof())
			throw std::logic_error("insufficent information in file");

		ifs.getline(buffer, Utility::BUFFER_SIZE);

		MyString line(buffer);

		if (line.lenght() == 0)
			continue;
		if (line[0] == Utility::COMMENT_SIGN)
		{
			header.pushBack(std::move(line));
			comment = true;
			continue;
		}

		comment = false;
	}
	ifs.close();

	unsigned headerSkip = characterCount(header);

	NetPbm* ret = nullptr;
	switch (magicNumber)
	{
	case Utility::BITMAP_NORMAL_MAGIC_NUMBER:
		ret = readBitMap(filename, headerSkip, dataNumbers[0], dataNumbers[1], header); break;
	case Utility::BITMAP_BINARY_MAGIC_NUMBER:
		ret = readBitMapBinary(filename, headerSkip, dataNumbers[0], dataNumbers[1], header);	break;
	case Utility::GRAYMAP_NORMAL_MAGIC_NUMBER:
		ret = readGrayMap(filename, headerSkip, dataNumbers[0], dataNumbers[1], header, dataNumbers[2]); break;
	case Utility::GRAYMAP_BINARY_MAGIC_NUMBER:
		ret = readGrayMapBinary(filename, headerSkip, dataNumbers[0], dataNumbers[1], header, dataNumbers[2]); break;
	case Utility::PIXMAP_NORMAL_MAGIC_NUMBER:
		ret = readPixMap(filename, headerSkip, dataNumbers[0], dataNumbers[1], header, dataNumbers[2]); break;
	case Utility::PIXMAP_BINARY_MAGIC_NUMBER:
		ret = readPixMapBinary(filename, headerSkip, dataNumbers[0], dataNumbers[1], header, dataNumbers[2]); break;
	default:
		throw std::logic_error("error creating NetPbm in header part");
		break;
	}

	return ret;
}

NetPbm* NetPbmCreator::readBitMap(const MyString& filename, unsigned headerSkip, unsigned width, unsigned height, const Vector<MyString>& header)
{
	std::ifstream ifs(filename.c_str());

	if(!ifs.is_open())
		throw std::logic_error("invalid file location");

	ifs.seekg(headerSkip);

	Vector<BitSet> data;
	for (unsigned i = 0; i < height; i++)
	{
		BitSet row(width - 1, Utility::DEFAULT_MAX_BIT_VALUE);
		for (unsigned j = 0; j < width; j++)
		{
			unsigned bit;
			ifs >> bit;

			if (!Utility::isBit(bit))
				throw std::logic_error("invalid data");

			row.setNumber(j, bit);
		}
		data.pushBack(std::move(row));
	}

	return BitMap(Utility::BITMAP_NORMAL_MAGIC_NUMBER, width, height, header, data).clone();
}

NetPbm* NetPbmCreator::readGrayMap(const MyString& filename, unsigned headerSkip, unsigned width, unsigned height, const Vector<MyString>& header, unsigned maxGray)
{
	unsigned capacity = Utility::minimumBitsToStore(maxGray);

	std::ifstream ifs(filename.c_str());

	if (!ifs.is_open())
		throw std::logic_error("invalid file location");

	ifs.seekg(headerSkip);

	Vector<BitSet> data;
	for (unsigned i = 0; i < height; i++)
	{
		BitSet row(width - 1, capacity);

		char buffer[Utility::BUFFER_SIZE];
		ifs.getline(buffer, Utility::BUFFER_SIZE);
		Vector<unsigned> values = strToVector(MyString(buffer));
		
		for (unsigned j = 0; j < width; j++)
		{
			if (values[j] > maxGray)
				throw std::logic_error("invalid data");

			row.setNumber(j, values[j]);
		}
		data.pushBack(row);
	}
	return GrayMap(Utility::GRAYMAP_NORMAL_MAGIC_NUMBER, width, height, header, maxGray, data).clone();
}

NetPbm* NetPbmCreator::readPixMap(const MyString& filename, unsigned headerSkip, unsigned width, unsigned height, const Vector<MyString>& header, unsigned colorValue)
{
	unsigned capacity = Utility::minimumBitsToStore(colorValue);

	std::ifstream ifs(filename.c_str());

	if (!ifs.is_open())
		throw std::logic_error("invalid file location");

	ifs.seekg(headerSkip);

	Vector<Vector<Color>> data;
	for (unsigned i = 0; i < height; i++)
	{
		Vector<Color> row;

		char buffer[Utility::BUFFER_SIZE];
		ifs.getline(buffer, Utility::BUFFER_SIZE);
		Vector<unsigned> values = strToVector(MyString(buffer));

		for (unsigned j = 0; j < width; j++)
		{
			if (values[3 * j + Utility::RED_POITION] > colorValue || values[3 * j + Utility::GREEN_POSITION] > colorValue || values[3 * j + Utility::BLUE_POSITION] > colorValue)
				throw std::logic_error("invalid data");

			BitSet bitset(Utility::NUMBER_OF_COLORS_IN_PIXEL - 1, Utility::minimumBitsToStore(colorValue));
			bitset.setNumber(Utility::RED_POITION, values[3 * j + Utility::RED_POITION]);
			bitset.setNumber(Utility::GREEN_POSITION, values[3 * j + Utility::GREEN_POSITION]);
			bitset.setNumber(Utility::BLUE_POSITION, values[3 * j + Utility::BLUE_POSITION]);
			Color temp(bitset);
			row.pushBack(temp);
			//row[row.getSize() - 1].check();
		}
		data.pushBack(row);
	}
	return PixMap(Utility::GRAYMAP_NORMAL_MAGIC_NUMBER, width, height, header, colorValue, data).clone();
}

NetPbm* NetPbmCreator::readBitMapBinary(const MyString& filename, unsigned headerSkip, unsigned width, unsigned height, const Vector<MyString>& header)
{
	return nullptr;
}

NetPbm* NetPbmCreator::readGrayMapBinary(const MyString& filename, unsigned headerSkip, unsigned width, unsigned height, const Vector<MyString>& header, unsigned maxGray)
{
	return nullptr;
}

NetPbm* NetPbmCreator::readPixMapBinary(const MyString& filename, unsigned headerSkip, unsigned width, unsigned height, const Vector<MyString>& header, unsigned colorValue)
{
	return nullptr;
}

Vector<unsigned> strToVector(const MyString& str)
{
	Vector<unsigned> ret;

	bool lastSpace = false;
	unsigned currentNumber = 0;
	unsigned strLength = str.lenght();

	for (unsigned i = 0; i < strLength; i++)
	{
		if (str[i] == Utility::NUMBER_SEPARATOR)
		{
			ret.pushBack(currentNumber);
			currentNumber = 0;
			lastSpace = true;
			continue;
		}

		(currentNumber *= 10) += Utility::charToDigit(str[i]);
		lastSpace = false;
	}

	if (!lastSpace)
		ret.pushBack(currentNumber);

	return ret;
}

unsigned characterCount(const Vector<MyString>& text)
{
	unsigned ans = 0;
	unsigned size = text.getSize();
	for (unsigned i = 0; i < size; i++)
	{
		ans += text[i].lenght() + 2;//'\n'
	}
	return ans;
}
