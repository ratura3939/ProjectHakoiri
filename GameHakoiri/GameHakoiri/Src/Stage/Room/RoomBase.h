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
	static constexpr int UNIT_STEALTH_SIZE_Y = 32;

	//�񋓌^
	enum class TYPE
	{
		NONE
		, OWN
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
	void DrawPazzle(void);	//�p�Y���V�[���ɂ����镔���̕`��
	void DrawStealth(void);	//�X�e���X�V�[���ɂ����镔���̕`��
	bool Release(void);	//���

	TYPE GetRoomType(void);	//�����̎�ނ�ԋp

	void SetPzlPos(Vector2F);	//�p�Y�����W�̐ݒ�
	void SetMapPos(Vector2F);	//�}�b�v�̍��W�ݒ�

	void SetIsCursor(bool);	//�J�[�\���t���O�̐ݒ�
	bool GetIsCursor(void);	//�J�[�\���t���O�̕ԋp
	

private:
	Vector2F pzlPos_;		//�p�Y���V�[���ɂ�������W
	Vector2F mapPos_;		//�X�e���X�V�[���ɂ�����map�̍��W�i�K�v���͂킩���j

	Vector2F pieceSize_;	//���ۂɕ`�悷���̃T�C�Y
	Vector2F mapSize_;		//���ۂɕ`�悷��}�b�v�̃T�C�Y

	bool isCursor_;			//�J�[�\���ɑI������Ă��邩�ǂ���
	

protected:

	TYPE type_;	//�����̎�ނ̎��ʎq

	Vector2F PazzleSize_;	//�p�Y���V�[���ɂ�����T�C�Y(�Z�~�Z���j
	int pieceImg_;		//��̉摜�i�[
	int frameImg_;		//�g�̉摜

	Vector2F StealthSize_;	//�X�e���X�V�[���ɂ�����}�b�v�̃T�C�Y(�Z�~�Z���j


	virtual void SetParam(void);	//�������Ƃ̃p�����[�^�ݒ�

	//�e�X�g�p
	int dbgColor_;
};