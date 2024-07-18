//#pragma once
#include"SceneBase.h"
#include"../Common/Vector2.h"



class SelectScene :public SceneBase
{
public:

	//�萔
	static constexpr int STAGE_NUM = 3;
	static constexpr int BACK_TITLE_X = 512;
	static constexpr int BACK_TITLE_Y = 256;
	static constexpr float ROT_MAX = 10.0f;
	static constexpr float ROT_MIN = -10.0f;
	static constexpr float ROT_UNIT = 0.5f;

	SelectScene(void);	//�R���X�g���N�^
	~SelectScene(void);	//�f�X�g���N�^

	bool Init(void);	//������
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool Release(void);	//���

private:
	int selectNum_;	//�J�[�\����̃X�e�[�W�i���o�[��ێ�
	int stageNumImg_[STAGE_NUM];	//�X�e�[�W�I���̉摜
	float stageNumRot_[STAGE_NUM];	//�X�e�[�W�I���̉摜
	bool rotDecre_;
	Vector2 stageNumPos_[STAGE_NUM];//�ʒu

	int checkImg_;	//�`�F�b�N�}�[�N

	int backTitleImg_;	//�^�C�g���ɖ߂�
	bool selectBack_;	//�^�C�g���ɖ߂�ɃJ�[�\���𓖂ĂĂ��邩

	int frame_[2];	//�t���[���摜

	Vector2 prevStick_;	//1�t���[���O�̃X�e�B�b�N�̈ړ���ێ�

	void KeyboardContoroller(void);	// �L�[�{�[�h�̑���
	void GamePadController(void);	// �Q�[���p�b�h�̑���

	void SetSelectBack(const bool flag);
	void ResetRot(void);
};