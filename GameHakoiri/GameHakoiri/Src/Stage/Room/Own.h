#pragma once
#include "RoomBase.h"
class Own :public RoomBase
{
public:
	Own(int roomImg, int sizeX, int sizeY,
		std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
		int* mapchip);	//�R���X�g���N�^
	Own(int roomImg);	//�R�s�[�R���X�g���N�^
	~Own(void);
	void SetParam(void) override; //�p�����[�^�̐ݒ�

};

