#include<DxLib.h>
#include"../Manager/ResourceManager.h"
#include"../Manager/InputManager.h"
#include"../System/Stealth.h"
#include"../Application.h"
#include "Player.h"


#include"../Manager/SceneManager.h"
#include"../Manager/Camera.h"

Player::Player(void)
{
}

Player::~Player(void)
{
}

void Player::SetParam(void)
{
	img_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::PLAYER_IMGS).handleIds_;
	dir_ = CharacterBase::DIR::BOTTOM;
	pos_ = { 990.0f,270.0f };
	move_ = 2.0f;

	hpPos_ = { Application::SCREEN_SIZE_X - HP_SIZE / 2,HP_SIZE / 2 };
	hp_ = HP;
	hpBaseImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::HP_BASE_IMG).handleId_;
	hpCircleImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::HP_CIRCLE_IMG).handleId_;
	hpText_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::HP_TEXT_IMG).handleId_;
}

void Player::Move(void)
{
	//�ړ��O�̕�����ۑ�
	auto prevDir = GetDir();

	auto cnt = SceneManager::GetInstance().GetController();

	switch (cnt)
	{
	case SceneManager::CONTROLLER::KEYBOARD:
		KeyboardContoroller();
		break;
	case SceneManager::CONTROLLER::PAD:
		GamePadController();
		break;
	}

	//�S�Ă̈ړ��������I����Ă���A�j���[�V������ύX���邩���߂�
	if (GetDir() != prevDir)
	{
		ResetAnim(GetDir());
	}
}

void Player::Draw(void)
{
	CharacterBase::Draw();


	//�g
	DrawRotaGraph(hpPos_.x,
		hpPos_.y,
		1.0f,
		0.0 * Utility::DEG2RAD,
		hpBaseImg_,
		true,
		false);
	//HP���̂���
	DrawCircleGauge(hpPos_.x,
		hpPos_.y,
		hp_,
		hpCircleImg_,
		0.0);
	//HP�e�L�X�g
	DrawRotaGraph(hpPos_.x,
		hpPos_.y,
		1.0f,
		0.0 * Utility::DEG2RAD,
		hpText_,
		true,
		false);
}

bool Player::IsDrawMap(void) const
{
	return isDrawMap_;
}

float Player::GetHp(void) const
{
	return hp_;
}

void Player::Damage(void)
{
	hp_ -= Stealth::DAMAGE;
}

void Player::KeyboardContoroller(void)
{
	InputManager& ins = InputManager::GetInstance();

	bool IsMoveY = false;

	//�ړ�
	if (ins.IsNew(KEY_INPUT_UP)) 
	{
		pos_.y -= move_; 
		SetDir(CharacterBase::DIR::TOP);
		IsMoveY = true;
	}
	if (ins.IsNew(KEY_INPUT_DOWN))
	{
		pos_.y += move_; 
		SetDir(CharacterBase::DIR::BOTTOM);
		IsMoveY = true;
	}
	if (ins.IsNew(KEY_INPUT_LEFT)) 
	{
		pos_.x -= move_; 
		SetDir(CharacterBase::DIR::LEFT);
		if (IsMoveY)
		{
			if (pos_.y < prevPos_.y)SetDir(CharacterBase::DIR::TOP_LEFT);
			else SetDir(CharacterBase::DIR::BOTTOM_LEFT);
		}
	}
	if (ins.IsNew(KEY_INPUT_RIGHT)) 
	{
		pos_.x += move_; 
		SetDir(CharacterBase::DIR::RIGHT);
		if (IsMoveY)
		{
			if (pos_.y < prevPos_.y)SetDir(CharacterBase::DIR::TOP_RIGHT);
			else SetDir(CharacterBase::DIR::BOTTOM_RIGHT);
		}
	}

	//�}�b�v�̕`��؂�ւ�
	if (ins.IsTrgDown(KEY_INPUT_M))
	{
		ChangeIsDrawMap();
	}
}

void Player::GamePadController(void)
{
	InputManager& ins = InputManager::GetInstance();

	// ���X�e�B�b�N�̉���
	auto leftStickX = ins.GetInstance().GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLX;
	// ���X�e�B�b�N�̏c��
	auto leftStickY = ins.GetInstance().GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLY;
	//�X�e�B�b�N�̓��������킹�ĕۑ�
	Vector2 inputStick = { leftStickX,leftStickY };

	//�ړ�
	if (inputStick.x > 0)pos_.x += move_;
	else if (inputStick.x < 0)pos_.x -= move_;

	if (inputStick.y > 0)pos_.y += move_;
	else  if (inputStick.y < 0) pos_.y -= move_;

	//��������
	auto stickRad = static_cast<float>(atan2(static_cast<double>(inputStick.y), static_cast<double>(inputStick.x)));
	auto stickDeg= static_cast<float>(Utility::DegIn360(Utility::Rad2DegF(stickRad)));

	auto dir = CheckDir(stickDeg);

	if (pos_.x != prevPos_.x || pos_.y != prevPos_.y)
	{
		SetDir(dir);
	}

	

	//�}�b�v�̕`��
	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::TOP))ChangeIsDrawMap();
}

CharacterBase::DIR Player::CheckDir(float deg)
{
	//��������
	//�e�����S�T������
	int counter = 0;	//�������߂�����s���������J�E���g�B����ɉ����ĕ������Z�b�g
	DIR ret = DIR::RIGHT;	
	for (int i = 1; i < static_cast<int>(DIR::MAX); i++)
	{
		if (deg <= (UNIT_DIR_DEG * i) + UNIT_DIR_DEG / 2 &&
			deg > (UNIT_DIR_DEG * i) - UNIT_DIR_DEG / 2)
		{
			counter=i;
			break;
		}
	}
	
	switch (counter)
	{
	case DIR_TOP:
		ret = DIR::TOP;
		break;
	case DIR_TOP_RGH:
		ret = DIR::TOP_RIGHT;
		break;
	case DIR_RGH:
		ret = DIR::RIGHT;
		break;
	case DIR_BTM_RGH:
		ret = DIR::BOTTOM_RIGHT;
		break;
	case DIR_BTM:
		ret = DIR::BOTTOM;
		break;
	case DIR_BTM_LFT:
		ret = DIR::BOTTOM_LEFT;
		break;
	case DIR_LFT:
		ret = DIR::LEFT;
		break;
	case DIR_TOP_LFT:
		ret = DIR::TOP_LEFT;
		break;
	}

	return ret;
}

void Player::ChangeIsDrawMap(void)
{
	if (isDrawMap_)isDrawMap_ = false;
	else isDrawMap_ = true;
}