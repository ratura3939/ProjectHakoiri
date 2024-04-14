//#pragma once

class Application
{
public:
	//定数
	static constexpr int SCREEN_SIZE_X = 1280;
	static constexpr int SCREEN_SIZE_Y = 720;

	//メンバ関数
	bool Init(void);	//初期化
	void Run(void);		//起動
	bool Release(void);	//解放

	//シングルトン化
	static bool CreateInstance(void);		//インスタンスの生成
	static Application& GetInstance(void);	//インスタンスの取得

private:

	//シングルトン化
	Application(void);	//コンストラクタ
	Application(const Application&);	//コピーコンストラクタ
	void Destroy(void);	//デストラクタ

	static Application* instance_;
};