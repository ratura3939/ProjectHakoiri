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
	//
	StageManager& stage = StageManager::GetInstance();
	stage.SetFlash(isSelect_);
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
	StageManager& stage = StageManager::GetInstance();
	
	if (!isSelect_)
	{
		//�Ֆʃ��Z�b�g
		if (ins.IsTrgDown(KEY_INPUT_R))
		{
			stage.PazzleReset();
		}
		//�J�[�\���̈ړ���t
		if (ins.IsTrgDown(KEY_INPUT_UP))
		{
			stage.MoveCursor(Utility::DIR::UP);
		}
		if (ins.IsTrgDown(KEY_INPUT_DOWN))
		{
			stage.MoveCursor(Utility::DIR::DOWN);
		}
		if (ins.IsTrgDown(KEY_INPUT_LEFT))
		{
			stage.MoveCursor(Utility::DIR::LEFT);
		}
		if (ins.IsTrgDown(KEY_INPUT_RIGHT))
		{
			stage.MoveCursor(Utility::DIR::RIGHT);
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
			stage.MovePiece(Utility::DIR::UP);
		}
		if (ins.IsTrgDown(KEY_INPUT_DOWN))
		{
			stage.MovePiece(Utility::DIR::DOWN);
		}
		if (ins.IsTrgDown(KEY_INPUT_LEFT))
		{
			stage.MovePiece(Utility::DIR::LEFT);
		}
		if (ins.IsTrgDown(KEY_INPUT_RIGHT))
		{
			stage.MovePiece(Utility::DIR::RIGHT);
		}
		if (ins.IsTrgDown(KEY_INPUT_SPACE))
		{
			ChangeIsSelect(false);
		}
	}
}

#pragma region �p�b�h����

// �Q�[���p�b�h�̑���
//********************************************************
void Pazzle::GamePadController(void)
{
	//InputManager& ins = InputManager::GetInstance();
	//StageManager& stage = StageManager::GetInstance();

	//if (!isSelect_)
	//{
	//	//�Ֆʃ��Z�b�g
	//	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1,InputManager::JOYPAD_BTN::TOP))
	//	{
	//		stage.PazzleReset();
	//	}
	//	//�J�[�\���̈ړ���t
	//	if (ins.IsPadStickTrgDown(InputManager::JOYPAD_NO::PAD1,InputManager::JOYPAD_BTN::TOP))
	//	{
	//		stage.MoveCursor(Utility::DIR::UP);
	//	}
	//	if (ins.IsPadStickTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	//	{
	//		stage.MoveCursor(Utility::DIR::DOWN);
	//	}
	//	if (ins.IsPadStickTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::LEFT))
	//	{
	//		stage.MoveCursor(Utility::DIR::LEFT);
	//	}
	//	if (ins.IsPadStickTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
	//	{
	//		stage.MoveCursor(Utility::DIR::RIGHT);
	//	}
	//	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	//	{
	//		ChangeIsSelect(true);
	//	}
	//}
	//else
	//{
	//	//��̈ړ���t
	//	if (ins.IsPadStickTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::TOP))
	//	{
	//		stage.MovePiece(Utility::DIR::UP);
	//	}
	//	if (ins.IsPadStickTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	//	{
	//		stage.MovePiece(Utility::DIR::DOWN);
	//	}
	//	if (ins.IsPadStickTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::LEFT))
	//	{
	//		stage.MovePiece(Utility::DIR::LEFT);
	//	}
	//	if (ins.IsPadStickTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
	//	{
	//		stage.MovePiece(Utility::DIR::RIGHT);
	//	}

	//	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
	//	{
	//		ChangeIsSelect(false);
	//	}
	//}
}
#pragma endregion

bool Pazzle::IsSelect(void)
{
	return isSelect_;
}

//IsSelect�̕ύX
//********************************************************
void Pazzle::ChangeIsSelect(bool flag)
{
	isSelect_ = flag;
}
