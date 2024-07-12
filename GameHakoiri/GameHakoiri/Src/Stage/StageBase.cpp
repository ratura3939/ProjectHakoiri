#include<DxLib.h>
#include<iostream>

#include"../Application.h"
#include"../Utility/Utility.h"
#include"../Manager/ResourceManager.h"
#include"../Manager/StageManager.h"
#include"Room/RoomBase.h"
#include"Room/None.h"
#include"Room/Own.h"
#include"Room/Wasitu.h"
#include"Room/Living.h"
#include"Room/Bath.h"
#include"Room/Storage.h"
#include"Room/Kitchen.h"
#include"Room/Entrance.h"
#include"Room/Wall.h"
#include"Room/Goal.h"


#include"StageBase.h"

//�R���X�g���N�^
//********************************************************
StageBase::StageBase(std::vector<std::vector<int>>::iterator pzlIt, int pzlSizeX, int pzlSizeY,
	std::vector<std::vector<int>> map[], std::vector<std::vector<int>> obj[],
	int* roomImg, int* mapchip[])
{
	pzlCsv_ = pzlIt;
	size_.x = pzlSizeX;
	size_.y = pzlSizeY;

	mapCsv_ = map;
	objCsv_ = obj;
	roomImg_ = roomImg;
	mapchip_ = mapchip;

	roomKey_ = "00";
	doorSpare_ = StageManager::DOOR_Y::NONE;
}
//�f�X�g���N�^
//********************************************************
StageBase::~StageBase(void)
{

}

//������
//********************************************************
bool StageBase::Init(void)
{
	frameAnim_ = 0;
	//�t���O�̏�����
	SetFrameFlash(false);
	SetIsMoveRoom(true);
	SetIsSecondRoom(false);
	SetIsGoal(false);

	//�e�X�e�[�W�ɂ��ݒ�
	SetParam();
	//�p�Y���z�u�̓ǂݍ���
	//LoadPazzle();
	//�摜�ǂݍ���
	LoadImgs();

	Vector2F pos{ static_cast<float>(Application::SCREEN_SIZE_X / 4),
		static_cast<float>(Application::SCREEN_SIZE_Y / 4) };

	goalPos_ = { 0,0 };


	for (int y = 0; y < size_.y; y++)
	{
		for (int x = 0; x < size_.x; x++)
		{
			RoomBase* r = nullptr;

			switch (static_cast<RoomBase::TYPE>(pzlCsv_[y][x]))
			{
			//�󂫃X�y�[�X
			case RoomBase::TYPE::NONE: 
				r = new None(roomImg_[static_cast<int>(RoomBase::TYPE::NONE)]);
				r->Init();
				break;

			//����
			case RoomBase::TYPE::OWN: 
				r = new Own(roomImg_[static_cast<int>(RoomBase::TYPE::OWN)],
					StageManager::OBLONG_2_MAP_X, StageManager::OBLONG_2_MAP_Y,
					mapCsv_[static_cast<int>(RoomBase::TYPE::OWN)],
					objCsv_[static_cast<int>(RoomBase::TYPE::OWN)],
					mapchip_[static_cast<int>(StageManager::MAPCHIP::INTERIA)]);
				r->Init();
				//���������������̂������`�̂Q�R�}�ڂ�������
				if (CheckInstanceLeft(y, x, r)){ r = GetSecondRoomInstance(r); }
				break;
			//�a��
			case RoomBase::TYPE::WASITU:
				r = new Wasitu(roomImg_[static_cast<int>(RoomBase::TYPE::WASITU)],
					StageManager::NOMAL_MAP_X, StageManager::NOMAL_MAP_Y,
					mapCsv_[static_cast<int>(RoomBase::TYPE::WASITU)],
					objCsv_[static_cast<int>(RoomBase::TYPE::WASITU)],
					mapchip_[static_cast<int>(StageManager::MAPCHIP::INTERIA)]);
				r->Init();
				break;
			//����
			case RoomBase::TYPE::LIVING:
				r = new Living(roomImg_[static_cast<int>(RoomBase::TYPE::LIVING)],
					StageManager::OBLONG_MAP_X, StageManager::OBLONG_MAP_Y,
					mapCsv_[static_cast<int>(RoomBase::TYPE::LIVING)],
					objCsv_[static_cast<int>(RoomBase::TYPE::LIVING)],
					mapchip_[static_cast<int>(StageManager::MAPCHIP::INTERIA)]);
				r->Init();
				//���������������̂������`�̂Q�R�}�ڂ�������
				if (CheckInstanceUp(y, x, r)) { r = GetSecondRoomInstance(r); }
				break;
			//���C
			case RoomBase::TYPE::BATH: 
				r = new Bath(roomImg_[static_cast<int>(RoomBase::TYPE::BATH)],
					StageManager::NOMAL_MAP_X, StageManager::NOMAL_MAP_Y,
					mapCsv_[static_cast<int>(RoomBase::TYPE::BATH)],
					objCsv_[static_cast<int>(RoomBase::TYPE::BATH)],
					mapchip_[static_cast<int>(StageManager::MAPCHIP::BATH)]);
				r->Init();
				break;
			//���u
			case RoomBase::TYPE::STORAGE:
				r = new Storage(roomImg_[static_cast<int>(RoomBase::TYPE::STORAGE)],
					StageManager::NOMAL_MAP_X, StageManager::NOMAL_MAP_Y,
					mapCsv_[static_cast<int>(RoomBase::TYPE::STORAGE)],
					objCsv_[static_cast<int>(RoomBase::TYPE::STORAGE)],
					mapchip_[static_cast<int>(StageManager::MAPCHIP::INTERIA)]);
				r->Init();
				break;
			//�䏊
			case RoomBase::TYPE::KITCHEN: 
				r = new Kitchen(roomImg_[static_cast<int>(RoomBase::TYPE::KITCHEN)],
					StageManager::OBLONG_MAP_X, StageManager::OBLONG_MAP_Y,
					mapCsv_[static_cast<int>(RoomBase::TYPE::KITCHEN)],
					objCsv_[static_cast<int>(RoomBase::TYPE::KITCHEN)],
					mapchip_[static_cast<int>(StageManager::MAPCHIP::INTERIA)]);
				r->Init();
				//���������������̂������`�̂Q�R�}�ڂ�������
				if (CheckInstanceUp(y, x, r)) { r = GetSecondRoomInstance(r); }
				break;
			//����
			case RoomBase::TYPE::ENTRANCE: 
				r = new Entrance(roomImg_[static_cast<int>(RoomBase::TYPE::ENTRANCE)],
					StageManager::OBLONG_2_MAP_X, StageManager::OBLONG_2_MAP_Y,
					mapCsv_[static_cast<int>(RoomBase::TYPE::ENTRANCE)],
					objCsv_[static_cast<int>(RoomBase::TYPE::ENTRANCE)],
					mapchip_[static_cast<int>(StageManager::MAPCHIP::EXTERIA)]);
				r->Init();
				//���������������̂������`�̂Q�R�}�ڂ�������
				if (CheckInstanceLeft(y, x, r)) { r = GetSecondRoomInstance(r); }
				break;
			//��
			case RoomBase::TYPE::WALL:	
				r = new Wall(roomImg_[static_cast<int>(RoomBase::TYPE::WALL)]);
				r->Init();
				break;
			//�S�[��
			case RoomBase::TYPE::GOAL:
				r = new Goal(roomImg_[static_cast<int>(RoomBase::TYPE::GOAL)]);
				r->Init();
				goalPos_ = { x,y };
				break;
			}

			CreateKey(y, x);
			roomMng_[roomKey_] = r;//�z����Ɋi�[
			resetRoom_[roomKey_] = r->GetRoomType();
			resetRoomClone_[roomKey_] = r->IsClone();
			pzlPos_[roomKey_] = pos;

			//���W�̍X�V
			pos.x += static_cast<float>(StageManager::UNIT_PAZZLE_SIZE_X);
		}
		pos.x = static_cast<float>(Application::SCREEN_SIZE_X / 4);
		pos.y += static_cast<float>(StageManager::UNIT_PAZZLE_SIZE_Y);
	}

	//�����̃J�[�\���ݒ�
	for (int y = 0; y < size_.y; y++)
	{
		for (int x = 0; x < size_.x; x++)
		{
			CreateKey(y, x);
			if (!IsDontMoveBlock(roomKey_) &&
				roomMng_[roomKey_]->GetRoomType() != RoomBase::TYPE::NONE)
			{
				roomMng_[roomKey_]->SetIsCursor(true);
				//�������������I�������̂�
				return true;
			}
		}
	}
	//�������������I�������̂�
	return true;
}

