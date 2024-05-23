#include<DxLib.h>
#include"../../Common/Vector2.h"

#include"RoomBase.h"

//�R���X�g���N�^
//********************************************************
RoomBase::RoomBase(int roomImg, int sizeX, int sizeY)
{
	roomImg_ = roomImg;
	mapSize_.x_ = sizeX;
	mapSize_.y_ = sizeY;
	type_ = TYPE::NONE;
	pzlPos_ = { 0.0f,0.0f };
	mapPos_ = { 0.0f,0.0f };
	pieceSize_ = { 1.0f,1.0f };
	mapMaxSize_ = { 1.0f,1.0f };
	isCursor_ = false;
	isChange_ = false;
}
//�f�X�g���N�^
//********************************************************
RoomBase::~RoomBase(void)
{

}

//������
//********************************************************
bool RoomBase::Init(void)
{
	pzlPos_ = { 0.0f,0.0f };
	mapPos_ = { 0.0f,0.0f };
	isCursor_ = false;
	isChange_ = false;

	//�e�����̐ݒ�
	SetParam();
	//��̑傫���̐ݒ�
	pieceSize_ = { pazzleSize_.x_ * static_cast<float>(UNIT_PAZZLE_SIZE_X),
		pazzleSize_.y_ * static_cast<float>(UNIT_PAZZLE_SIZE_Y) };

	//�}�b�v�̑傫���̐ݒ�
	mapMaxSize_ = { mapSize_.x_ * UNIT_STEALTH_SIZE_X,
		mapSize_.y_ * UNIT_STEALTH_SIZE_Y };


	//�������������I�������̂�
	return true;
}

#pragma region �`��

//�p�Y���V�[���ɂ����镔���̕`��
//********************************************************
void RoomBase::DrawPazzle(void)
{
	Vector2 pos = pzlPos_.ToVector2();
	if (isDrawRoom_)
	{
		DrawGraph(pos.x_, pos.y_,
			roomImg_, true);
	}

	/*DrawBox(pos.x_, pos.y_,
		pos.x_ + static_cast<int>(pieceSize_.x_),
		pos.y_ + static_cast<int>(pieceSize_.y_),
		dbgColor_, true);*/
}

//�X�e���X�V�[���ɂ����镔���̕`��
//********************************************************
void RoomBase::DrawStealth(void)
{
	//�}�b�v��\�����Ȃ��Ƃ���͕`�揈�����s��Ȃ�
	if (type_ == TYPE::NONE || type_ == TYPE::WALL || type_ == TYPE::GOAL) { return; }


	
}
#pragma endregion



//���
//********************************************************
bool RoomBase::Release(void)
{
	//�摜�̊J��
	DeleteGraph(pieceImg_);

	//�������������I�������̂�
	return true;
}

#pragma region �����̎�ނ�SetGet

void RoomBase::SetRoomType(TYPE type)
{
	type_ = type;
}

RoomBase::TYPE RoomBase::GetRoomType(void)
{
	return type_;
}
#pragma endregion



#pragma region �p�Y����SetGet

void RoomBase::SetPzlPos(Vector2F pos)
{
	pzlPos_ = pos;
}
Vector2F RoomBase::GetPzlPos(void)
{
	return pzlPos_;
}
#pragma endregion

#pragma region �}�b�v��SetGet

void RoomBase::SetMapPos(Vector2F pos)
{
	mapPos_ = pos;
}

Vector2F RoomBase::GetMapPos(void)
{
	return mapPos_;
}
#pragma endregion

#pragma region �J�[�\����SetGet

void RoomBase::SetIsCursor(bool flag)
{
	isCursor_ = flag;
}

bool RoomBase::GetIsCursor(void)
{
	return isCursor_;
}
bool RoomBase::IsChange(void)
{
	return isChange_;
}
void RoomBase::SetIsChange(bool flag)
{
	isChange_ = flag;
}
void RoomBase::SetIsDrawRoom(bool flag)
{
	isDrawRoom_ = flag;
}
#pragma endregion

//�������Ƃ̃p�����[�^�ݒ�
//********************************************************
void RoomBase::SetParam(void)
{
	//���̊֐��͔h���悲�Ƃ̂��̂Ȃ̂Ŋ֌W�Ȃ�
}