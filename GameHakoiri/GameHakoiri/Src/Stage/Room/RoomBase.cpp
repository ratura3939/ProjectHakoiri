#include<DxLib.h>
#include"../../Application.h"
#include"../../Common/Vector2.h"
#include"../../Manager/SceneManager.h"
#include"../../Manager/StageManager.h"
#include"../../Manager/Camera.h"

#include"RoomBase.h"

//�R���X�g���N�^
//********************************************************
RoomBase::RoomBase(int roomImg, int sizeX, int sizeY,
	std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
	int* mapchip)
{
	roomImg_ = roomImg;
	mapSize_.x = sizeX;
	mapSize_.y = sizeY;

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
	pieceSize_ = { pazzleSize_.x * static_cast<float>(StageManager::UNIT_PAZZLE_SIZE_X),
		pazzleSize_.y * static_cast<float>(StageManager::UNIT_PAZZLE_SIZE_Y) };

	//�}�b�v�̑傫���̐ݒ�
	mapMaxSize_ = { mapSize_.x * StageManager::UNIT_STEALTH_SIZE_X,
		mapSize_.y * StageManager::UNIT_STEALTH_SIZE_Y };


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
	DrawGraph(pos.x, pos.y,
		roomImg_, true);
}

//�X�e���X�V�[���ɂ����镔���̕`��
//********************************************************
void RoomBase::DrawStealth(void)
{
	//�}�b�v��\�����Ȃ��Ƃ���͕`�揈�����s��Ȃ�
	if (!isDrawStealth_) { return; }

	Vector2F pos = mapPos_;
	auto cameraPos = SceneManager::GetInstance().GetCamera().GetPos();

	for (int y = 0; y < mapSize_.y; y++)
	{
		for (int x = 0; x < mapSize_.x; x++)
		{
			//map���C���[�̕`��
			int mapchip = map_[y][x];
			DrawGraph(pos.x-cameraPos.x,
				pos.y-cameraPos.y,
				mapchip_[mapchip],
				false);

			mapchip = obj_[y][x];
			if (mapchip != -1)		//�摜�����݂���Ƃ�
			{
				DrawGraph(
					pos.x - cameraPos.x,
					pos.y - cameraPos.y,
					mapchip_[mapchip],
					true);
			}

			pos.x += StageManager::UNIT_STEALTH_SIZE_X;
		}
		pos.x = 0;
		pos.y += StageManager::UNIT_STEALTH_SIZE_Y;
	}
	
}
void RoomBase::DrawStealthObject(void)
{
	Vector2F pos = mapPos_;
	pos.x += StageManager::UNIT_STEALTH_SIZE_X / 2;
	pos.y += StageManager::UNIT_STEALTH_SIZE_Y / 2;
	auto cameraPos = SceneManager::GetInstance().GetCamera().GetPos();

	for (int y = 0; y < mapSize_.y; y++)
	{
		for (int x = 0; x < mapSize_.x; x++)
		{
			//obj���C���[�̕`��
			int mapchip = obj_[y][x];
			if (mapchip != -1)		//�摜�����݂���Ƃ�
			{
				DrawRotaGraph(
					pos.x - cameraPos.x,
					pos.y - cameraPos.y,
					1.0f,
					Utility::DEG2RAD,
					mapchip_[mapchip],
					true,
					false);
			}
			pos.x += StageManager::UNIT_STEALTH_SIZE_X;
		}
		pos.x = StageManager::UNIT_STEALTH_SIZE_X / 2;
		pos.y += StageManager::UNIT_STEALTH_SIZE_Y;
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

RoomBase::TYPE RoomBase::GetRoomType(void)const
{
	return type_;
}
#pragma endregion



#pragma region �p�Y����SetGet

void RoomBase::SetPzlPos(Vector2F pos)
{
	pzlPos_ = pos;
}
Vector2F RoomBase::GetPzlPos(void)const
{
	return pzlPos_;
}
#pragma endregion

#pragma region �}�b�v��SetGet

void RoomBase::SetMapPos(Vector2F pos)
{
	mapPos_ = pos;
}

Vector2F RoomBase::GetMapPos(void)const
{
	return mapPos_;
}
#pragma endregion

#pragma region �J�[�\����SetGet

void RoomBase::SetIsCursor(bool flag)
{
	isCursor_ = flag;
}

bool RoomBase::GetIsCursor(void)const
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
Vector2F RoomBase::GetRoomSize(void) const
{
	return mapSize_;
}
int RoomBase::GetObj(Vector2 pos) const
{
	return obj_[pos.y][pos.x];
}
int RoomBase::GetMapchip(Vector2 pos) const
{
	return map_[pos.y][pos.x];
}
bool RoomBase::IsOneDownObj(Vector2 pos) const
{
	pos.y++;
	if (obj_[pos.y][pos.x] == -1)	//�I�u�W�F�N�g�����������Ă��Ȃ�������
	{
		return true;
	}
	return false;
}
#pragma endregion

//�������Ƃ̃p�����[�^�ݒ�
//********************************************************
void RoomBase::SetParam(void)
{
	//���̊֐��͔h���悲�Ƃ̂��̂Ȃ̂Ŋ֌W�Ȃ�
}