#include"DxLib.h"
#include"Application.h"
#include"SceneManager.h"

Application* Application::instance_ = nullptr;

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
	SetWindowText("2316026 松永諒雅");	//ゲームウィンドウのタイトル
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);			//ゲームウィンドウのサイズと色モードを設定
	ChangeWindowMode(true);				//ゲームウィンドウの表示方法（false : フルスクリーン）
	if (DxLib_Init() == -1)				//DXライブラリの初期化処理
	{
		return false;						//DXライブラリの初期化失敗のためシステム終了
	}

	//インスタンスの生成
	if (!SceneManager::CreateInstance())
	{
		return false;	//初期化失敗のためシステム終了
	}

	//正しく処理が終了したので
	return true;
}
//起動
//********************************************************
void Application::Run(void)
{
	//ゲームループ
	//------------------------------------------------------------
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//ゲームメイン処理
		//------------------------------------------------------------------------
		SceneManager::GetInstance().Update();	//更新

		//描画処理
		//------------------------------------------------------------------------
		SetDrawScreen(DX_SCREEN_BACK);	//描画する画面を裏の画面に設定
		ClearDrawScreen();				//描画する画面の内容を消去

		SceneManager::GetInstance().Draw();	//描画

		ScreenFlip();					//裏の画面を表の画面に瞬間コピー
	}
}

//解放
//********************************************************
bool Application::Release(void)
{
	instance_ = nullptr;
	SceneManager::GetInstance().Release();
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