bool StageBase::InitStealth(void)
{
	//���݂̃J�[�\��������
	roomMng_[roomKey_]->SetIsCursor(false);

	//�p�Y���`��̈ʒu�ύX
	Vector2F pos = { 0.0f,0.0f };

	for (int y = 0; y < size_.y; y++)
	{
		for (int x = 0; x < size_.x; x++)
		{
			CreateKey(y, x);
			pzlPos_[roomKey_] = pos;
			//���W�̍X�V
			pos.x += static_cast<float>(StageManager::UNIT_PAZZLE_SIZE_X);
		}
		pos.x = 0.0f;
		pos.y += static_cast<float>(StageManager::UNIT_PAZZLE_SIZE_Y);
	}


	//�ȑO�̃J�[�\�����\����
	for (int y = 0; y < size_.y; y++)
	{
		for (int x = 0; x < size_.x; x++)
		{
			CreateKey(y, x);
			roomMng_[roomKey_]->SetIsCursor(false);
		}
	}

	//�����ʒu�̏ꏊ���������[���L�[�𐶐�
	for (int y = 0; y < size_.y; y++)
	{
		for (int x = 0; x < size_.x; x++)
		{
			CreateKey(y, x);
			if (roomMng_[roomKey_]->GetRoomType() == RoomBase::TYPE::OWN)
			{
				//���ݒn�ɃJ�[�\���Z�b�g
				roomMng_[roomKey_]->SetIsCursor(true);
				//�������������I�������̂�
				return true;
			}
		}
	}

	//��������
	return false;
}

void StageBase::DrawObject(void)
{
	roomMng_[roomKey_]->DrawStealthObject();
}

#pragma region �X�V

void StageBase::Update(GameScene::MODE mode)
{
	switch (mode)
	{
	case GameScene::MODE::STEALTH:
		UpdateStealth();
		break;
	default:
		break;
	}
}

void StageBase::UpdateStealth(void)
{
}
#pragma endregion



#pragma region �`��

void StageBase::Draw(GameScene::MODE mode)
{
	switch (mode)
	{
	case GameScene::MODE::PAZZLE:
		DrawPazzle();
		break;
	case GameScene::MODE::STEALTH:
		DrawStealth();
		break;
	default:
		break;
	}
}
#pragma region �p�Y���V�[��

	void StageBase::DrawPazzle(void)
	{		
		frameAnim_++;

		//��̕`��
		for (int y = 0; y < size_.y; y++)
		{
			for (int x = 0; x < size_.x; x++)
			{
				CreateKey(y, x);
				roomMng_[roomKey_]->SetPzlPos(pzlPos_[roomKey_]);
				roomMng_[roomKey_]->DrawPazzle();
			}
			
		}
 		if (frameFlash_)
		{
			if (frameAnim_ % (Application::FPS / 2) < FRAME_INTERVAL)
			{
				//�g�̕`��
				DrawCursor();
			}
		}
		else
		{
			//�g�̕`��
			DrawCursor();
		}
	}

	#pragma endregion

