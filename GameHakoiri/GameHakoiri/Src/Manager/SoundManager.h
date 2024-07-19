#pragma once
class SoundManager
{
public:
	//シングルトン化
	static bool CreateInstance(void);		//インスタンスの生成
	static SoundManager& GetInstance(void);	//インスタンスの取得

	void Init(void);

	void PlayBgmOfTitle(void);
	void StopBgmOfTitle(void);
	void PlayBgmOfSelect(void);
	void StopBgmOfSelect(void);
	void PlayBgmOfPazzle(void);
	void StopBgmOfPazzle(void);
	void PlayBgmOfStealth(void);
	void StopBgmOfStealth(void);

private:
	int titleBgm_;
	int selectBgm_;
	int pazzleBgm_;
	int stealthBgm_;

	SoundManager(void);
	void Destroy(void);	//デストラクタ
	static SoundManager* instance_;
};

