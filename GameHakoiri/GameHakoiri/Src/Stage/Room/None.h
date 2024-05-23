#pragma once
#include "RoomBase.h"
class None : public RoomBase
{
public:
	None(int roomImg, int sizeX, int sizeY);
	~None(void);

	void SetParam(void)override;
};