#pragma region �J�[�\��

	void StageBase::DrawCursor(void)
	{
		Vector2 key = GetNowCursorPos();

		CreateKey(key.y, key.x);
		switch (roomMng_[roomKey_]->GetRoomType())
		{
			// �󂫃X�y�[�X
		case RoomBase::TYPE::NONE:
			//�a��
		case RoomBase::TYPE::WASITU:
			//���C
		case RoomBase::TYPE::BATH:
			//���u
		case RoomBase::TYPE::STORAGE:
			//��
		case RoomBase::TYPE::WALL:
			//�S�[��
		case RoomBase::TYPE::GOAL:
			SetCursorType(CURSOR::NORMAL);
			break;
			//�c��
			//����
		case RoomBase::TYPE::LIVING:
			//�䏊
		case RoomBase::TYPE::KITCHEN:
			SetCursorType(CURSOR::OBLONG);
			break;

			//����
			//����
		case RoomBase::TYPE::OWN:
			//����
		case RoomBase::TYPE::ENTRANCE:
			SetCursorType(CURSOR::OBLONG_2);
			break;
		}
		if (roomMng_[roomKey_]->GetIsCursor())
		{
			//�g�̕`��
			DrawGraph(pzlPos_[roomKey_].x, pzlPos_[roomKey_].y,
				frame_[static_cast<int>(type_)], true);
		}
	}

	
	
#pragma endregion

#pragma region �X�e���X

	void StageBase::DrawStealth(void)
	{
		roomMng_[roomKey_]->DrawStealth();
	}
#pragma endregion


#pragma endregion

//���
//********************************************************
bool StageBase::Release(void)
{
	//��

	for (int y = 0; y < size_.y; y++)
	{
		for (int x = 0; x < size_.x; x++)
		{
			CreateKey(y, x);
			roomMng_[roomKey_]->Release();
			delete roomMng_[roomKey_];
			roomMng_[roomKey_] = nullptr;
		}
	}

	//�������������I�������̂�
	return true;
}

//�X�e�[�W���Ƃ̃p�����[�^�ݒ�
//********************************************************
void StageBase::SetParam(void)
{
	//���̊֐��͔h���悲�Ƃ̂��̂Ȃ̂Ŋ֌W�Ȃ�
}
//�A�z�z��̃L�[����
//********************************************************
void StageBase::CreateKey(int y, int x)
{
	std::string key= std::to_string(y) + std::to_string(x);
	roomKey_ = key;
}

std::string StageBase::GetKey(void) const
{
	return roomKey_;
}

#pragma region �X�e���X�̂��낢��

//���ݕ`�悵�Ă���}�b�v�̍ő�T�C�Y���擾
//********************************************************
Vector2F StageBase::GetNowDrawMapSize(void)
{
	Vector2F mapMax = roomMng_[roomKey_]->GetRoomSize() *
		Vector2F {
		StageManager::UNIT_STEALTH_SIZE_X, StageManager::UNIT_STEALTH_SIZE_Y
	};
	return mapMax;
}

