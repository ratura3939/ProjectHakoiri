#include<DxLib.h>
#include"../Manager/ResourceManager.h"
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"../Utility/Utility.h"
#include"../Application.h"
#include "Plate.h"


Plate* Plate::instance_ = nullptr;

Plate::Plate(void)
{
	plateImg_[0] = 0;
	plateImg_[1] = 0;
	frameImg_ = 0;
	answer_ = ANSWER::OK;
	isSelect_ = false;
	isFinish_ = false;
}

void Plate::Destroy(void)
{
	delete instance_;
}

bool Plate::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new Plate;
	}

	instance_->Init();

	return true;
}

Plate& Plate::GetInstance(void)
{
	return *instance_;
}

void Plate::Init(void)
{
	plateImg_[static_cast<int>(TYPE::SELECT)] = 
		ResourceManager::GetInstance().Load(ResourceManager::SRC::PLATE_SELECT_IMG).handleId_;
	plateImg_[static_cast<int>(TYPE::CHECK)] = 
		ResourceManager::GetInstance().Load(ResourceManager::SRC::PLATE_CHECK_IMG).handleId_;
	boxImg_[static_cast<int>(ANSWER::NO)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::SELECT_NO_IMG).handleId_;
	boxImg_[static_cast<int>(ANSWER::OK)] =
		ResourceManager::GetInstance().Load(ResourceManager::SRC::SELECT_OK_IMG).handleId_;

	


	Reset();
}

void Plate::Reset(void)
{
 	frameImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::FRAME_OBLONG_2_IMG).handleId_;

	platePos_ = { Application::SCREEN_SIZE_X / 2,-PLATE_SIZE / 2 };
	boxPos_[static_cast<int>(TYPE::SELECT)][static_cast<int>(ANSWER::OK)]
		= { platePos_.x - DELTA_X,platePos_.y + DELTA_Y };
	boxPos_[static_cast<int>(TYPE::SELECT)][static_cast<int>(ANSWER::NO)]
		= { platePos_.x + DELTA_X,platePos_.y + DELTA_Y };
	boxPos_[static_cast<int>(TYPE::CHECK)][static_cast<int>(ANSWER::OK)]
		= { platePos_.x,platePos_.y + DELTA_Y };
	//これだけ映らないように座標を調節
	boxPos_[static_cast<int>(TYPE::CHECK)][static_cast<int>(ANSWER::NO)]
		= { platePos_.x,-EXCEPTION };

	frameAnim_ = 0;
	prevStick_ = 0;
	state_ = STATE::GO;
	answer_ = ANSWER::OK;
	isSelect_ = false;
	isFinish_ = false;
}

bool Plate::Update(TYPE type)
{
	switch (state_)
	{
	case Plate::STATE::GO:
		UpdateGo(type);
		break;
	case Plate::STATE::STOP:
		UpdateStop(type);
		break;
	case Plate::STATE::BACK:
		UpdateBack(type);
		break;
	}
    return false;
}

void Plate::UpdateGo(TYPE type)
{
	//遷移状態の初めであるこの部分でisFinishがtrueということは二回目以降なので変数をリセット
	if (isFinish_) Reset();

	platePos_.y += PLATE_SPEED;
	boxPos_[static_cast<int>(type)][static_cast<int>(ANSWER::NO)].y += PLATE_SPEED;
	boxPos_[static_cast<int>(type)][static_cast<int>(ANSWER::OK)].y += PLATE_SPEED;

	if (platePos_.y > Application::SCREEN_SIZE_Y / 2)
	{
		SetState(STATE::STOP);
	}
}

void Plate::UpdateStop(TYPE type)
{
	frameAnim_++;
	auto cnt = SceneManager::GetInstance().GetController();
	INPUT ins = INPUT::NONE;

	switch (cnt)
	{
	case SceneManager::CONTROLLER::KEYBOARD:
		ins = KeyboardContoroller();
		break;
	case SceneManager::CONTROLLER::PAD:
		ins = GamePadController();
		break;
	}

	//二択の選択画面のみ動きを感知する
	if (type == TYPE::SELECT)
	{
		if (ins == INPUT::MOVE)
		{
			ChangeAnswer();
		}
	}
	//選択されていたら遷移
	if (ins == INPUT::SELECT)
	{
		SetIsSelect(true);
		SetState(STATE::BACK);
	}
}

