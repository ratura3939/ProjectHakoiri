#pragma once
#include "RoomBase.h"
class Living :public RoomBase
{
public:
	Living(int roomImg);
	~Living(void);
	void SetParam(void) override; //�p�����[�^�̐ݒ�
};

