#include<DxLib.h>
#include"Application.h"
#include"Manager/SceneManager.h"
#include"Manager/InputManager.h"
#include"Manager/ResourceManager.h"

Application* Application::instance_ = nullptr;


const std::string Application::PATH_ANIM = "Data/Anim/";
const std::string Application::PATH_MAP = "Data/Csv/Map/";
const std::string Application::PATH_OBSTACLE = "Data/Csv/Map/Mapchip/";
const std::string Application::PATH_PAZZLE = "Data/Csv/Pazzle/";
const std::string Application::PATH_CHARACTER = "Data/Img/Character/";
const std::string Application::PATH_MAPCHIP = "Data/Img/Map/";
const std::string Application::PATH_ROOM = "Data/Img/Room/";
const std::string Application::PATH_SYSTEM = "Data/Img/System/";
const std::string Application::PATH_MANUAL = "Data/Img/Manual/";
const std::string Application::PATH_SOUND = "Data/Snd/";
const std::string Application::PATH_BGM = "Data/Snd/Bgm/";

//コンストラクタ
//********************************************************
Application::Application(void)
{
	
}
//コピーコンストラクタ
//********************************************************
Application::Application(const Application& ins)
{

}
//デストラクタ
//********************************************************
void Application::Destroy(void)
{
	delete instance_;
}

//初期化
//********************************************************
bool Application::Init(void)
{
	//システム処理
	//------------------------------------------------------------
	SetWindowText("ProjectHakoiri");	//ゲームウィンドウのタイトル
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);			//ゲームウィンドウのサイズと色モードを設定
	ChangeWindowMode(true);				//ゲームウィンドウの表示方法（false : フルスクリーン）
	if (DxLib_Init() == -1)				//DXライブラリの初期化処理
	{
		return false;						//DXライブラリの初期化失敗のためシステム終了
	}
	
	//入力管理初期化
	InputManager::CreateInstance();
	//リソース管理初期化
	ResourceManager::CreateInstance();

	//インスタンスの生成
	if (!SceneManager::CreateInstance())
	{
		return false;	//初期化失敗のためシステム終了
	}

	currentFrame_ = 0;
	lastFrame_ = 0;
	//正しく処理が終了したので
	return true;
}
//起動
//********************************************************
void Application::Run(void)
{
	SceneManager& instance = SceneManager::GetInstance();
	//ゲームループ
	//------------------------------------------------------------
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//ゲームメイン処理
		//------------------------------------------------------------------------

		Sleep(1);	//システムに処理を返す
		currentFrame_ = GetNowCount();


		if (currentFrame_ - lastFrame_ >= frameRate)
		{
			lastFrame_ = currentFrame_;
			InputManager::GetInstance().Update();
			instance.Update();	//更新
		}

		//描画処理
		//------------------------------------------------------------------------
		SetDrawScreen(DX_SCREEN_BACK);	//描画する画面を裏の画面に設定
		ClearDrawScreen();				//描画する画面の内容を消去

		instance.Draw();	//描画

		ScreenFlip();					//裏の画面を表の画面に瞬間コピー
	}
}

//解放
//********************************************************
bool Application::Release(void)
{
	instance_ = nullptr;
	SceneManager::GetInstance().Release();
	ResourceManager::GetInstance().Destroy();
	//システム終了処理
//------------------------------------------------------------
	DxLib_End();	//DXライブラリの終了処理
	//正しく処理が終了したので
	return true;
}

//シングルトン化
//インスタンスの生成
//********************************************************
bool Application::CreateInstance(void)
{
	if (instance_ == nullptr)
	{
		instance_ = new Application();
	}
	if (!instance_->Init())
	{
		OutputDebugString("アプリケーション初期化失敗");
		return false;
	}
	//正しく処理が終了したので
	return true;
}
//インスタンスの取得
//********************************************************
Application& Application::GetInstance(void)
{
	return *instance_;
}