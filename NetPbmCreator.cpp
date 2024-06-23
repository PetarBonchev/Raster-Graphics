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

	ifs.close();

	return new BitMap(Utility::BITMAP_NORMAL_MAGIC_NUMBER, width, height, header, filename, data);
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

	ifs.close();

	return new GrayMap(Utility::GRAYMAP_NORMAL_MAGIC_NUMBER, width, height, header, filename, maxGray, data);
}

NetPbm* NetPbmCreator::readPixMap(const MyString& filename, unsigned headerSkip, unsigned width, unsigned height, const Vector<MyString>& header, unsigned colorValue)
{
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
			if (values[3 * j + Utility::RED_POSITION] > colorValue || values[3 * j + Utility::GREEN_POSITION] > colorValue || values[3 * j + Utility::BLUE_POSITION] > colorValue)
				throw std::logic_error("invalid data");

			BitSet bitset(Utility::NUMBER_OF_COLORS_IN_PIXEL - 1, Utility::minimumBitsToStore(colorValue));
			bitset.setNumber(Utility::RED_POSITION, values[3 * j + Utility::RED_POSITION]);
			bitset.setNumber(Utility::GREEN_POSITION, values[3 * j + Utility::GREEN_POSITION]);
			bitset.setNumber(Utility::BLUE_POSITION, values[3 * j + Utility::BLUE_POSITION]);
			Color temp(bitset);
			row.pushBack(temp);
			//row[row.getSize() - 1].check();
		}
		data.pushBack(row);
	}

	ifs.close();

	return new PixMap(Utility::PIXMAP_NORMAL_MAGIC_NUMBER, width, height, header, filename, colorValue, data);
}

NetPbm* NetPbmCreator::readBitMapBinary(const MyString& filename, unsigned headerSkip, unsigned width, unsigned height, const Vector<MyString>& header)
{
	std::ifstream ifs(filename.c_str(), std::ios::binary);

	if (!ifs.is_open())
		throw std::logic_error("invalid file location");

	ifs.seekg(headerSkip);

	Vector<BitSet> data;
	for (unsigned i = 0; i < height; i++)
	{
		BitSet row(width - 1, Utility::DEFAULT_MAX_BIT_VALUE);
		for (unsigned j = 0; j < width; j++)
		{
			uint8_t bit;
			ifs.read((char*)&bit, sizeof(uint8_t));

			if (!Utility::isBit((uint8_t)bit))
				throw std::logic_error("invalid data");

			row.setNumber(j, bit);
		}
		data.pushBack(std::move(row));
	}

	ifs.close();

	return new BitMap(Utility::BITMAP_BINARY_MAGIC_NUMBER, width, height, header, filename, data);
}

NetPbm* NetPbmCreator::readGrayMapBinary(const MyString& filename, unsigned headerSkip, unsigned width, unsigned height, const Vector<MyString>& header, unsigned maxGray)
{
	unsigned capacity = Utility::minimumBitsToStore(maxGray);

	std::ifstream ifs(filename.c_str(),std::ios::binary);

	if (!ifs.is_open())
		throw std::logic_error("invalid file location");

	ifs.seekg(headerSkip);

	Vector<BitSet> data;
	for (unsigned i = 0; i < height; i++)
	{
		BitSet row(width - 1, capacity);

		for (unsigned j = 0; j < width; j++)
		{
			uint8_t gray;
			ifs.read((char*)&gray, sizeof(uint8_t));

			if ((uint8_t)gray > (uint8_t)maxGray)
				throw std::logic_error("invalid data");

			row.setNumber(j, gray);
		}
		data.pushBack(row);
	}

	ifs.close();

	return new GrayMap(Utility::GRAYMAP_BINARY_MAGIC_NUMBER, width, height, header, filename, maxGray, data);
}

NetPbm* NetPbmCreator::readPixMapBinary(const MyString& filename, unsigned headerSkip, unsigned width, unsigned height, const Vector<MyString>& header, unsigned colorValue)
{
	unsigned capacity = Utility::minimumBitsToStore(colorValue);

	std::ifstream ifs(filename.c_str(),std::ios::binary);

	if (!ifs.is_open())
		throw std::logic_error("invalid file location");

	ifs.seekg(headerSkip);

	Vector<Vector<Color>> data;
	for (unsigned i = 0; i < height; i++)
	{
		Vector<Color> row;

		for (unsigned j = 0; j < width; j++)
		{
			uint8_t red, green, blue;
			ifs.read((char*)&red, sizeof(uint8_t));
			ifs.read((char*)&green, sizeof(uint8_t));
			ifs.read((char*)&blue, sizeof(uint8_t));

			//std::cout << colorValue << std::endl;
			//std::cout << "rgb: " << (uint8_t)red << " " << (uint8_t)green << " " << (uint8_t)blue << std::endl;
			if ((uint8_t)red > (uint8_t)colorValue || (uint8_t)green > (uint8_t)colorValue || (uint8_t)blue > (uint8_t)colorValue)
				throw std::logic_error("invalid data");

			BitSet bitset(Utility::NUMBER_OF_COLORS_IN_PIXEL - 1, Utility::minimumBitsToStore(colorValue));
			bitset.setNumber(Utility::RED_POSITION, green);
			bitset.setNumber(Utility::GREEN_POSITION, blue);
			bitset.setNumber(Utility::BLUE_POSITION, red);
			Color temp(bitset);
			row.pushBack(temp);
			//row[row.getSize() - 1].check();
		}
		data.pushBack(row);
	}

	ifs.close();

	return new PixMap(Utility::PIXMAP_BINARY_MAGIC_NUMBER, width, height, header, filename, colorValue, data);
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
