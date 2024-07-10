#pragma once
#include"../Common/Vector2F.h"
class Plate
{
public:

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

	//�萔
	static constexpr int PLATE_SIZE = 512;

	Plate(void);
	~Plate(void);

	void Init(void);
	bool Update(TYPE type);
	void UpdateGo(void);
	bool UpdateStop(TYPE type);
	void UpdateBack(void);
	void Draw(TYPE type);
	void Release(void);


private:

	STATE state_;

	int plateImg_[static_cast<int>(TYPE::MAX)];
	int frameImg_;

	Vector2F platePos_;
	float speed_;

	bool isFinishAnim_;
	bool isSelect_;

	INPUT KeyboardContoroller(void);	// �L�[�{�[�h�̑���
	INPUT GamePadController(void);	// �Q�[���p�b�h�̑���
};

