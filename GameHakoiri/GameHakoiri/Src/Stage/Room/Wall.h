#pragma once
#include "RoomBase.h"
class Wall :public RoomBase
{
public:
	Wall(int roomImg);	//�R���X�g���N�^
	~Wall(void);
	void SetParam(void) override; //�p�����[�^�̐ݒ�
};

