#pragma once
#include "RoomBase.h"
class None : public RoomBase
{
public:
	None(int roomImg);
	~None(void);

	void SetParam(void)override;
	//void DrawPazzle(void)override;

	//void ChangeRole(RoomBase::TYPE type, int clr);
};

