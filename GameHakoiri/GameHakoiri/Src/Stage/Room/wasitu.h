#pragma once
#include"RoomBase.h"

class Wasitu :public RoomBase
{
public:
	Wasitu(int roomImg, int sizeX, int sizeY);
	~Wasitu(void);

	void SetParam(void) override; //�p�����[�^�̐ݒ�
};