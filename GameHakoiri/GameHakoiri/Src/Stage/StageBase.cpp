#include<DxLib.h>


#include"../Application.h"
#include"../Utility/Utility.h"
#include"Room/RoomBase.h"
#include"Room/Wasitu.h"
#include"Room/None.h"
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
	//
	SetParam();

	LoadPazzle();

	//�e�X�g�p

	size_t pzlY = pzlMap_.size();
	size_t pzlX = pzlX_.size();

	pzlX /= pzlY;

	for (int y = 0; y < pzlY; y++)
	{
		for (int x = 0; x < pzlX; x++)
		{
			RoomBase* r = nullptr;

			switch (static_cast<RoomBase::TYPE>(pzlMap_[y][x+(3*y)]))
			{
			case RoomBase::TYPE::NONE: //�󂫃X�y�[�X
				r = new None();
				OutputDebugString("NONE�̃C���X�^���X����\n");
				break;
				//case RoomBase::TYPE::OWN: //����
				//	r = new Own();
				//	break;
			case RoomBase::TYPE::WASITU: //�a��
				r = new Wasitu();
				OutputDebugString("�a���̃C���X�^���X����\n");
				break;
				//case RoomBase::TYPE::LIVING: //����
				//	r = new Living();
				//	break;
				//case RoomBase::TYPE::BATH: //���C
				//	r = new Bath();
				//	break;
				//case RoomBase::TYPE::STORAGE: //���u
				//	r = new Storage();
				//	break;
				//case RoomBase::TYPE::KITCHEN: //�䏊
				//	r = new Kitchen();
				//	break;
				//case RoomBase::TYPE::ENTRANCE: //����
				//	r = new Entrance();
				//	break;
			}
			if (r->Init() == false)
			{
				OutputDebugString("�����̏��������s\n");
			}

			//rooms_.push_back(r);	//�z����Ɋi�[
			CreateKey(y, x);
			roomMng_[roomKey_] = r;
		}
	}



	CreateKey(0, 0);
	roomMng_[roomKey_]->SetIsCursor(true);

	//�������������I�������̂�
	return true;
}
//�X�V
//********************************************************
void StageBase::Update(void)
{

}
//�`��
//********************************************************
void StageBase::PazzleDraw(void)
{
	Vector2F pos{ static_cast<float>(Application::SCREEN_SIZE_X / 2),
	static_cast<float>(Application::SCREEN_SIZE_Y / 2) };

	size_t pzlY = pzlMap_.size();
	size_t pzlX = pzlX_.size();

	pzlX /= pzlY;

	

	for (int y = 0; y < pzlY; y++)
	{
		for (int x = 0; x < pzlX; x++)
		{
			pos.x_ += static_cast<float>(RoomBase::UNIT_PAZZLE_SIZE_X);
			CreateKey(y, x);
			roomMng_[roomKey_]->SetPzlPos(pos);
			roomMng_[roomKey_]->DrawPazzle();
		}
		pos.x_ = static_cast<float>(Application::SCREEN_SIZE_X / 2);
		pos.y_ += static_cast<float>(RoomBase::UNIT_PAZZLE_SIZE_Y);
	}
}
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

	//�������������I�������̂�
	return true;
}

#pragma region �p�Y���ǂݍ���

void StageBase::LoadPazzle(void)
{
	std::string loadName;
	//loadName = Application::PATH_PAZZLE + testName_;

	//std::ifstream ifs = std::ifstream(loadName);
	std::ifstream ifs = std::ifstream("Data/Csv/Pazzle/test_2.csv");

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

void StageBase::SetCursor(int moveY, int moveX)
{
	//���݂̃J�[�\���ʒu
	Vector2 cursor = GetNowCursorPos();

	//���݂̃J�[�\���̉���
	CreateKey(cursor.y_, cursor.x_);	//roomKey_�̐���
	roomMng_[roomKey_]->SetIsCursor(false);

	//�J�[�\���ʒu�̈ړ�
	cursor.y_ += moveY;
	cursor.x_ += moveX;

	size_t pzlY = pzlMap_.size();
	size_t pzlX = pzlX_.size();
	pzlX /= pzlY;

	//�ړ��オ����𒴂��Ă�����
	if ((cursor.x_ >= pzlX)
		|| (cursor.y_ >= pzlY))
	{
		cursor.y_ -= moveY;
		cursor.x_ -= moveX;
		CreateKey(cursor.y_, cursor.x_);	//roomKey_�̐���
		roomMng_[roomKey_]->SetIsCursor(true);
	}
	else
	{
		CreateKey(cursor.y_, cursor.x_);	//roomKey_�̐���
		roomMng_[roomKey_]->SetIsCursor(true);
	}
}
#pragma endregion

#pragma region ��̓���ւ�

void StageBase::SetPiece(int moveY, int moveX)
{
	size_t pzlY = pzlMap_.size();
	size_t pzlX = pzlX_.size();
	pzlX /= pzlY;

	//���݂̃J�[�\���ʒu
	Vector2 cursor = GetNowCursorPos();
	CreateKey(cursor.y_, cursor.x_);
	std::string prevKey = roomKey_;
	
	//�ړ��������ꏊ�̒��g�`�F�b�N
	cursor.y_ += moveY;
	cursor.x_ += moveX;
	CreateKey(cursor.y_, cursor.x_);

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
#pragma endregion

	