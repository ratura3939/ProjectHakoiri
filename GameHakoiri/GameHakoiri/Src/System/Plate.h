#pragma once
#include"../Common/Vector2F.h"
#include"../Utility/Utility.h"

class Plate
{
public:
	//�萔
	static constexpr float FRAME_EX = 2.0f;

	//�v���[�g�̏��
	enum class STATE
	{
		GO,
		STOP,
		BACK
	};

	//�v���[�g�̎��
	enum class TYPE
	{
		SELECT,
		CHECK,
		MAX
	};

	enum class INPUT
	{
		NONE,
		MOVE,
		SELECT
	};

	enum class ANSWER
	{
		NO,
		OK,
		MAX
	};

	//�萔
	static constexpr float PLATE_SIZE = 512.0f;
	static constexpr float BOX_SIZE_X = 256.0f;
	static constexpr float BOX_SIZE_Y = 128.0f;
	static constexpr float PLATE_SPEED = 20.0f;
	static constexpr float DELTA_X = BOX_SIZE_X / 2;
	static constexpr float DELTA_Y = PLATE_SIZE / 2 - BOX_SIZE_Y / 2;
	static constexpr float EXCEPTION = PLATE_SIZE * 2;
	static constexpr int   FLASH = 20;

	//�V���O���g����
	static bool CreateInstance(void);		//�C���X�^���X�̐���
	static Plate& GetInstance(void);	//�C���X�^���X�̎擾

	void Init(void);
	bool Update(TYPE type);
	void UpdateGo(TYPE type);
	void UpdateStop(TYPE type);
	void UpdateBack(TYPE type);
	void Draw(TYPE type,std::string str,bool strLong);


	void Release(void);

	ANSWER GetAnswer(void);		//OK/NO��Ԃ�
	bool IsSelect(void);		//�I������������������Ԃ�
	bool IsFinish(void);		//��A�̓��삪�I����������Ԃ�
	void SetState(STATE st);	//��Ԃ̃Z�b�g
	void Reset(void);			//���Z�b�g

private:
	//�J��
	STATE state_;
	//�摜
	int plateImg_[static_cast<int>(TYPE::MAX)];
	int boxImg_[static_cast<int>(ANSWER::MAX)];
	int frameImg_;

	//�ʒu
	Vector2F platePos_;
	Vector2F boxPos_[static_cast<int>(TYPE::MAX)][static_cast<int>(ANSWER::MAX)];

	int frameAnim_;
	int prevStick_;


	ANSWER answer_;	//OK/NO�ǂ�����I�񂾂�
	bool isFinish_;	//�v���[�g�̈�A�̓��삪�I��������ǂ���
	bool isSelect_;	//�I�����m�肳������

	void ChangeAnswer(void);	//OK/NO�̑I����ύX
	void SetIsFinish(bool flag);	//��A�̓��삪�I����������bool���Z�b�g
	void SetIsSelect(bool flag);	//�I���I����������bool���Z�b�g
	INPUT KeyboardContoroller(void);	// �L�[�{�[�h�̑���
	INPUT GamePadController(void);	// �Q�[���p�b�h�̑���

	

	//�V���O���g����
	Plate(void);
	void Destroy(void);

	static Plate* instance_;
};

