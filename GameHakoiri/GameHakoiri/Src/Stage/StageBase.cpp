#include<DxLib.h>


#include"../Application.h"
#include"../Utility/Utility.h"
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
StageBase::StageBase(void)
{
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
	frame_ = 0;
	frameImg_ = LoadGraph("Data/Img/frame.png");
	frameObImg_ = LoadGraph("Data/Img/frame_oblong.png");
	frameOb2Img_= LoadGraph("Data/Img/frame_oblong_2.png");

	//�e�X�e�[�W�ɂ��ݒ�
	SetParam();
	//�p�Y���z�u�̓ǂݍ���
	LoadPazzle();

	//�������ɕK�v�ȕϐ�
	size_t pzlY = pzlMap_.size();
	size_t pzlX = pzlX_.size();
	pzlX /= pzlY;

	Vector2F pos{ static_cast<float>(Application::SCREEN_SIZE_X / 4),
		static_cast<float>(Application::SCREEN_SIZE_Y / 4) };


	for (int y = 0; y < pzlY; y++)
	{
		for (int x = 0; x < pzlX; x++)
		{
			RoomBase* r = nullptr;

			switch (static_cast<RoomBase::TYPE>(pzlMap_[y][x+(pzlX*y)]))
			{
			//�󂫃X�y�[�X
			case RoomBase::TYPE::NONE: 
				r = new None;
				r->Init();
				break;
			//����
			case RoomBase::TYPE::OWN: 
				r = new Own();
				r->Init();
				//���������������̂������`�̂Q�R�}�ڂ�������
				if (CheckInstanceLeft(y, x, r)){ r = GetSecondRoomInstance(r); }
				break;
			//�a��
			case RoomBase::TYPE::WASITU:
				r = new Wasitu;;
				r->Init();
				break;
			//����
			case RoomBase::TYPE::LIVING:
				r = new Living;
				r->Init();
				//���������������̂������`�̂Q�R�}�ڂ�������
				if (CheckInstanceUp(y, x, r)) { r = GetSecondRoomInstance(r); }
				break;
			//���C
			case RoomBase::TYPE::BATH: 
				r = new Bath;
				r->Init();
				break;
			//���u
			case RoomBase::TYPE::STORAGE:
				r = new Storage;
				r->Init();
				break;
			//�䏊
			case RoomBase::TYPE::KITCHEN: 
				r = new Kitchen;
				r->Init();
				//���������������̂������`�̂Q�R�}�ڂ�������
				if (CheckInstanceUp(y, x, r)) { r = GetSecondRoomInstance(r); }
				break;
			//����
			case RoomBase::TYPE::ENTRANCE: 
				r = new Entrance;
				r->Init();
				//���������������̂������`�̂Q�R�}�ڂ�������
				if (CheckInstanceLeft(y, x, r)) { r = GetSecondRoomInstance(r); }
				break;
			//��
			case RoomBase::TYPE::WALL:	
				r = new Wall;
				r->Init();
				break;
			//�S�[��
			case RoomBase::TYPE::GOAL:
				r = new Goal;
				r->Init();
				break;
			}

			CreateKey(y, x);
			roomMng_[roomKey_] = r;//�z����Ɋi�[
			pzlPos_[roomKey_] = pos;

			//���W�̍X�V
			pos.x_ += static_cast<float>(RoomBase::UNIT_PAZZLE_SIZE_X);
		}
		pos.x_ = static_cast<float>(Application::SCREEN_SIZE_X / 4);
		pos.y_ += static_cast<float>(RoomBase::UNIT_PAZZLE_SIZE_Y);
	}



	CreateKey(1, 1);
	roomMng_[roomKey_]->SetIsCursor(true);

	//�������������I�������̂�
	return true;
}
//�X�V
//********************************************************
void StageBase::Update(void)
{

}
#pragma region �`��

#pragma region �p�Y���V�[��

	void StageBase::PazzleDraw(void)
	{		
		size_t pzlY = pzlMap_.size();
		size_t pzlX = pzlX_.size();
	
		pzlX /= pzlY;


		//��̕`��
		for (int y = 0; y < pzlY; y++)
		{
			for (int x = 0; x < pzlX; x++)
			{
				CreateKey(y, x);
				roomMng_[roomKey_]->SetPzlPos(pzlPos_[roomKey_]);
				roomMng_[roomKey_]->DrawPazzle();
			}
			
		}
		//�g�̕`��
		DrawCursor();
	}
	#pragma endregion