//�w�肵�����W�̓I�u�W�F�N�g�����邩
//********************************************************
bool StageBase::IsMapObj(Vector2 pMapPos)
{
	if (roomMng_[roomKey_]->GetObj(pMapPos) != -1)	//�w�肵���ꏊ�ɃI�u�W�F�N�g����������
	{
		return true;
	}
	return false;
}
bool StageBase::IsMoveRoom(void)
{
	return isMoveRoom_;
}
//�w�肳�ꂽ�ꏊ�̃I�u�W�F�N�g�擾
//********************************************************
int StageBase::GetObjNum(Vector2 pMapPos)
{
	return roomMng_[roomKey_]->GetObj(pMapPos);
}
//�w�肳�ꂽ�ꏊ�̃}�b�v�`�b�v�擾
//********************************************************
int StageBase::GetMapNum(Vector2 pMapPos)
{
	return roomMng_[roomKey_]->GetMapchip(pMapPos);
}
//���݂̕������g�p����}�b�v�`�b�v�̎�ނ�Ԃ��B
//********************************************************
StageManager::MAPCHIP StageBase::GetMapchipType(void)
{
	auto type = roomMng_[roomKey_]->GetRoomType();
	//Bath�̃}�b�v�`�b�v���g�p����̂�BathRoom�̂�
	if (type == RoomBase::TYPE::BATH)
	{
		return StageManager::MAPCHIP::BATH;
	}
	//Exteria�̃}�b�v�`�b�v���g�p����̂�EntranceRoom�̂�
	if (type == RoomBase::TYPE::ENTRANCE)
	{
		return StageManager::MAPCHIP::EXTERIA;
	}

	return StageManager::MAPCHIP::INTERIA;
}
RoomBase::ROOM_SHAPE StageBase::GetNowShape(void)
{
	return GetRoomShape(roomKey_);
}
//����ɃI�u�W�F�N�g�����邩�𒲂ׂ�
//********************************************************
bool StageBase::CheckOneDownObject(Vector2 pMapPos)
{
	return roomMng_[roomKey_]->IsOneDownObj(pMapPos);
}
//������ς���
//********************************************************
void StageBase::ChangeRoom(Vector2 pMapPos)
{
	//�h�A�̈ʒu�擾
	door_ = SearchDoor(pMapPos);
	//�����̈ړ���
	Vector2 move = { 0,0 };
	//�ړ���̕�����ێ�
	Vector2 afterRoom;
	//���݂̕�����ێ�
	auto nowRoom = roomKey_;
	//���݂̕�����roomKey����t�Z
	//roomKey=(yx)�Ȃ̂�10�Ŋ��������̏���Y,�]�肪X��\��
	afterRoom.y = stoi(nowRoom) / STRING_TO_INT;
	afterRoom.x = stoi(nowRoom) % STRING_TO_INT;
	
	//���̈ʒu�ɂ�镔���̈ړ��ʂ��v�Z
	if (door_.y == StageManager::DOOR_Y::TOP) 
	{ 
		//���̕�����
		move.y--; 

		//���݂̏ꏊ�������`�������ꍇ
		if (GetRoomShape(nowRoom)!=RoomBase::ROOM_SHAPE::NOMAL)	
		{
			//���ݕ����������ŁA�E��̔��������ꍇ
			if (GetRoomShape(nowRoom) == RoomBase::ROOM_SHAPE::OBLONG_SIDE && door_.x == StageManager::DOOR_X::RIGHT)
			{
				//���E�ړ�
				move += MoveLeftOrRight(door_.x);
			}
			//���ݕ������c���ŁA���E�̔�(��̉�)�������ꍇ
			if (GetRoomShape(nowRoom) == RoomBase::ROOM_SHAPE::OBLONG && doorSpare_ == StageManager::DOOR_Y::BOTTOM)
			{
				//��ւ̈ړ��ł͂Ȃ����ߍ�����߂�
				move.y++;
				//���E�ړ�
				move += MoveLeftOrRight(door_.x);
			}
		}
	}	

	else if (door_.y == StageManager::DOOR_Y::BOTTOM) 
	{
		//����̕�����
		move.y++;

		//���ݕ����������ŁA�E��̔��������ꍇ
		if (GetRoomShape(nowRoom) == RoomBase::ROOM_SHAPE::OBLONG_SIDE && door_.x == StageManager::DOOR_X::RIGHT)
		{
			//���E�ړ�
			move += MoveLeftOrRight(door_.x);
		}
		//���ݕ������c��
		if (GetRoomShape(nowRoom) == RoomBase::ROOM_SHAPE::OBLONG )
		{
			if (doorSpare_ == StageManager::DOOR_Y::BOTTOM)
			{
				//�c�j�}�X�̕����̉��ւ̈ړ��Ȃ̂Ńj�}�X�������邽��
				move.y++;
			}
			//���E�̔�(���̏�)�������ꍇ
			if (doorSpare_ == StageManager::DOOR_Y::TOP)
			{
				//���E�ړ�
				move += MoveLeftOrRight(door_.x);
			}
		}
	}	
	else if (door_.y == StageManager::DOOR_Y::MIDDLE)
	{
		//���E�ړ�
		move += MoveLeftOrRight(door_.x);
		//���ݕ����������ŁA�E��̔��������ꍇ
		if (GetRoomShape(nowRoom) == RoomBase::ROOM_SHAPE::OBLONG_SIDE && door_.x == StageManager::DOOR_X::RIGHT)
		{
			//���E�ړ�
			move += MoveLeftOrRight(door_.x);
		}
	}

	afterRoom += move;
	MoveRoom(afterRoom, nowRoom);
}
//�o��̂Ɏg�p�����h�A�̈ʒu��n��
StageManager::DOOR StageBase::GetDoorPos(void) const
{
	return door_;
}
StageManager::DOOR_Y StageBase::GetDoorPosSecond(void) const
{
	return doorSpare_;
}
bool StageBase::IsSecondRoom(void)const
{
	return isSecondRoom_;
}
bool StageBase::IsGoal(void) const
{
	return isGoal_;
}
//�S�[���ɂȂ��镔�������邩�ǂ���
bool StageBase::CanGoal(void)
{
	auto pos = goalPos_;
	pos.y--;
	CreateKey(pos.y, pos.x);
	if (roomMng_[roomKey_]->GetRoomType() != RoomBase::TYPE::NONE)
	{
		return true;
	}
	return false;
}
void StageBase::MoveRoom(const Vector2 after, const std::string prvKey)
{
	SetIsMoveRoom(true);	//�t���O���Z�b�g �ړ��ł���O��
	SetIsSecondRoom(false);
	roomMng_[roomKey_]->SetIsCursor(false);

	auto moveAfter = after;
	

	//�ړ���̕����̌�����
	CreateKey(moveAfter.y, moveAfter.x);
	auto type = roomMng_[roomKey_]->GetRoomType();

	//�ړ��悪�S�[����������
	if (type == RoomBase::TYPE::GOAL)
	{
		SetIsGoal(true);
		return;
	}

	//�ړ��悪�����ł͂Ȃ�������
	if (type == RoomBase::TYPE::NONE ||
		type == RoomBase::TYPE::WALL)
	{
		roomKey_ = prvKey;
		SetIsMoveRoom(false);	//�t���O�Z�b�g
		roomMng_[roomKey_]->SetIsCursor(true);

		return;
	}

	//�����`�Ŏ��̂ł͂Ȃ��ق��ɏo���Ƃ�
	if (GetRoomShape(roomKey_) != RoomBase::ROOM_SHAPE::NOMAL)
	{
		
		auto r = CreateInstance4Confirmation(type);
		//�c���̎��̒���
		if (GetRoomShape(type) == RoomBase::ROOM_SHAPE::OBLONG)
		{
			if (CheckInstanceUp(moveAfter.y, moveAfter.x, r))
			{
				moveAfter.y--;
				CreateKey(moveAfter.y, moveAfter.x);
				SetIsSecondRoom(true);
			}
		}
		//�����̎��̒���
		if (GetRoomShape(type) == RoomBase::ROOM_SHAPE::OBLONG_SIDE)
		{
			if (CheckInstanceLeft(moveAfter.y, moveAfter.x, r))
			{
				moveAfter.x--;
				CreateKey(moveAfter.y, moveAfter.x);
				SetIsSecondRoom(true);
			}
		}
	}

	//�ړ���ɃJ�[�\���Z�b�g
	roomMng_[roomKey_]->SetIsCursor(true);
}
//���E�ړ�
//********************************************************
Vector2 StageBase::MoveLeftOrRight(const StageManager::DOOR_X door)
{
	if (door == StageManager::DOOR_X::LEFT) { return { -1,0 }; }	//�����
	if (door == StageManager::DOOR_X::RIGHT) { return { 1,0 }; }	//��E��
}
//�h�A�̈ʒu����
//********************************************************
StageManager::DOOR StageBase::SearchDoor(const Vector2 pMapPos)
{
	//�h�A�ʒu�ۑ��p
	StageManager::DOOR ret;
	//player�ʒu
	Vector2 pPos = pMapPos;
	//����X�y�A�̃��Z�b�g
	doorSpare_ = StageManager::DOOR_Y::NONE;

	//���̈ʒu�������邽�ߕ����𕪊��B
	auto size = roomMng_[roomKey_]->GetRoomSize().ToVector2();

	size.x /= StageManager::SPLIT_ROOM_X;
	size.y /= StageManager::SPLIT_ROOM_Y;

	//�T�������ʒu
	Vector2 startPos = { 0,0 };

	ret = SplitRoom(pPos, size,startPos);

	//�c���̏ꍇ�͓��ڂ̔��肪�K�v
	if (roomMng_[roomKey_]->GetRoomType() == RoomBase::TYPE::KITCHEN ||
		roomMng_[roomKey_]->GetRoomType() == RoomBase::TYPE::LIVING)
	{
		//���ڂ̔���͈��ڂŕ��������㒆��������ɕ�����������肷��(�����̈ꕔ���Y�[�����銴��)
		//�v���C���[�̏ꏊ�͈��ڂ̕����̉e�����󂯂�
		//player���������̋����ɐݒ�
		pPos.y -= size.y * (static_cast<int>(ret.y) - 1);

		//�ړ��̉����ݒ�
		size.y /= static_cast<int>(StageManager::DOOR_Y::BOTTOM);	//�T�C�Y���O����

		//���菉���ʒu�����ڂ�Y�����(�\���̂̓s����-1�ŃX�^�[�g�ʒu�ɂ���j
		startPos.y = StageManager::SPLIT_ROOM_Y * (static_cast<int>(ret.y) - 1);
		StageManager::DOOR oblongSecond = SplitRoom(pPos, size, startPos);

		doorSpare_ = oblongSecond.y;
	}
		
	return ret;
}
//�}�b�v��Z���������Ƃ�player���ǂ��ɃC���J��ԋp
StageManager::DOOR StageBase::SplitRoom(const Vector2 pMapPos, const Vector2 size, const Vector2 startPos)
{
	StageManager::DOOR ret;

	//���E�̋��
	if (pMapPos.x < size.x) { ret.x = StageManager::DOOR_X::LEFT; }
	else { ret.x = StageManager::DOOR_X::RIGHT; }

	//�㒆���̔��f�i���̑傫��������s��
	//�K�����ɂ͂���̂ŏ����l�͉�����
	ret.y = StageManager::DOOR_Y::BOTTOM;

	if (pMapPos.y < size.y * static_cast<int>(StageManager::DOOR_Y::MIDDLE))
	{
		ret.y = StageManager::DOOR_Y::MIDDLE;
	}
	if (pMapPos.y < size.y * static_cast<int>(StageManager::DOOR_Y::TOP))
	{
		ret.y = StageManager::DOOR_Y::TOP;
	}

	return ret;
}
#pragma endregion


