#include<DxLib.h>
#include"../../Common/Vector2.h"
#include"RoomBase.h"
#include "None.h"

//�p�����[�^�̐ݒ�
void None::SetParam(void)
{
	PazzleSize_ = { 1.0f,1.0f };
	StealthSize_ = { 0.0f,0.0f };
	type_ = RoomBase::TYPE::NONE;

	//�e�X�g�p
	//dbgColor_ = 0x8b4513;
	dbgColor_ = 0x000000;
}

//void None::DrawPazzle(void)
//{
//	if (RoomBase::GetRoomType() == RoomBase::TYPE::NONE)
//	{
//		Vector2 pos = pzlPos_.ToVector2();
//		DrawBox(pos.x_, pos.y_,
//			pos.x_ + static_cast<int>(pieceSize_.x_),
//			pos.y_ + static_cast<int>(pieceSize_.y_),
//			dbgColor_, true);
//
//		//�g�̕`��
//		if (isCursor_)
//		{
//			DrawGraph(pos.x_, pos.y_, frameImg_, true);
//		}
//	}
//}