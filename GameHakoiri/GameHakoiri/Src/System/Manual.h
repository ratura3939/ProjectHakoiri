#pragma once
#include"../Manager/SceneManager.h"
#include"../Scene/GameScene.h"
#include"../Common/Vector2.h"


class Manual
{
public:

	//�萔
	static constexpr int MANUAL_PAGE = 3;

	//�ꏊ�i�X�N���[���T�C�Y����{�b�N�X�̃T�C�Y�����j
	static constexpr int OK_KBD_X = 1280 - 256 / 2;
	static constexpr int OK_KBD_Y = 780 - 128;
	static constexpr int OK_PAD_X = 1280 - 256 / 2;
	static constexpr int OK_PAD_Y = 780 / 2 - 128;

	//�V���O���g����
	static bool CreateInstance(void);		//�C���X�^���X�̐���
	static Manual& GetInstance(void);	//�C���X�^���X�̎擾

	void Init(void);
	void Update(void);
	void Draw(void);

	void SetManual(GameScene::MODE mode, SceneManager::CONTROLLER cnt);
	bool IsFinish(void);

private:

	bool isFinish_;
	int prevStick_;
	Vector2 okPos_;

	int manualImg_[static_cast<int>(GameScene::MODE::MAX)][2];	//�V�[���ʂ̃}�j���A��
	//�R���g���[���[��+�V�[���ʂ̃}�j���A��
	int cntManualImg_[static_cast<int>(SceneManager::CONTROLLER::MAX)][static_cast<int>(GameScene::MODE::MAX)];
	int okImg_;//OKBOX��IMG
	int useImg_[3];	//�`��ɕK�v�Ȃ��̂���������
	int useIdx_;


	void KeyboardContoroller(void);	// �L�[�{�[�h�̑���
	void GamePadController(void);	// �Q�[���p�b�h�̑���

	//�V���O���g����
	Manual(void);
	void Destroy(void);

	static Manual* instance_;
};

