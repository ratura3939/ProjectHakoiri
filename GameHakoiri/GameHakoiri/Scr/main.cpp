//ゲーム制作：箱入り娘の脱出
//氏名：松永諒雅
//-----------------------------------------------------

#include<DxLib.h>	//DXライブラリの使用
#include"Application.h"

int WINAPI WinMain(
	_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	if (Application::CreateInstance() == false)	//初期化
	{
		return -1;	//初期化失敗で終了
	}

	Application& instance = Application::GetInstance();


	instance.Run();		//ゲームループ開始

	instance.Release();	//解放

	return 0;			//ゲームの終了
}