#pragma region ���݂̃J�[�\���ʒu�擾

Vector2 StageBase::GetNowCursorPos(void)
{
	//���݂̃J�[�\���̈ʒu���擾
	Vector2 cursor;

	for (int y = 0; y < size_.y; y++)
	{
		for (int x = 0; x < size_.x; x++)
		{
			CreateKey(y, x);
			if (roomMng_[roomKey_]->GetIsCursor())
			{
				cursor = { x,y };
			}
		}
	}
	return cursor;
}



void StageBase::SetCursorType(CURSOR type)
{
	type_ = type;
}
StageManager::DOOR_Y StageBase::GetDoorSpare(void)
{
	return doorSpare_;
}
#pragma endregion


#pragma region �J�[�\���̈ړ�

void StageBase::SetCursor(Vector2 move, Utility::DIR dir)
{
	//���݂̃J�[�\���ʒu
	Vector2 cursor = GetNowCursorPos();

	//���݂̃J�[�\���̉���
	CreateKey(cursor.y, cursor.x);	
	//���s�O�̈ʒu��ۑ�
	std::string prevKey = roomKey_;
	roomMng_[prevKey]->SetIsCursor(false);

	//�J�[�\���ʒu�̌��ݒn����̈ړ�
	switch (roomMng_[prevKey]->GetRoomType())
	{
		//�󂫃X�y�[�X
	case RoomBase::TYPE::NONE:
		//�a��
	case RoomBase::TYPE::WASITU:
		//���C
	case RoomBase::TYPE::BATH:
		//���u
	case RoomBase::TYPE::STORAGE:
		//��
	case RoomBase::TYPE::WALL:
		//�S�[��
	case RoomBase::TYPE::GOAL:
		cursor.y += move.y;
		cursor.x += move.x;
		break;

		//�c��
		//����
	case RoomBase::TYPE::LIVING:
		//�䏊
	case RoomBase::TYPE::KITCHEN:
		if (dir == Utility::DIR::DOWN) {cursor.y += move.y * 2;}
		else{cursor.y += move.y;}

		cursor.x += move.x;
		break;

		//����
		//����
	case RoomBase::TYPE::OWN:

		//����
	case RoomBase::TYPE::ENTRANCE:
		if (dir == Utility::DIR::RIGHT) { cursor.x += move.x * 2; }
		else { cursor.x += move.x; }

		cursor.y += move.y;
		break;
	}
	

	//�ړ���
	CreateKey(cursor.y, cursor.x);	//�ړ����roomKey_�̐���
	std::string afterMoveKey = roomKey_;		//�ړ����roomKey_�̐����ۑ�

	RoomBase::TYPE afterRoomType = roomMng_[afterMoveKey]->GetRoomType();

#pragma region �ړ��オNONE��������,����OFF
	//if (afterRoomType == RoomBase::TYPE::NONE)
	//{
	//	//�ǉ��ňړ�
	//	cursor.y_ += move.y_;
	//	cursor.x_ += move.x_;
	//	//�ǉ��ړ���̃L�[�֌W
	//	CreateKey(cursor.y_, cursor.x_);	
	//	std::string afterMoveKey = roomKey_;
	//	afterRoomType = roomMng_[afterMoveKey]->GetRoomType();
	//}
#pragma endregion


#pragma region �����`�̓�}�X�ڂ��������̏���
	if (GetRoomShape(afterRoomType)!=RoomBase::ROOM_SHAPE::NOMAL)
	{
		auto r = CreateInstance4Confirmation(afterRoomType);

		//���݂������`�̖{�̂����m�F
		if (CheckInstanceUp(cursor.y, cursor.x, r)||
			CheckInstanceLeft(cursor.y, cursor.x, r))
		{
			//�ۗ��̃J�[�\�����L�����Z��
			roomMng_[afterMoveKey]->SetIsCursor(false);
			//�����`�ɍ��킹���ꏊ�Ɉړ�
			if (afterRoomType == RoomBase::TYPE::KITCHEN || afterRoomType == RoomBase::TYPE::LIVING)
			{
				cursor.y--;
			}
			if (afterRoomType == RoomBase::TYPE::ENTRANCE ||afterRoomType == RoomBase::TYPE::OWN)
			{
				cursor.x--;
			}
			CreateKey(cursor.y, cursor.x);	//roomKey_�̍Đ���
			roomMng_[roomKey_]->SetIsCursor(true);
		}

		r->Release();
		delete r;
	}
#pragma endregion

#pragma region �ړ��͈͊O��������

	if ((cursor.x >= size_.x)
		|| (cursor.y >= size_.y)
		|| IsDontMoveBlock(afterMoveKey))
	{
		//�ړ��O�ɖ߂�
		roomMng_[prevKey]->SetIsCursor(true);
	}
	else
	{
		//�����`�ɂ��ω������邩���Ȃ̂�KEY�͕ۗ��̂��̂��g�p
		roomMng_[roomKey_]->SetIsCursor(true);
	}
#pragma endregion
}
#pragma endregion