#pragma region �J�[�\��

	void StageBase::DrawCursor(void)
	{
		Vector2 key = GetNowCursorPos();

		DrawFormatString(0, 20, 0xffffff, "CURSOR={%d.%d}", key.x_, key.y_);

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
			frame_ = frameImg_;
			break;
			//�c��
			//����
		case RoomBase::TYPE::LIVING:
			//�䏊
		case RoomBase::TYPE::KITCHEN:
			frame_ = frameObImg_;
			break;

			//����
			//����
		case RoomBase::TYPE::OWN:
			//����
		case RoomBase::TYPE::ENTRANCE:
			frame_ = frameOb2Img_;
			break;
		}
		if (roomMng_[roomKey_]->GetIsCursor())
		{
			//�g�̕`��
			DrawGraph(pzlPos_[roomKey_].x_, pzlPos_[roomKey_].y_,
				frame_, true);
		}
	}
#pragma endregion


#pragma endregion

//�`��
//********************************************************

//���
//********************************************************
bool StageBase::Release(void)
{
	//��
	size_t pzlY = pzlMap_.size();
	size_t pzlX = pzlX_.size();

	pzlX /= pzlY;

	for (int y = 0; y < pzlY; y++)
	{
		for (int x = 0; x < pzlX; x++)
		{
			CreateKey(y, x);
			roomMng_[roomKey_]->Release();
			delete roomMng_[roomKey_];
			roomMng_[roomKey_] = nullptr;
		}
	}

	DeleteGraph(frameImg_);
	DeleteGraph(frameObImg_);
	DeleteGraph(frameOb2Img_);

	//�������������I�������̂�
	return true;
}

#pragma region �p�Y���ǂݍ���

