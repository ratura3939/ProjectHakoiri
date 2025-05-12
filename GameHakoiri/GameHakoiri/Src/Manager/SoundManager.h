#pragma once
class SoundManager
{
public:
	//�V���O���g����
	static bool CreateInstance(void);		//�C���X�^���X�̐���
	static SoundManager& GetInstance(void);	//�C���X�^���X�̎擾

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

	//���ʉ�
	void PlaySndEnter(bool flag);
	void PlaySndMove(void);
	void PlaySndReset(void);
	void PlaySndSelect(void);

private:
	//BGM
	int titleBgm_;		//�^�C�g��
	int selectBgm_;		//�Z���N�g
	int pazzleBgm_;		//�p�Y��
	int stealthBgm_;	//�X�e���X
	int successBgm_;	//����
	int failedBgm_;		//���s
	int endingBgm_;		//�G���f�B���O

	//���ʉ�
	int enterSnd_;		//����
	int canselSnd_;		//�L�����Z��
	int moveSnd_;		//�ړ�
	int resetSnd_;		//���Z�b�g
	int selectSnd_;		//�I��

	SoundManager(void);
	void Destroy(void);	//�f�X�g���N�^
	static SoundManager* instance_;
};