#pragma region ��̓���ւ�

//��̓��ꂩ������
void StageBase::SetPiece(Vector2 move, Utility::DIR dir)
{
	std::string nowCursorKey;	//���݂̃J�[�\��
	std::string nowCursorKey2;	//���݂̃J�[�\��(�����`�p)
	std::string afterMoveKey;	//�ړ���̃}�X
	std::string afterMoveKey2;	//�����`�̓�R�}�ڂ̈ړ��������

	bool isSecondPvs = false;	//��R�}�ڂ̈ړ����D�悩

	//���݂̃J�[�\���ʒu
	Vector2 cursor = GetNowCursorPos();
	Vector2 cursor2 = GetNowCursorPos();
	CreateKey(cursor.y, cursor.x);
	nowCursorKey = roomKey_;

	//�����`�p�̓�}�X�ڂ̃J�[�\���ʒu
	if (GetRoomShape(nowCursorKey) != RoomBase::ROOM_SHAPE::NOMAL)	//�����`��������
	{
		//�c�����������𔻒f
		switch (roomMng_[nowCursorKey]->GetRoomType())
		{
		case RoomBase::TYPE::LIVING:
		case RoomBase::TYPE::KITCHEN:
			cursor2.y++;	//�����`�̉��p
			break;
		case RoomBase::TYPE::OWN:
		case RoomBase::TYPE::ENTRANCE:
			cursor2.x++;	//�����`�̉E�p
			break;
		}
		CreateKey(cursor2.y, cursor2.x);
		nowCursorKey2 = roomKey_;
	}
	
	//�ړ��������ꏊ�̒��g�`�F�b�N
	cursor.y += move.y;
	cursor.x += move.x;
	CreateKey(cursor.y, cursor.x);
	afterMoveKey = roomKey_;

	//�����`�̒ǉ�����ψʂ�Ή�(���̎��_�ł�roomKey�̓J�[�\���̈ړ���̃}�X)
	if (GetRoomShape(nowCursorKey) != RoomBase::ROOM_SHAPE::NOMAL)
	{
		//�ړ��������ꏊ�̒��g�`�F�b�N
		cursor2.y += move.y;
		cursor2.x += move.x;
		CreateKey(cursor2.y, cursor2.x);
		afterMoveKey2 = roomKey_;

		switch (roomMng_[nowCursorKey]->GetRoomType())
		{
		case RoomBase::TYPE::LIVING:
		case RoomBase::TYPE::KITCHEN:
			if (dir == Utility::DIR::DOWN) { isSecondPvs = true; }
			break;
		case RoomBase::TYPE::OWN:
		case RoomBase::TYPE::ENTRANCE:
			if (dir == Utility::DIR::RIGHT) { isSecondPvs = true; }
			break;
		}
	}

	///����ւ�
	switch (roomMng_[nowCursorKey]->GetRoomType())
	{
		//��}�X
	case RoomBase::TYPE::NONE:
	case RoomBase::TYPE::WASITU:
	case RoomBase::TYPE::BATH:
	case RoomBase::TYPE::STORAGE:
	case RoomBase::TYPE::WALL:
	case RoomBase::TYPE::GOAL:

		MovePiece(cursor,nowCursorKey,afterMoveKey);
		break;

		//�����`
	case RoomBase::TYPE::LIVING:
	case RoomBase::TYPE::KITCHEN:
	case RoomBase::TYPE::OWN:
	case RoomBase::TYPE::ENTRANCE:

		if (isSecondPvs)
		{
			if (!MovePiece(cursor2, nowCursorKey2, afterMoveKey2)) { return; }	//�ړ����s���Ȃ������̂ŏ����I��
			//�����`�̓�}�X�ڂ��ړ�����Ȃ������ꍇ
			if (!MovePiece(cursor, nowCursorKey, afterMoveKey))
			{
				//�ЂƂO�̎菇���Ȃ��������Ƃ�
				MovePiece(cursor2, afterMoveKey2, nowCursorKey2);
			}
		}
		else
		{
			if (!MovePiece(cursor, nowCursorKey, afterMoveKey)) { return; }		//�ړ����s���Ȃ������̂ŏ����I��
			if (!MovePiece(cursor2, nowCursorKey2, afterMoveKey2))
			{
				//�ЂƂO�̎菇���Ȃ��������Ƃ�
				MovePiece(cursor, afterMoveKey, nowCursorKey);
			}
		}
		break;
	}
}

