#pragma once
class SoundManager
{
public:
	//シングルトン化
	static bool CreateInstance(void);		//インスタンスの生成
	static SoundManager& GetInstance(void);	//インスタンスの取得

	void Init(void);
	void Relese(void);

	//BGM
	void PlayBgmOfTitle(void);
	void StopBgmOfTitle(void);
	void PlayBgmOfSelect(void);
	void StopBgmOfSelect(void);
	void PlayBgmOfPazzle(void);
	void StopBgmOfPazzle(void);
	void PlayBgmOfStealth(void);
	void StopBgmOfStealth(void);
	void PlayBgmOfSuccess(void);
	void StopBgmOfSuccess(void);
	void PlayBgmOfFailed(void);
	void StopBgmOfFailed(void);
	void PlayBgmOfEnding(void);
	void StopBgmOfEnding(void);

	//効果音
	void PlaySndEnter(bool flag);
	void PlaySndMove(void);
	void PlaySndReset(void);
	void PlaySndSelect(void);

private:
	//BGM
	int titleBgm_;		//タイトル
	int selectBgm_;		//セレクト
	int pazzleBgm_;		//パズル
	int stealthBgm_;	//ステルス
	int successBgm_;	//成功
	int failedBgm_;		//失敗
	int endingBgm_;		//エンディング

	//効果音
	int enterSnd_;		//決定
	int canselSnd_;		//キャンセル
	int moveSnd_;		//移動
	int resetSnd_;		//リセット
	int selectSnd_;		//選択

	SoundManager(void);
	void Destroy(void);	//デストラクタ
	static SoundManager* instance_;
};