void StageBase::LoadPazzle(void)
{
	std::string loadName;
	//loadName = Application::PATH_PAZZLE + testName_;

	//std::ifstream ifs = std::ifstream(loadName);
	std::ifstream ifs = std::ifstream("Data/Csv/Pazzle/map_test.csv");

	if (!ifs)
	{
		OutputDebugString("�n��X�e�[�W��ifstream�̏������s");
		return;
	}

	int chipNo = 0;
	//��̐擪����ۑ�����
	int x = 0;

	//�s�i�[�p�̈�
	std::string line;
	while (getline(ifs, line))	//�s�������
	{
		//Split�֐��߂�l�󂯎��p
		std::vector<std::string> strSplit;

		strSplit = Utility::Split(line, ',');	//�֐��̌Ăяo��

		//�ꕶ���̏��
		std::string chipData;
		//���������}�b�v�f�[�^���i�[����
		for (int x = 0; x < strSplit.size(); x++)
		{
			chipNo = stoi(strSplit[x]);
			pzlX_.push_back(chipNo);	//�z����Ɋi�[
		}
		pzlMap_.push_back(pzlX_);	//�z����Ɋi�[
	}

}
#pragma endregion

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

	size_t pzlY = pzlMap_.size();
	size_t pzlX = pzlX_.size();
	pzlX /= pzlY;
	for (int y = 0; y < pzlY; y++)
	{
		for (int x = 0; x < pzlX; x++)
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
#pragma endregion


#pragma region �J�[�\���̈ړ�

void StageBase::SetCursor(Vector2 move, Utility::DIR dir)
{
	//���݂̃J�[�\���ʒu
	Vector2 cursor = GetNowCursorPos();

	//���݂̃J�[�\���̉���
	CreateKey(cursor.y_, cursor.x_);	//���݈ʒu��roomKey_�̐���
	roomMng_[roomKey_]->SetIsCursor(false);

	//���s�O�̈ʒu��ۑ�
	std::string prevKey = roomKey_;;

	//�J�[�\���ʒu�̌��ݒn����̈ړ�
	switch (roomMng_[roomKey_]->GetRoomType())
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
	std::string holdKey = roomKey_;		//�����`�Ȃǂ̏ꍇ������̂ŕۗ��Ƃ���

	RoomBase::TYPE roomType = roomMng_[roomKey_]->GetRoomType();

	size_t pzlY = pzlMap_.size();
	size_t pzlX = pzlX_.size();
	pzlX /= pzlY;


#pragma region �����`�̓�}�X�ڂ�������
	//�c��
	if (roomType == RoomBase::TYPE::KITCHEN ||
		roomType == RoomBase::TYPE::LIVING)
	{
		RoomBase* r = nullptr;
		switch (roomType)
		{
		case RoomBase::TYPE::LIVING:
			r = new Living;
			r->Init();
			break;
		case RoomBase::TYPE::KITCHEN:
			r = new Kitchen;
			r->Init();
			break;
		}
		//���݂������`�̖{�̂����m�F
		if (CheckInstanceUp(cursor.y_, cursor.x_, r))
		{
			//�ۗ��̃J�[�\�����L�����Z��
			roomMng_[holdKey]->SetIsCursor(false);
			//�����`�ɍ��킹���ꏊ�Ɉړ�
			cursor.y_--;
			CreateKey(cursor.y_, cursor.x_);	//roomKey_�̍Đ���
			roomMng_[roomKey_]->SetIsCursor(true);
		}

		delete r;
	}
	//����
	if (roomType == RoomBase::TYPE::ENTRANCE ||
		roomType == RoomBase::TYPE::OWN)
	{
		RoomBase* r = nullptr;
		switch (roomType)
		{
		case RoomBase::TYPE::OWN:
			r = new Own;
			r->Init();
			break;
		case RoomBase::TYPE::ENTRANCE:
			r = new Entrance;
			r->Init();
			break;
		}
		//���݂������`�̖{�̂����m�F
		if (CheckInstanceLeft(cursor.y_, cursor.x_, r))
		{
			//�ۗ��̃J�[�\�����L�����Z��
			roomMng_[holdKey]->SetIsCursor(false);
			//�����`�ɍ��킹���ꏊ�Ɉړ�
			cursor.x_--;
			CreateKey(cursor.y_, cursor.x_);	//roomKey_�̍Đ���
			roomMng_[roomKey_]->SetIsCursor(true);
		}

		delete r;
	}
#pragma endregion

#pragma region �ړ��͈͊O��������

	if ((cursor.x_ >= pzlX)
		|| (cursor.y_ >= pzlY)
		|| (roomType == RoomBase::TYPE::WALL)
		|| (roomType == RoomBase::TYPE::GOAL))
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

void StageBase::SetPiece(Vector2 move, Utility::DIR dir)
{
	size_t pzlY = pzlMap_.size();
	size_t pzlX = pzlX_.size();
	pzlX /= pzlY;

	//���݂̃J�[�\���ʒu
	Vector2 cursor = GetNowCursorPos();
	CreateKey(cursor.y_, cursor.x_);
	std::string prevKey = roomKey_;
	
	//�ړ��������ꏊ�̒��g�`�F�b�N
	cursor.y_ += move.y_;
	cursor.x_ += move.x_;
	CreateKey(cursor.y_, cursor.x_);

	//�ړ��悪�ǁE�S�[���łȂ���
	if (roomMng_[roomKey_]->GetRoomType() != RoomBase::TYPE::WALL ||
		roomMng_[roomKey_]->GetRoomType() != RoomBase::TYPE::GOAL)
	{
		//�ړ��悪�͈͓��ł��邩
		if ((cursor.x_ >= 0) &&
			(cursor.x_ < pzlX) &&
			(cursor.y_ >= 0) &&
			(cursor.y_ < pzlY))
		{
			//�ړ��悪NONE��������
			if (roomMng_[roomKey_]->GetRoomType() == RoomBase::TYPE::NONE)
			{
				//�����̓���ւ�
				RoomBase* change = roomMng_[prevKey];
				roomMng_[prevKey] = roomMng_[roomKey_];
				roomMng_[roomKey_] = change;
			}
		}
	}
}
#pragma endregion

#pragma region �����`��̂Q�}�X��

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

#pragma endregion

#pragma region �����`�̂Q�R�}�ڂ̃C���X�^���X�𐶐�

//�Q�R�}�ڂ̃C���X�^���X��NONE�Œu���^�C�v���C�W��
RoomBase* StageBase::GetSecondRoomInstance(RoomBase* r)
{
	RoomBase* room;
	room = new None;
	room->Init();
	room->SetRoomType(r->GetRoomType());
	room->SetColor(r->GetColor());
	return room;
}
#pragma endregion