//����ւ�
bool StageBase::MovePiece(const Vector2 csr,const std::string bfr, const std::string aft)
{
	//�ړ��悪�ǁE�S�[���łȂ���
	if (!IsDontMoveBlock(aft))
	{
		//�ړ��悪�͈͓��ł��邩
		if ((csr.x >= 0) &&
			(csr.x < size_.x) &&
			(csr.y >= 0) &&
			(csr.y < size_.y))
		{
			//�ړ��悪NONE��������
			if (roomMng_[aft]->GetRoomType() == RoomBase::TYPE::NONE)
			{
				//�����̓���ւ�
				RoomBase* change = roomMng_[bfr];
				roomMng_[bfr] = roomMng_[aft];
				roomMng_[aft] = change;
				//�ړ����s��ꂽ�̂�
				return true;
			}
		}
	}
	//�ړ����s���Ȃ������̂�
	return false;
}



#pragma endregion

#pragma region �����`����
//�C���X�^���X�̐����i�������Ɏg�p�j
bool StageBase::CheckInstanceUp(int y, int x, RoomBase* r)
{
	y--;
	CreateKey(y, x);	//�z����̃L�[�𐶐�
	if (roomMng_[roomKey_]->GetRoomType() == r->GetRoomType())
	{
		return true;
	}
	y++;
	CreateKey(y, x);	//���̏ꏊ�̃L�[�𐶐�
	return false;
}
bool StageBase::CheckInstanceDown(int y, int x, RoomBase* r)
{
	y++;
	CreateKey(y, x);	//�z����̃L�[�𐶐�
	if (roomMng_[roomKey_]->GetRoomType() == r->GetRoomType())
	{
		return true;
	}
	y--;
	CreateKey(y, x);	//���̏ꏊ�̃L�[�𐶐�
	return false;
	return false;
}
bool StageBase::CheckInstanceLeft(int y, int x, RoomBase* r)
{
	x--;
	CreateKey(y, x);	//�z�����̃L�[�𐶐�
	if (roomMng_[roomKey_]->GetRoomType() == r->GetRoomType())
	{
		return true;
	}
	x++;
	CreateKey(y, x);	//���̏ꏊ�̃L�[�𐶐�
	return false;
}

bool StageBase::CheckInstanceRight(int y, int x, RoomBase* r)
{
	x++;
	CreateKey(y, x);	//�z�����̃L�[�𐶐�
	if (roomMng_[roomKey_]->GetRoomType() == r->GetRoomType())
	{
		return true;
	}
	x--;
	CreateKey(y, x);	//���̏ꏊ�̃L�[�𐶐�
	return false;
	return false;
}



//�����̌`�̎�ނ�ԋp
RoomBase::ROOM_SHAPE StageBase::GetRoomShape(std::string key)
{
	if (roomMng_[key]->GetRoomType() == RoomBase::TYPE::KITCHEN || roomMng_[key]->GetRoomType() == RoomBase::TYPE::LIVING)
	{
		return RoomBase::ROOM_SHAPE::OBLONG;
	}

	if (roomMng_[key]->GetRoomType() == RoomBase::TYPE::OWN || roomMng_[key]->GetRoomType() == RoomBase::TYPE::ENTRANCE)
	{
		return RoomBase::ROOM_SHAPE::OBLONG_SIDE;
	}

	return RoomBase::ROOM_SHAPE::NOMAL;
}

RoomBase::ROOM_SHAPE StageBase::GetRoomShape(RoomBase::TYPE type)
{
	if (type == RoomBase::TYPE::KITCHEN || type == RoomBase::TYPE::LIVING) 
	{ return RoomBase::ROOM_SHAPE::OBLONG; }

	if (type == RoomBase::TYPE::OWN || type == RoomBase::TYPE::ENTRANCE)
	{ return RoomBase::ROOM_SHAPE::OBLONG_SIDE; }

	return RoomBase::ROOM_SHAPE::NOMAL;
}



