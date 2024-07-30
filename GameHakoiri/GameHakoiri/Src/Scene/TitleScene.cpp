#include<DxLib.h>
#include"../Manager/SceneManager.h"
#include"../Manager/InputManager.h"
#include"../Manager/ResourceManager.h"
#include"../Manager/SoundManager.h"
#include"../System/Plate.h"
#include"../Application.h"
#include"../Utility/Utility.h"
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

	auto& rsM = ResourceManager::GetInstance();
	titleImg_= rsM.Load(ResourceManager::SRC::TITLE_IMG).handleId_;
	startImg_ = rsM.Load(ResourceManager::SRC::START_IMG).handleId_;
	startEx_ = 0.7f;

	SoundManager::GetInstance().PlayBgmOfTitle();
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

		startEx_ += 0.01f;
		if (startEx_ > START_EX_F)startEx_ = START_EX_S;
	}
	else
	{
		auto& plate = Plate::GetInstance();
		plate.Update(Plate::TYPE::SELECT);
		if (plate.IsFinish())
		{

			//プレートの一連の処理が終わっていたらシーン切り替え
			if (plate.GetAnswer() == Plate::ANSWER::OK)
			{
				SoundManager::GetInstance().StopBgmOfTitle();
				SceneManager::GetInstance().ChangeScene(SceneManager::SCENEID::SELECT, true);
			}
				
			else isCheck_ = false;
		}
	}
}
//描画
//********************************************************
void TitleScene::Draw(void)
{
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 4,
		1.0,
		0.0 * Utility::DEG2RAD,
		titleImg_,
		true,
		false);

	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y -256,
		startEx_,
		0.0 * Utility::DEG2RAD,
		startImg_,
		true,
		false);

	if (isCheck_) Plate::GetInstance().Draw(Plate::TYPE::SELECT, str_, true);
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
	auto& snd = SoundManager::GetInstance();

	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		snd.PlaySndEnter(true);
		SceneManager::GetInstance().SetController(SceneManager::CONTROLLER::KEYBOARD);
		isCheck_ = true;
		Plate::GetInstance().SetState(Plate::STATE::GO);
		str_ = "操作方法はキーボードで良いですか？\n\n※操作方法を変更する場合はこのタイトルまで戻る必要があります";
	}

	//製作者専用コマンド
	//クリア状況のリセット
	if (ins.IsNew(KEY_INPUT_R) &&
		ins.IsNew(KEY_INPUT_E) &&
		ins.IsNew(KEY_INPUT_S) &&
		ins.IsNew(KEY_INPUT_T))
	{
		snd.PlaySndReset();
		SceneManager::GetInstance().Reset();
	}
	//各ステージをクリア判定に
	if (ins.IsNew(KEY_INPUT_LSHIFT))
	{
		if (ins.IsNew(KEY_INPUT_1))SceneManager::GetInstance().CustomClearFlag(1);
		if (ins.IsNew(KEY_INPUT_2))SceneManager::GetInstance().CustomClearFlag(2);
		if (ins.IsNew(KEY_INPUT_3))SceneManager::GetInstance().CustomClearFlag(3);
	}
}

void TitleScene::GamePadController(void)
{
	InputManager& ins = InputManager::GetInstance();
	auto& snd = SoundManager::GetInstance();

	if (ins.IsPadBtnTrgDown(InputManager::JOYPAD_NO::PAD1, InputManager::JOYPAD_BTN::DOWN))
	{
		snd.PlaySndEnter(true);
		SceneManager::GetInstance().SetController(SceneManager::CONTROLLER::PAD);
		isCheck_ = true;
		str_ = "操作方法はコントローラーで良いですか？\n\n※操作方法を変更する場合はこのタイトルまで戻る必要があります";
	}
}
