#pragma once
#include "RoomBase.h"
class Entrance :public RoomBase
{
public:
	Entrance(int roomImg, int sizeX, int sizeY,
		std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
		int* mapchip);	//�R���X�g���N�^
	Entrance(int roomImg);	//�R�s�[�R���X�g���N�^
	~Entrance(void);
	void SetParam(void) override; //�p�����[�^�̐ݒ�

};