bool StageBase::IsDontMoveBlock(std::string key)
{
	if (roomMng_[key]->GetRoomType() == RoomBase::TYPE::GOAL ||
		roomMng_[key]->GetRoomType() == RoomBase::TYPE::WALL)
	{
		//�ړ��s�̃u���b�N�Ȃ̂�
		return true;
	}
	return false;
}

#pragma endregion

#pragma region �����`�̂Q�R�}�ڂ̃C���X�^���X�𐶐�

//�Q�R�}�ڂ̃C���X�^���X��NONE�Œu���^�C�v���C�W��
RoomBase* StageBase::GetSecondRoomInstance(RoomBase* r)
{
	RoomBase* room;
	room = new None(roomImg_[static_cast<int>(RoomBase::TYPE::NONE)]);
	room->Init();
	room->SetRoomType(r->GetRoomType());
	room->SetIsDrawRoom(false);
	room->SetIsClone(true);
	return room;
}
void StageBase::SetIsMoveRoom(bool flag)
{
	isMoveRoom_ = flag;
}
void StageBase::SetIsSecondRoom(bool flag)
{
	isSecondRoom_ = flag;
}
void StageBase::SetIsGoal(bool flag)
{
	isGoal_ = flag;
}
//�������Ď擾�������͕̂K���p���I�������������ƁI
RoomBase* StageBase::CreateInstance4Confirmation(RoomBase::TYPE type)
{
	RoomBase* r = nullptr;

	switch (type)
	{
	case RoomBase::TYPE::LIVING:
		r = new Living(roomImg_[static_cast<int>(RoomBase::TYPE::LIVING)]);
		r->Init();
		break;
	case RoomBase::TYPE::KITCHEN:
		r = new Kitchen(roomImg_[static_cast<int>(RoomBase::TYPE::KITCHEN)]);
		r->Init();
		break;
	case RoomBase::TYPE::OWN:
		r = new Own(roomImg_[static_cast<int>(RoomBase::TYPE::OWN)]);
		r->Init();
		break;
	case RoomBase::TYPE::ENTRANCE:
		r = new Entrance(roomImg_[static_cast<int>(RoomBase::TYPE::ENTRANCE)]);
		r->Init();
		break;
	}
	return r;
}

void StageBase::SetFrameFlash(bool flag)
{
	frameFlash_ = flag;
}
#pragma endregion

#pragma region ���Z�b�g

void StageBase::ResetPazzl(void)
{
	//����ւ������p�̌��݈ʒu�ۑ�
	std::string nowKey;
	

	for (int y = 0; y < size_.y; y++)
	{
		for (int x = 0; x < size_.x; x++)
		{
			CreateKey(y, x);
			nowKey = roomKey_;	
			auto type = roomMng_[nowKey]->GetRoomType();
			if (type != RoomBase::TYPE::WALL)
			{
				auto shape = GetRoomShape(resetRoom_[nowKey]);
				RoomBase* ret = new None(roomImg_[static_cast<int>(RoomBase::TYPE::NONE)]);

				//�����ƕ�����������ꍇ
				if (type != resetRoom_[nowKey])
				{
					//����ւ�
					SwapPazzle(nowKey);
				}
				//�����̏�ԂƈႤ�Ƃ��i�����`�̖{�̂�u���ׂ��ꏊ�ɕ��������Ă��܂����Ƃ��j
				while (resetRoomClone_[nowKey] != roomMng_[nowKey]->IsClone())
				{
					//����ւ�
					SwapPazzle(nowKey);
				}
			}
			//�m��ς݂ɕύX
			roomMng_[nowKey]->SetIsChange(true);
		}
	}
	
	//�m�������
	for (int y = 0; y < size_.y; y++)
	{
		for (int x = 0; x < size_.x; x++)
		{
			CreateKey(y, x);
			nowKey = roomKey_;
			roomMng_[nowKey]->SetIsChange(false);
		}
	}


	debug();
}

void StageBase::SwapPazzle(std::string nowKey)
{
	//���݂̈ʒu���珉���̃^�C�v�̕��������邩���m�F
	for (int i = 0; i < size_.y; i++)
	{
		for (int n = 0; n < size_.x; n++)
		{
			CreateKey(i, n);
			//�܂��m�肵�Ă��Ȃ��ꏊ�ŏ����̕��������������ꍇ
			if (!roomMng_[roomKey_]->IsChange() &&
				roomMng_[roomKey_]->GetRoomType() == resetRoom_[nowKey] &&
				roomKey_ != nowKey)
			{
				RoomBase* r = roomMng_[nowKey];
				roomMng_[nowKey] = roomMng_[roomKey_];
				roomMng_[roomKey_] = r;
				break;
			}
		}
	}
}

#pragma endregion



#pragma region �摜�ǂݍ���

void StageBase::LoadImgs(void)
{
	//�J�[�\��
	frame_[static_cast<int>(CURSOR::NORMAL)]= 
		ResourceManager::GetInstance().Load(ResourceManager::SRC::FRAME_IMG).handleId_;
	frame_[static_cast<int>(CURSOR::OBLONG)] = 
		ResourceManager::GetInstance().Load(ResourceManager::SRC::FRAME_OBLONG_IMG).handleId_;
	frame_[static_cast<int>(CURSOR::OBLONG_2)] = 
		ResourceManager::GetInstance().Load(ResourceManager::SRC::FRAME_OBLONG_2_IMG).handleId_;
}
void StageBase::debug(void)
{
	std::map<std::string, RoomBase::TYPE> resetAfter;
	for (int y = 0; y < size_.y; y++)
	{
		for (int x = 0; x < size_.x; x++)
		{
			CreateKey(y, x);
			resetAfter[roomKey_] = roomMng_[roomKey_]->GetRoomType();
		}
	}

	OutputDebugString("�m�F�p");
}
#pragma endregion

