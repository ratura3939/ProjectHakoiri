#pragma once
class SoundManager
{
public:
	//�V���O���g����
	static bool CreateInstance(void);		//�C���X�^���X�̐���
	static SoundManager& GetInstance(void);	//�C���X�^���X�̎擾

	void Init(void);
	void Relese(void);

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

	void PlaySndEnter(bool flag);
	void PlaySndMove(void);
	void PlaySndReset(void);
	void PlaySndSelect(void);

private:
	int titleBgm_;
	int selectBgm_;
	int pazzleBgm_;
	int stealthBgm_;
	int successBgm_;
	int failedBgm_;
	int endingBgm_;

	int enterSnd_;
	int canselSnd_;
	int moveSnd_;
	int resetSnd_;
	int selectSnd_;

	SoundManager(void);
	void Destroy(void);	//�f�X�g���N�^
	static SoundManager* instance_;
};

