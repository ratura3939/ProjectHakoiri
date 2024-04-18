#include<DxLib.h>
#include"../Application.h"
#include"Room/RoomBase.h"
#include"Room/Wasitu.h"
#include"Room/None.h"
#include"StageBase.h"

//�R���X�g���N�^
//********************************************************
StageBase::StageBase(void)
{

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
	SetParam();

	//�e�X�g�p

	
	
	for (int i = 0; i < 5; i++)
	{
		RoomBase* r = nullptr;

		switch (static_cast<RoomBase::TYPE>(test_[i]))
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

		rooms_.push_back(r);	//�z����Ɋi�[
	}
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
void StageBase::Draw(void)
{
	Vector2F pos{ static_cast<float>(Application::SCREEN_SIZE_X / 2),
	static_cast<float>(Application::SCREEN_SIZE_Y / 2) };
	int x = 0;
	int y = 0;

	size_t piece = rooms_.size();
	for (int i = 0; i < piece; i++)
	{
		pos.x_ += static_cast<float>(RoomBase::UNIT_PAZZLE_SIZE_X);
		rooms_[i]->SetPzlPos(pos);
		rooms_[i]->DrawPazzle();
		DrawFormatString(x, y, 0xffffff, "�z��%d��`��", i, true);
		y += 100;
	}
}
//���
//********************************************************
bool StageBase::Release(void)
{
	//��
	size_t size = rooms_.size();
	for (int i = 0; i < size; i++)
	{
		rooms_[i]->Release();
		delete rooms_[i];
		rooms_[i] = nullptr;
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