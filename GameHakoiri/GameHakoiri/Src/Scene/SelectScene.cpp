#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"../Manager/ResourceManager.h"
#include"../Manager/SoundManager.h"
#include"../Utility/Utility.h"
#include"../Application.h"
#include"../System/Plate.h"
#include"SelectScene.h"


//コンストラクタ
//********************************************************
SelectScene::SelectScene(void)
{
	selectNum_ = 0;
}
//デストラクタ
//********************************************************
SelectScene::~SelectScene(void)
{

}
//初期化
//********************************************************
bool SelectScene::Init(void)
{
	prevStick_ = {0,0};
	selectNum_ = 0;
	selectBack_ = false;

	ResetRot();

	stageNumImg_[0]= ResourceManager::GetInstance().Load(ResourceManager::SRC::STAGE_1_IMG).handleId_;
	stageNumImg_[1]= ResourceManager::GetInstance().Load(ResourceManager::SRC::STAGE_2_IMG).handleId_;
	stageNumImg_[2]= ResourceManager::GetInstance().Load(ResourceManager::SRC::STAGE_3_IMG).handleId_;

	checkImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::CHECK_IMG).handleId_;
	backTitleImg_ = ResourceManager::GetInstance().Load(ResourceManager::SRC::BACK_TITLE_IMG).handleId_;

	frame_[0] = ResourceManager::GetInstance().Load(ResourceManager::SRC::FRAME_IMG).handleId_;
	frame_[1] = ResourceManager::GetInstance().Load(ResourceManager::SRC::FRAME_OBLONG_2_IMG).handleId_;

	stageNumPos_[0] = { Application::SCREEN_SIZE_X / 4,Application::SCREEN_SIZE_Y / 4 };
	stageNumPos_[1] = { Application::SCREEN_SIZE_X / 2,Application::SCREEN_SIZE_Y / 4 };
	stageNumPos_[2] = { Application::SCREEN_SIZE_X / 4 + Application::SCREEN_SIZE_X / 2,
		Application::SCREEN_SIZE_Y / 4 };


	SoundManager::GetInstance().PlayBgmOfSelect();

	//正常に処理が行われたので
	return true;
}
//更新
//********************************************************
void SelectScene::Update(void)
{
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

	if (rotDecre_)
	{
		stageNumRot_[selectNum_] -= ROT_UNIT;
		if (stageNumRot_[selectNum_] < ROT_MIN)rotDecre_ = false;
	}
	else
	{
		stageNumRot_[selectNum_] += ROT_UNIT;
		if (stageNumRot_[selectNum_] > ROT_MAX)rotDecre_ = true;
	}
}
//描画
//********************************************************
void SelectScene::Draw(void)
{

	auto& stg = SceneManager::GetInstance();

	//ステージナンバーの描画
	for (int i = 0; i < STAGE_NUM; i++)
	{
		DrawRotaGraph(stageNumPos_[i].x, stageNumPos_[i].y,
			1.0f, stageNumRot_[i] * Utility::DEG2RAD,
			stageNumImg_[i], true, false);
		if (stg.IsClearStage(i))
		{
			DrawRotaGraph(stageNumPos_[i].x, stageNumPos_[i].y,
				1.0f, 0.0f * Utility::DEG2RAD,
				checkImg_, true, false);
		}
	}

	//タイトルに戻るの描画
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y - BACK_TITLE_Y / 2,
		1.0f, 0.0f * Utility::DEG2RAD,
		backTitleImg_, true, false);

	//フレームの描画
	if (selectBack_)	//タイトルに戻るにカーソルがあっていたら
	{
		DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y - BACK_TITLE_Y / 2,
			4.0f, 0.0f * Utility::DEG2RAD,
			frame_[1], true, false);
	}
	else
	{
		DrawRotaGraph(stageNumPos_[selectNum_].x, stageNumPos_[selectNum_].y,
			4.0f, stageNumRot_[selectNum_] * Utility::DEG2RAD,
			frame_[0], true, false);
	}
}
//解放
//********************************************************
bool SelectScene::Release(void)
{
	//正常に処理が行われたので
	return true;
}

void SelectScene::KeyboardContoroller(void)
{
	auto& ins = InputManager::GetInstance();

	auto prevSelect = selectNum_;
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		if (!selectBack_)
		{
			SoundManager::GetInstance().StopBgmOfSelect();
			//ステージナンバーを受け渡しシーン切り替え
			SceneManager::GetInstance().SetStageNum(selectNum_ + 1);
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::GAME, true);
		}
		else
		{
			SoundManager::GetInstance().StopBgmOfSelect();
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::TITLE, true);
		}
	}
	//左右移動
	if (ins.IsTrgDown(KEY_INPUT_RIGHT))
	{
		selectNum_++;
		if (selectNum_ >= STAGE_NUM)selectNum_ = STAGE_NUM - 1;
	}
	if (ins.IsTrgDown(KEY_INPUT_LEFT))
	{
		selectNum_--;
		if (selectNum_ < 0)selectNum_ = 0;
	}
	if (prevSelect != selectNum_)ResetRot();
	//動きによって下段にいるか上段にいるかを設定
	if (ins.IsTrgDown(KEY_INPUT_DOWN))selectBack_ = true;
	if (ins.IsTrgDown(KEY_INPUT_UP))selectBack_ = false;
}

void SelectScene::GamePadController(void)
{
	auto& ins = InputManager::GetInstance();

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		if (!selectBack_)
		{
			SoundManager::GetInstance().StopBgmOfSelect();
			//ステージナンバーを受け渡しシーン切り替え
			SceneManager::GetInstance().SetStageNum(selectNum_ + 1);
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::GAME, true);
		}
		else
		{
			SoundManager::GetInstance().StopBgmOfSelect();
			SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::TITLE, true);
		}
	}

	// 左スティックの横軸
	auto leftStickX = ins.GetInstance().GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLX;
	// 左スティックの縦軸
	auto leftStickY = ins.GetInstance().GetJPadInputState(InputManager::JOYPAD_NO::PAD1).AKeyLY;

	auto prevSelect = selectNum_;
	//左右移動
	if (prevStick_.x == 0)
	{
		if (leftStickX > 0)
		{
			selectNum_++;
			if (selectNum_ >= STAGE_NUM)selectNum_ = STAGE_NUM - 1;
		}
		else if (leftStickX < 0)
		{
			selectNum_--;
			if (selectNum_ < 0)selectNum_ = 0;
		}
		if (prevSelect != selectNum_)ResetRot();
	}
	//Y軸移動
	if (prevStick_.y == 0)
	{
		//動きによって下段にいるか上段にいるかを設定
		if (leftStickY > 0)selectBack_ = true;
		else if (leftStickY < 0)selectBack_ = false;
	}

	prevStick_ = { leftStickX ,leftStickY };
}

void SelectScene::SetSelectBack(const bool flag)
{
	selectBack_ = flag;
}

void SelectScene::ResetRot(void)
{
	stageNumRot_[0] = 0.0f;
	stageNumRot_[1] = 0.0f;
	stageNumRot_[2] = 0.0f;
	rotDecre_ = false;
}
