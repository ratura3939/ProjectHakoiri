#include<DxLib.h>

#include"../Utility/Utility.h"
#include"../Manager/InputManager.h"
#include"../Manager/StageManager.h"
#include "Pazzle.h"

//�R���X�g���N�^
//********************************************************
Pazzle::Pazzle(void)
{
	isSelect_ = false;
}
//�f�X�g���N�^
//********************************************************
Pazzle::~Pazzle(void)
{

}
//�X�V
//********************************************************
void Pazzle::Update(void)
{
	//StageMng�o�R��roomMng�̕ύX���s��
	//���͌n
	KeyboardContoroller();
	GamePadController();
}

// �L�[�{�[�h�̑���
//********************************************************
void Pazzle::KeyboardContoroller(void)
{
	InputManager& ins = InputManager::GetInstance();
	if (!isSelect_)
	{
		//�J�[�\���̈ړ���t
		if (ins.IsTrgDown(KEY_INPUT_UP))
		{
			StageManager::GetInstance().MoveCursor(Utility::DIR::UP);
		}
		if (ins.IsTrgDown(KEY_INPUT_DOWN))
		{
			StageManager::GetInstance().MoveCursor(Utility::DIR::DOWN);
		}
		if (ins.IsTrgDown(KEY_INPUT_LEFT))
		{
			StageManager::GetInstance().MoveCursor(Utility::DIR::LEFT);
		}
		if (ins.IsTrgDown(KEY_INPUT_RIGHT))
		{
			StageManager::GetInstance().MoveCursor(Utility::DIR::RIGHT);
		}
		if (ins.IsTrgDown(KEY_INPUT_SPACE))
		{
			ChangeIsSelect(true);
		}
	}
	else
	{
		//��̈ړ���t
		if (ins.IsTrgDown(KEY_INPUT_UP))
		{

		}
		if (ins.IsTrgDown(KEY_INPUT_DOWN))
		{

		}
		if (ins.IsTrgDown(KEY_INPUT_LEFT))
		{

		}
		if (ins.IsTrgDown(KEY_INPUT_RIGHT))
		{

		}
		if (ins.IsTrgDown(KEY_INPUT_Q))
		{
			ChangeIsSelect(false);
		}
	}
}

// �Q�[���p�b�h�̑���
//********************************************************
void Pazzle::GamePadController(void)
{
	InputManager& ins = InputManager::GetInstance();
}

//IsSelect�̕ύX
//********************************************************
void Pazzle::ChangeIsSelect(bool flag)
{
	isSelect_ = flag;
}
