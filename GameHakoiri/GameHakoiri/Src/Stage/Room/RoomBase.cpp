#include<DxLib.h>
#include"../../Common/Vector2.h"

#include"RoomBase.h"

//�R���X�g���N�^
//********************************************************
RoomBase::RoomBase(int roomImg, int sizeX, int sizeY,
	std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
	int* mapchip)
{
	roomImg_ = roomImg;
	mapSize_.x_ = sizeX;
	mapSize_.y_ = sizeY;

	map_ = map;
	obj_ = obj;
	mapchip_ = mapchip;


	type_ = TYPE::NONE;
	pzlPos_ = { 0.0f,0.0f };
	mapPos_ = { 0.0f,0.0f };
	pieceSize_ = { 1.0f,1.0f };
	mapMaxSize_ = { 1.0f,1.0f };
	isCursor_ = false;
	isChange_ = false;
	isDrawRoom_ = false;
	isDrawStealth_ = true;	//�}�b�v�̏�񂪂��邽�ߕ`�悷��
}
RoomBase::RoomBase(int roomImg)
{
	roomImg_ = roomImg;

	type_ = TYPE::NONE;
	pzlPos_ = { 0.0f,0.0f };
	pieceSize_ = { 1.0f,1.0f };

	isCursor_ = false;
	isChange_ = false;
	isDrawRoom_ = false;
	isDrawStealth_ = false;	//�}�b�v�̏�񂪂Ȃ����ߕ`�悵�Ȃ�
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
	if (!isDrawRoom_) { return; }

	Vector2 pos = pzlPos_.ToVector2();
	DrawGraph(pos.x_, pos.y_,
		roomImg_, true);
}

//�X�e���X�V�[���ɂ����镔���̕`��
//********************************************************
void RoomBase::DrawStealth(void)
{
	//�}�b�v��\�����Ȃ��Ƃ���͕`�揈�����s��Ȃ�
	if (!isDrawStealth_) { return; }

	Vector2F pos = mapPos_;

	for (int y = 0; y < mapSize_.y_; y++)
	{
		for (int x = 0; x < mapSize_.x_; x++)
		{
			//map���C���[�̕`��
			int mapchip = map_[y][x];
			DrawGraph(pos.x_, pos.y_,
				mapchip_[mapchip],
				false);

			//obj���C���[�̕`��
			mapchip = obj_[y][x];
			if (mapchip != -1)		//�摜�����݂���Ƃ�
			{
				DrawGraph(pos.x_, pos.y_,
					mapchip_[mapchip],
					true);
			}
			pos.x_ += UNIT_STEALTH_SIZE_X;
		}
		pos.x_ = 0;
		pos.y_ += UNIT_STEALTH_SIZE_Y;
	}
	
}
#pragma endregion



//���
//********************************************************
bool RoomBase::Release(void)
{

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