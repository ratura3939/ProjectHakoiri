#include<DxLib.h>
#include"RoomBase.h"
#include "Entrance.h"

//�p�����[�^�̐ݒ�
void Entrance::SetParam(void)
{
	PazzleSize_ = { 2.0f,1.0f };
	StealthSize_ = { 60.0f,30.0f };
	type_ = RoomBase::TYPE::ENTRANCE;

	//�摜�̊i�[
	frameImg_ = LoadGraph("Data/Img/frame_oblong_2.png");

	//�e�X�g�p
	dbgColor_ = 0xff8c00;
}