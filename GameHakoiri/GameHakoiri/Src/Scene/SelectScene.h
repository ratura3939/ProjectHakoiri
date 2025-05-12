//#pragma once
#include"SceneBase.h"
#include"../Common/Vector2.h"



class SelectScene :public SceneBase
{
public:
	enum class FRAME_TYPE {
		NOMAL,
		OBLONG,
		MAX
	};

	//�萔
	static constexpr int STAGE_NUM = 3;
	static constexpr int BACK_TITLE_X = 512;
	static constexpr int BACK_TITLE_Y = 256;
	static constexpr float ROT_MAX = 10.0f;
	static constexpr float ROT_MIN = -10.0f;
	static constexpr float ROT_UNIT = 0.5f;
	static constexpr float BACK_FRAME_EX = 4.0f;

	SelectScene(void);	//�R���X�g���N�^
	~SelectScene(void);	//�f�X�g���N�^

	bool Init(void);	//������
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool Release(void);	//���

private:
	void KeyboardContoroller(void);	// �L�[�{�[�h�̑���
	void GamePadController(void);	// �Q�[���p�b�h�̑���

	/// <summary>
	///�^�C�g���ɖ߂��I�����Ă��邩�ݒ�
	/// </summary>
	/// <param name="flag">true=���Ă���/false=���Ă��Ȃ�</param>
	void SetSelectBack(const bool flag);

	/// <summary>
	/// ��]���Z�b�g
	/// </summary>
	/// <param name=""></param>
	void ResetRot(void);

	int selectNum_;					//�J�[�\����̃X�e�[�W�i���o�[��ێ�
	int stageNumImg_[STAGE_NUM];	//�X�e�[�W�I���̉摜
	float stageNumRot_[STAGE_NUM];	//�X�e�[�W�I���̉摜
	bool rotDecre_;
	Vector2 stageNumPos_[STAGE_NUM];//�ʒu

	int checkImg_;		//�`�F�b�N�}�[�N

	int backTitleImg_;	//�^�C�g���ɖ߂�
	bool selectBack_;	//�^�C�g���ɖ߂�ɃJ�[�\���𓖂ĂĂ��邩

	int frame_[static_cast<int>(FRAME_TYPE::MAX)];	//�t���[���摜

	Vector2 prevStick_;	//1�t���[���O�̃X�e�B�b�N�̈ړ���ێ�

};