void Plate::UpdateBack(TYPE type)
{
	platePos_.y -= PLATE_SPEED;
	boxPos_[static_cast<int>(type)][static_cast<int>(ANSWER::NO)].y -= PLATE_SPEED;
	boxPos_[static_cast<int>(type)][static_cast<int>(ANSWER::OK)].y -= PLATE_SPEED;

	//画像の下部分が画面外に行ったとき
	if (platePos_.y + PLATE_SIZE / 2 < 0.0f)
	{
		SetIsFinish(true);
		SetState(STATE::GO);
	}
}

void Plate::Draw(TYPE type, std::string str)
{
	DrawDebug(type);

	//ボードの表示
	DrawRotaGraph(platePos_.x, platePos_.y,
		1.0f,
		0.0f * Utility::DEG2RAD,
		plateImg_[static_cast<int>(type)],
		true,
		false);

	//文章の表示
	auto size = str.length();
	auto pos = Vector2F{ platePos_.x - PLATE_SIZE / 4,platePos_.y };
	DrawFormatString(pos.x, pos.y, 0x000000, "%s", str.c_str());

	//ボタンの表示
	for (int i = 0; i < static_cast<int>(ANSWER::MAX); i++)
	{
		DrawRotaGraph(boxPos_[static_cast<int>(type)][i].x, boxPos_[static_cast<int>(type)][i].y,
			1.0f,
			0.0f * Utility::DEG2RAD,
			boxImg_[i],
			true,
			false);
	}


	if (frameAnim_ % (Application::FPS / 2) < FLASH)
	{
		//フレームの表示
		DrawRotaGraph(boxPos_[static_cast<int>(type)][static_cast<int>(answer_)].x,
			boxPos_[static_cast<int>(type)][static_cast<int>(answer_)].y,
			2.0f,
			0.0f * Utility::DEG2RAD,
			frameImg_,
			true,
			false);
	}
}

void Plate::DrawDebug(TYPE type)
{
	DrawFormatString(0, 50, 0xff0000, "platePos={%.1f,%.1f}\nOKPos={%.1f,%.1f}\nNOPos={%.1f,%.1f}",
		platePos_.x,platePos_.y,
		boxPos_[static_cast<int>(type)][static_cast<int>(ANSWER::OK)].x,
			boxPos_[static_cast<int>(type)][static_cast<int>(ANSWER::OK)].y,
				boxPos_[static_cast<int>(type)][static_cast<int>(ANSWER::NO)].x,
					boxPos_[static_cast<int>(type)][static_cast<int>(ANSWER::NO)].y);
}

void Plate::Release(void)
{
	
}

Plate::ANSWER Plate::GetAnswer(void)
{
	return answer_;
}

bool Plate::IsSelect(void)
{
	return isSelect_;
}

bool Plate::IsFinish(void)
{
	return isFinish_;
}

void Plate::SetState(STATE st)
{
	state_ = st;
}



void Plate::ChangeAnswer(void)
{
	if (answer_==ANSWER::OK) answer_ = ANSWER::NO;
	else if(answer_ == ANSWER::NO)answer_ = ANSWER::OK;
}

void Plate::SetIsFinish(bool flag)
{
	isFinish_ = flag;
}

void Plate::SetIsSelect(bool flag)
{
	isSelect_ = flag;
}

Plate::INPUT Plate::KeyboardContoroller(void)
{
	auto& ins = InputManager::GetInstance();
	INPUT ret = INPUT::NONE;

	if (ins.IsTrgDown(KEY_INPUT_LEFT) || ins.IsTrgDown(KEY_INPUT_RIGHT))ret = INPUT::MOVE;
	if (ins.IsTrgDown(KEY_INPUT_SPACE))ret = INPUT::SELECT;

	return ret;
}

Plate::INPUT Plate::GamePadController(void)
{
	auto& ins = InputManager::GetInstance();
	INPUT ret = INPUT::NONE;

	// 左スティックの横軸
	auto leftStickX = ins.GetInstance().GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLX;
	if (prevStick_ == 0 && leftStickX != 0)ret = INPUT::MOVE;

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))ret = INPUT::SELECT;

	prevStick_ = leftStickX;
	return ret;
}
