#pragma once
#include"../../Common/Vector2F.h"

class RoomBase
{
public:
	//�萔
	static constexpr int ROOM_TYPES = 7;	//�����̎�ސ�
	static constexpr int UNIT_PAZZLE_SIZE_X = 64;
	static constexpr int UNIT_PAZZLE_SIZE_Y = 64;
	static constexpr int UNIT_STEALTH_SIZE_X = 32;
	static constexpr int UNIT_STEALTH_SIZE_X = 32;

	//�񋓌^
	enum class TYPE
	{
		OWN
		, WASITU
		, LIVING
		, BATH
		, STORAGE
		, KITCHEN
		, ENTRANCE
		, MAX
	};

	RoomBase(void);	//�R���X�g���N�^
	~RoomBase(void);	//�f�X�g���N�^

	bool Init(void);	//������
	bool Release(void);	//���

	virtual void SetParam(void);	//�������Ƃ̃p�����[�^�ݒ�

private:


protected:
	Vector2F PazzleSize_;
	int pieceImg_;

	Vector2F StealthSize_;
};