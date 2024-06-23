#pragma once
#include "CommandVector.h"

class CollageCommand : public CommandVector
{
public:
	CollageCommand(Vector<Polymorphic_Ptr<NetPbm>>& data, unsigned img1Idx, unsigned img2Idx,
		bool isHorizontal, const MyString& saveFileName);

	void execute() override;
	void undo() override;
	CommandVector* clone()const override;
	MyString message()const override;

	~CollageCommand() = default;
private:
	unsigned img1Idx = 0;
	unsigned img2Idx = 0;
	bool isHorizontal = false;
	MyString saveFileName;

	NetPbm* collageBitMaps(const BitMap* img1, const BitMap* img2)const;
	NetPbm* collageGrayMaps(const GrayMap* img1, const GrayMap* img2)const;
	NetPbm* collagePixMaps(const PixMap* img1, const PixMap* img2)const;
};
