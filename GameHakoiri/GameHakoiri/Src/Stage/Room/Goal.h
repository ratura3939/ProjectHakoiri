#pragma once
#include "RoomBase.h"
class Goal :public RoomBase
{
public:
	Goal(int roomImg);	//�R���X�g���N�^
	~Goal(void);
	void SetParam(void) override; //�p�����[�^�̐ݒ�
};

