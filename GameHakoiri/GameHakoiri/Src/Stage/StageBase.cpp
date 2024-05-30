#include<DxLib.h>


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
	size_.x_ = pzlSizeX;
	size_.y_ = pzlSizeY;

	mapCsv_ = map;
	objCsv_ = obj;
	roomImg_ = roomImg;
	mapchip_ = mapchip;

	roomKey_ = "00";
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
	SetFrameFlash(false);

	//�e�X�e�[�W�ɂ��ݒ�
	SetParam();
	//�p�Y���z�u�̓ǂݍ���
	//LoadPazzle();
	//�摜�ǂݍ���
	LoadImgs();

	Vector2F pos{ static_cast<float>(Application::SCREEN_SIZE_X / 4),
		static_cast<float>(Application::SCREEN_SIZE_Y / 4) };


	for (int y = 0; y < size_.y_; y++)
	{
		for (int x = 0; x < size_.x_; x++)
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
				break;
			}

			CreateKey(y, x);
			roomMng_[roomKey_] = r;//�z����Ɋi�[
			resetRoom_[roomKey_] = r->GetRoomType();
			pzlPos_[roomKey_] = pos;

			//���W�̍X�V
			pos.x_ += static_cast<float>(RoomBase::UNIT_PAZZLE_SIZE_X);
		}
		pos.x_ = static_cast<float>(Application::SCREEN_SIZE_X / 4);
		pos.y_ += static_cast<float>(RoomBase::UNIT_PAZZLE_SIZE_Y);
	}

	//�����̃J�[�\���ݒ�
	for (int y = 0; y < size_.y_; y++)
	{
		for (int x = 0; x < size_.x_; x++)
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
	//�����ʒu�̏ꏊ���������[���L�[�𐶐�
	for (int y = 0; y < size_.y_; y++)
	{
		for (int x = 0; x < size_.x_; x++)
		{
			CreateKey(y, x);
			if (roomMng_[roomKey_]->GetRoomType() == RoomBase::TYPE::OWN)
			{
				//�������������I�������̂�
				return true;
			}
		}
	}

	//��������
	return false;
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
		for (int y = 0; y < size_.y_; y++)
		{
			for (int x = 0; x < size_.x_; x++)
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

		CreateKey(key.y_, key.x_);
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
			DrawGraph(pzlPos_[roomKey_].x_, pzlPos_[roomKey_].y_,
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

	for (int y = 0; y < size_.y_; y++)
	{
		for (int x = 0; x < size_.x_; x++)
		{
			CreateKey(y, x);
			roomMng_[roomKey_]->Release();
			delete roomMng_[roomKey_];
			roomMng_[roomKey_] = nullptr;
		}
	}

	for (int i = 0; i < static_cast<int>(CURSOR::MAX); i++)
	{
		DeleteGraph(frame_[i]);
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

#pragma region ���݂̃J�[�\���ʒu�擾

Vector2 StageBase::GetNowCursorPos(void)
{
	//���݂̃J�[�\���̈ʒu���擾
	Vector2 cursor;

	for (int y = 0; y < size_.y_; y++)
	{
		for (int x = 0; x < size_.x_; x++)
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
Vector2F StageBase::GetNowDrawMapSize(void)
{
	return Vector2F();
}
#pragma endregion


#pragma region �J�[�\���̈ړ�

void StageBase::SetCursor(Vector2 move, Utility::DIR dir)
{
	//���݂̃J�[�\���ʒu
	Vector2 cursor = GetNowCursorPos();

	//���݂̃J�[�\���̉���
	CreateKey(cursor.y_, cursor.x_);	
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
		cursor.y_ += move.y_;
		cursor.x_ += move.x_;
		break;

		//�c��
		//����
	case RoomBase::TYPE::LIVING:
		//�䏊
	case RoomBase::TYPE::KITCHEN:
		if (dir == Utility::DIR::DOWN) {cursor.y_ += move.y_ * 2;}
		else{cursor.y_ += move.y_;}

		cursor.x_ += move.x_;
		break;

		//����
		//����
	case RoomBase::TYPE::OWN:

		//����
	case RoomBase::TYPE::ENTRANCE:
		if (dir == Utility::DIR::RIGHT) { cursor.x_ += move.x_ * 2; }
		else { cursor.x_ += move.x_; }

		cursor.y_ += move.y_;
		break;
	}
	

	//�ړ���
	CreateKey(cursor.y_, cursor.x_);	//�ړ����roomKey_�̐���
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
	if (IsOblong(afterRoomType))
	{
		RoomBase* r = nullptr;
		switch (afterRoomType)
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
		//���݂������`�̖{�̂����m�F
		if (CheckInstanceUp(cursor.y_, cursor.x_, r)||
			CheckInstanceLeft(cursor.y_, cursor.x_, r))
		{
			//�ۗ��̃J�[�\�����L�����Z��
			roomMng_[afterMoveKey]->SetIsCursor(false);
			//�����`�ɍ��킹���ꏊ�Ɉړ�
			if (afterRoomType == RoomBase::TYPE::KITCHEN || afterRoomType == RoomBase::TYPE::LIVING)//{ cursor.y_--; }
			{
				cursor.y_--;
			}
			if (afterRoomType == RoomBase::TYPE::ENTRANCE ||afterRoomType == RoomBase::TYPE::OWN)//{ cursor.x_--; }
			{
				cursor.x_--;
			}
			CreateKey(cursor.y_, cursor.x_);	//roomKey_�̍Đ���
			roomMng_[roomKey_]->SetIsCursor(true);
		}

		delete r;
	}
#pragma endregion

#pragma region �ړ��͈͊O��������

	if ((cursor.x_ >= size_.x_)
		|| (cursor.y_ >= size_.y_)
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
	CreateKey(cursor.y_, cursor.x_);
	nowCursorKey = roomKey_;

	//�����`�p�̓�}�X�ڂ̃J�[�\���ʒu
	if (IsOblong(nowCursorKey))	//�����`��������
	{
		//�c�����������𔻒f
		switch (roomMng_[nowCursorKey]->GetRoomType())
		{
		case RoomBase::TYPE::LIVING:
		case RoomBase::TYPE::KITCHEN:
			cursor2.y_++;	//�����`�̉��p
			break;
		case RoomBase::TYPE::OWN:
		case RoomBase::TYPE::ENTRANCE:
			cursor2.x_++;	//�����`�̉E�p
			break;
		}
		CreateKey(cursor2.y_, cursor2.x_);
		nowCursorKey2 = roomKey_;
	}
	
	//�ړ��������ꏊ�̒��g�`�F�b�N
	cursor.y_ += move.y_;
	cursor.x_ += move.x_;
	CreateKey(cursor.y_, cursor.x_);
	afterMoveKey = roomKey_;

	//�����`�̒ǉ�����ψʂ�Ή�(���̎��_�ł�roomKey�̓J�[�\���̈ړ���̃}�X)
	if (IsOblong(nowCursorKey))
	{
		//�ړ��������ꏊ�̒��g�`�F�b�N
		cursor2.y_ += move.y_;
		cursor2.x_ += move.x_;
		CreateKey(cursor2.y_, cursor2.x_);
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
		if ((csr.x_ >= 0) &&
			(csr.x_ < size_.x_) &&
			(csr.y_ >= 0) &&
			(csr.y_ < size_.y_))
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

//�����`�ł��邩
bool StageBase::IsOblong(std::string key)
{
	if (roomMng_[key]->GetRoomType() == RoomBase::TYPE::KITCHEN ||
		roomMng_[key]->GetRoomType() == RoomBase::TYPE::LIVING ||
		roomMng_[key]->GetRoomType() == RoomBase::TYPE::OWN ||
		roomMng_[key]->GetRoomType() == RoomBase::TYPE::ENTRANCE)
	{
		return true;
	}
	return false;
}
bool StageBase::IsOblong(RoomBase::TYPE type)
{
	if (type == RoomBase::TYPE::KITCHEN ||
		type == RoomBase::TYPE::LIVING ||
		type == RoomBase::TYPE::OWN ||
		type == RoomBase::TYPE::ENTRANCE)
	{
		return true;
	}
	return false;
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
	return room;
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

	for (int y = 0; y < size_.y_; y++)
	{
		for (int x = 0; x < size_.x_; x++)
		{
			CreateKey(y, x);
			nowKey = roomKey_;	

			//�����ƕ�����������ꍇ
			if (roomMng_[nowKey]->GetRoomType() != resetRoom_[nowKey])
			{
				//���݂̈ʒu���珉���̃^�C�v�̕��������邩���m�F
				for (int i = 0; i < size_.y_; i++)
				{
					for (int n = 0; n < size_.x_; n++)
					{
						CreateKey(i, n);
						//�܂��m�肵�Ă��Ȃ��ꏊ�ŏ����̕��������������ꍇ
						if (!roomMng_[roomKey_]->IsChange() &&
							roomMng_[roomKey_]->GetRoomType() == resetRoom_[nowKey])
						{
							RoomBase* r = roomMng_[nowKey];
							roomMng_[nowKey] = roomMng_[roomKey_];
							roomMng_[roomKey_] = r;
						}
					}
				}
			}
			//�m��ς݂ɕύX
			roomMng_[nowKey]->SetIsChange(true);
		}
	}
	
	//�m�������
	for (int y = 0; y < size_.y_; y++)
	{
		for (int x = 0; x < size_.x_; x++)
		{
			CreateKey(y, x);
			nowKey = roomKey_;
			roomMng_[nowKey]->SetIsChange(false);
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
#pragma endregion

