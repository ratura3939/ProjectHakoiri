#pragma once
#include"RoomBase.h"

class Wasitu :public RoomBase
{
public:
	Wasitu(int roomImg, int sizeX, int sizeY,
		std::vector<std::vector<int>>::iterator map, std::vector<std::vector<int>>::iterator obj,
		int* mapchip);	//�R���X�g���N�^
	~Wasitu(void);

	void SetParam(void) override; //�p�����[�^�̐ݒ�
};