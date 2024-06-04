//#pragma once

#include <string>

class Application
{
public:
	//定数
	// スクリーンサイズ
	//-------------------------------------------
	static constexpr int SCREEN_SIZE_X = 1280;
	static constexpr int SCREEN_SIZE_Y = 720;

	static constexpr int FPS = 60;
	static constexpr float SIE = 3.1415926535;

	// データパス関連
	//-------------------------------------------
	static const std::string PATH_ANIM;

	static const std::string PATH_MAP;
	static const std::string PATH_OBSTACLE;
	static const std::string PATH_PAZZLE;

	static const std::string PATH_CHARACTER;
	static const std::string PATH_MAPCHIP;
	static const std::string PATH_ROOM;
	static const std::string PATH_SYSTEM;
	static const std::string PATH_SOUND;
	static const std::string PATH_BGM;

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