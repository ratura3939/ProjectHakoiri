#pragma once
#include "RoomBase.h"
class Storage :public RoomBase
{
public:
	Storage(int roomImg, int sizeX, int sizeY,
		std::vector<std::vector<int>>::iterator map, std::vector<std::vector<int>>::iterator obj,
		int* mapchip);	//�R���X�g���N�^
	~Storage(void);
	void SetParam(void) override; //�p�����[�^�̐ݒ�
};

