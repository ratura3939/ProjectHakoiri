#pragma once
#include "RoomBase.h"
class Living :public RoomBase
{
public:
	Living(int roomImg, int sizeX, int sizeY,
		std::vector<std::vector<int>>::iterator map, std::vector<std::vector<int>>::iterator obj,
		int* mapchip);	//�R���X�g���N�^
	~Living(void);
	void SetParam(void) override; //�p�����[�^�̐ݒ�
};

