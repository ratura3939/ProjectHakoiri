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
		CHECK
	};

	Plate(void);
	~Plate(void);

	void Init(void);
	bool Update(TYPE type);
	void UpdateGo(void);
	bool UpdateStopSelect(void);
	bool UpdateStopCheck(void);
	void UpdateBack(void);
	void Draw(void);
	void Release(void);


private:

	STATE state_;

	int plateSelectImg_;
	int plateChangeImg_;
	int frameImg_;

	Vector2F platePos_;

	bool isFinishAnim_;
	bool isSelect_;
};

