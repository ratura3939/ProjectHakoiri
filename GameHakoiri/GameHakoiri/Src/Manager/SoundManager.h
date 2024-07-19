#pragma once
class SoundManager
{
public:
	//�V���O���g����
	static bool CreateInstance(void);		//�C���X�^���X�̐���
	static SoundManager& GetInstance(void);	//�C���X�^���X�̎擾

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
	void Destroy(void);	//�f�X�g���N�^
	static SoundManager* instance_;
};

