#pragma once
#include "RoomBase.h"
class Goal :public RoomBase
{
public:
	Goal(int roomImg, int sizeX, int sizeY,
		std::vector<std::vector<int>>::iterator map, std::vector<std::vector<int>>::iterator obj,
		int* mapchip);	//�R���X�g���N�^
	~Goal(void);
	void SetParam(void) override; //�p�����[�^�̐ݒ�
};

