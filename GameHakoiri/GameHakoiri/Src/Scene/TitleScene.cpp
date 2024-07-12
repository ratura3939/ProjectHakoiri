#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"../System/Plate.h"
#include"TitleScene.h"


//コンストラクタ
//********************************************************
TitleScene::TitleScene(void)
{
	isNext_ = false;
}
//デストラクタ
//********************************************************
TitleScene::~TitleScene(void)
{

}
//初期化
//********************************************************
bool TitleScene::Init(void)
{
	isCheck_ = false;
	str_ = "NONE";
	//正常に処理が行われたので
	return true;
}
//更新
//********************************************************
void TitleScene::Update(void)
{
	if (!isCheck_)
	{
		KeyboardContoroller();
		GamePadController();
	}
	else
	{
		auto& plate = Plate::GetInstance();
		plate.Update(Plate::TYPE::SELECT);
		if (plate.IsFinish())
		{

			//プレートの一連の処理が終わっていたらシーン切り替え
			if (plate.GetAnswer() == Plate::ANSWER::OK)
				SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::SELECT, true);
			else isCheck_ = false;
		}
			
	}
}
//描画
//********************************************************
void TitleScene::Draw(void)
{
	DrawString(0, 0, "TitleScene",0xffffff, true);
	DrawBox(50, 50, 500, 500, 0xffff00, true);

	if (isCheck_) Plate::GetInstance().Draw(Plate::TYPE::SELECT,str_);
}
//解放
//********************************************************
bool TitleScene::Release(void)
{
	//正常に処理が行われたので
	return true;
}

void TitleScene::KeyboardContoroller(void)
{
	InputManager& ins = InputManager::GetInstance();

	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().SetController(SceneManager::CONTROLLER::KEYBOARD);
		isCheck_ = true;
		Plate::GetInstance().SetState(Plate::STATE::GO);
		str_ = "操作方法はキーボードで良いですか？";
	}
}

void TitleScene::GamePadController(void)
{
	InputManager& ins = InputManager::GetInstance();

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		SceneManager::GetInstance().SetController(SceneManager::CONTROLLER::PAD);
		isCheck_ = true;
		str_ = "操作方法はコントローラーで良いですか？";
	}
}
