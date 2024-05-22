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
		, WALL
		, GOAL
		, MAX
	};

	RoomBase(int roomImg);	//�R���X�g���N�^
	virtual ~RoomBase(void);	//�f�X�g���N�^

	bool Init(void);	//������
	void Draw(void);
	virtual void DrawPazzle(void);	//�p�Y���V�[���ɂ����镔���̕`��
	void DrawStealth(void);	//�X�e���X�V�[���ɂ����镔���̕`��
	bool Release(void);	//���

	void SetRoomType(TYPE type);	//�����̎�ނ�ݒ�
	TYPE GetRoomType(void);	//�����̎�ނ�ԋp

	void SetPzlPos(Vector2F pos);	//�p�Y���̍��W�ݒ�
	Vector2F GetPzlPos(void);	//�p�Y���̍��W�ԋp

	void SetMapPos(Vector2F pos);	//�}�b�v�̍��W�ݒ�
	Vector2F GetMapPos(void);	//�}�b�v�̍��W�ԋp

	void SetIsCursor(bool flag);	//�J�[�\���t���O�̐ݒ�
	bool GetIsCursor(void);	//�J�[�\���t���O�̕ԋp

	bool IsChange(void);	//IsChange�̃Q�b�^�[
	void SetIsChange(bool flag);	//IsChange�̃Z�b�^�[

	void SetIsDrawRoom(bool flag);


	//�������������
	void SetColor(int col);
	int GetColor(void);
	

private:
	Vector2F mapPos_;		//�X�e���X�V�[���ɂ�����map�̍��W�i�K�v���͂킩���j
	Vector2F mapSize_;		//���ۂɕ`�悷��}�b�v�̃T�C�Y

	bool IsChange_;	//�p�Y�����Z�b�g���ɂ��łɊm�肵�Ă���ꏊ�ł��邩�̔���
	

protected:

	TYPE type_;	//�����̎�ނ̎��ʎq


	Vector2F pzlPos_;		//�p�Y���V�[���ɂ�������W
	Vector2F pieceSize_;	//���ۂɕ`�悷���̃T�C�Y

	Vector2F PazzleSize_;	//�p�Y���V�[���ɂ�����T�C�Y(�Z�~�Z���j
	int pieceImg_;		//��̉摜�i�[

	Vector2F StealthSize_;	//�X�e���X�V�[���ɂ�����}�b�v�̃T�C�Y(�Z�~�Z���j

	bool isCursor_;			//�J�[�\���ɑI������Ă��邩�ǂ���

	int roomImg_;	//�����̉摜
	int isDrawRoom_;	//�`�悷�邩���߂�i�����`�̓�}�X�ڗp�j

	virtual void SetParam(void);	//�������Ƃ̃p�����[�^�ݒ�
};