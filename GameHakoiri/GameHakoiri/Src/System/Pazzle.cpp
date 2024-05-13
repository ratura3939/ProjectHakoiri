#include<DxLib.h>

#include"../Utility/Utility.h"
#include"../Manager/InputManager.h"
#include"../Manager/StageManager.h"
#include"../Scene/GameScene.h"
#include "Pazzle.h"	

//�R���X�g���N�^
//********************************************************
Pazzle::Pazzle(void)
{
	isFinish_ = false;
	isSelect_ = false;
	isNeutral_ = true;
	neutralStick_ = { 0,0 };
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

#pragma region �L�[�{�[�h

// �L�[�{�[�h�̑���
//********************************************************
void Pazzle::KeyboardContoroller(void)
{
	InputManager& ins = InputManager::GetInstance();
	StageManager& stage = StageManager::GetInstance();

	if (ins.IsTrgDown(KEY_INPUT_RETURN))
	{
		ChangeIsFinish(true);
		return;
	}

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
#pragma endregion


#pragma region �p�b�h����

// �Q�[���p�b�h�̑���
//********************************************************
void Pazzle::GamePadController(void)
{
	
	InputManager& ins = InputManager::GetInstance();
	StageManager& stage = StageManager::GetInstance();

	//�p�Y���������̃��[�h�Ɉڍs
	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::RIGHT))
	{
		ChangeIsFinish(true);
		return;
	}




	// ���X�e�B�b�N�̉���
	auto leftStickX = ins.GetInstance().GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLX;
	// ���X�e�B�b�N�̏c��
	auto leftStickY = ins.GetInstance().GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLY;
	//�X�e�B�b�N�̓��������킹�ĕۑ�
	Vector2 inputStick = { leftStickX,leftStickY };

	//�j���[�g�����ɖ߂�������
	if (!isNeutral_)
	{
		//���݂��j���[�g�������𔻒f
		if (IsStickNeutral(inputStick))
		{
			ChangeIsNeutral(true);
		}
	}
	

	//�X�e�B�b�N���j���[�g������Ԃ̂Ƃ�
	if (isNeutral_)
	{
		//��̑I�𒆂ł͂Ȃ��Ƃ�
		if (!isSelect_)
		{
			//�Ֆʃ��Z�b�g
			if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::TOP))
			{
				stage.PazzleReset();
			}

			//�X�e�B�b�N���ړ����Ă���Ƃ�
			if (abs(leftStickY) > 0 ||
				abs(leftStickX) > 0)
			{
				stage.MoveCursor(MoveStick(inputStick));
			}
			
			//��̑I��
			if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
			{
				ChangeIsSelect(true);
			}
		}
		else
		{
			//��̈ړ���t
			//�X�e�B�b�N���ړ����Ă���Ƃ�
			if (abs(leftStickY) > 0 ||
				abs(leftStickX) > 0)
			{
				stage.MovePiece(MoveStick(inputStick));
			}

			if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
			{
				ChangeIsSelect(false);
			}
		}
	}
}
#pragma endregion


#pragma region �t���O�̃Q�b�^�[

bool Pazzle::IsSelect(void)
{
	return isSelect_;
}

bool Pazzle::IsNeutral(void)
{
	return isNeutral_;
}

bool Pazzle::IsFinish(void)
{
	return isFinish_;
}
#pragma endregion

#pragma region �t���O�̃Z�b�^�[

void Pazzle::ChangeIsSelect(bool flag)
{
	isSelect_ = flag;
}

void Pazzle::ChangeIsNeutral(bool flag)
{
	isNeutral_ = flag;
}

void Pazzle::ChangeIsFinish(bool flag)
{
	isFinish_ = flag;
}
#pragma endregion


#pragma region L�X�e�B�b�N�֘A

//�j���[�g������Ԃ̔���
bool Pazzle::IsStickNeutral(Vector2 stick)
{
	if (neutralStick_.x_ == stick.x_ &&
		neutralStick_.y_ == stick.y_)
	{
		return true;
	}
	return false;
}

//�ړ���������
Utility::DIR Pazzle::MoveStick(Vector2 stick)
{

	//�c���̕����ړ��ʂ�������
	if (abs(stick.y_) > abs(stick.x_))
	{
		if (stick.y_ < 0)
		{
			ChangeIsNeutral(false);
			return Utility::DIR::UP;
		}
		else
		{
			ChangeIsNeutral(false);
			return Utility::DIR::DOWN;
		}
	}
	else
	{
		if (stick.x_ > 0)
		{
			ChangeIsNeutral(false);
			return Utility::DIR::RIGHT;
		}
		else
		{
			ChangeIsNeutral(false);
			return Utility::DIR::LEFT;
		}
	}
}

#pragma endregion

