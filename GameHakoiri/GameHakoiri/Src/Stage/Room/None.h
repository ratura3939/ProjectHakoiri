#pragma once
#include "RoomBase.h"
class None : public RoomBase
{
public:
	None(int roomImg, int sizeX, int sizeY,
		std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
		int* mapchip);	//�R���X�g���N�^
	~None(void);

	void SetParam(void)override;
};

