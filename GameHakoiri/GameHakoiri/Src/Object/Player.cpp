#include<DxLib.h>
#include"../Manager/ResourceManager.h"
#include"../Manager/InputManager.h"
#include "Player.h"

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
}

void Player::Move(void)
{
	//移動前の方向を保存
	auto prevDir = GetDir();

	KeyboardContoroller();
	GamePadController();

	//全ての移動処理が終わってからアニメーションを変更するか決める
	if (GetDir() != prevDir)
	{
		ResetAnim(GetDir());
	}
}

void Player::KeyboardContoroller(void)
{
	InputManager& ins = InputManager::GetInstance();

	//移動
	if (ins.IsNew(KEY_INPUT_UP)) 
	{
		pos_.y -= move_; 
		SetDir(CharacterBase::DIR::TOP);
	}
	if (ins.IsNew(KEY_INPUT_DOWN))
	{
		pos_.y += move_; 
		SetDir(CharacterBase::DIR::BOTTOM);
	}
	if (ins.IsNew(KEY_INPUT_LEFT)) 
	{
		pos_.x -= move_; 
		SetDir(CharacterBase::DIR::LEFT);
	}
	if (ins.IsNew(KEY_INPUT_RIGHT)) 
	{
		pos_.x += move_; 
		SetDir(CharacterBase::DIR::RIGHT);
	}

}

void Player::GamePadController(void)
{
	InputManager& ins = InputManager::GetInstance();
}
