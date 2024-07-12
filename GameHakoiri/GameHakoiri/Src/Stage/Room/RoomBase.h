#pragma once
#include<vector>
#include"../../Common/Vector2F.h"


class RoomBase
{
public:
	//�萔
	static constexpr int ROOM_TYPES = 7;	//�����̎�ސ�

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

	enum class ROOM_SHAPE
	{
		NOMAL,
		OBLONG,
		OBLONG_SIDE,
		MAX
	};

	RoomBase(int roomImg, int sizeX, int sizeY,
		std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
		int* mapchip);	//�R���X�g���N�^
	RoomBase(int roomImg);	//�R�s�[�R���X�g���N�^
	virtual ~RoomBase(void);	//�f�X�g���N�^

	bool Init(void);	//������
	virtual void DrawPazzle(void);	//�p�Y���V�[���ɂ����镔���̕`��
	void DrawStealth(void);	//�X�e���X�V�[���ɂ����镔���̕`��
	void DrawStealthObject(void);	//�X�e���X�V�[���ɂ����镔���̕`��(����̓v���C���[�Ƃ̕`�揇�̊֌W�ŃX�e���X�ŌĂԁj
	bool Release(void);	//���


	//�Z�b�^�[�E�Q�b�^�[
	void SetRoomType(TYPE type);	//�����̎�ނ�ݒ�
	TYPE GetRoomType(void)const;			//�����̎�ނ�ԋp

	void SetPzlPos(Vector2F pos);	//�p�Y���̍��W�ݒ�
	Vector2F GetPzlPos(void)const;		//�p�Y���̍��W�ԋp

	void SetMapPos(Vector2F pos);	//�}�b�v�̍��W�ݒ�
	Vector2F GetMapPos(void)const;		//�}�b�v�̍��W�ԋp

	void SetIsCursor(bool flag);	//�J�[�\���t���O�̐ݒ�
	bool GetIsCursor(void)const;			//�J�[�\���t���O�̕ԋp

	bool IsChange(void);			//IsChange�̃Q�b�^�[
	void SetIsChange(bool flag);	//IsChange�̃Z�b�^�[

	void SetIsDrawRoom(bool flag);	//������`�悷�邩�̃t���O���Z�b�g

	Vector2F GetRoomSize(void)const;//���݂̕����̃T�C�Y���擾

	int GetObj(Vector2 pos)const;	//�w�肳�ꂽ�ꏊ�̃I�u�W�F�N�gCSV�̒l��Ԃ�
	int GetMapchip(Vector2 pos)const;	//�w�肳�ꂽ�ꏊ�̃I�u�W�F�N�gCSV�̒l��Ԃ�
	bool IsOneDownObj(Vector2 pos)const;	//�w�肳�ꂽ�ꏊ�̃I�u�W�F�N�gCSV�̒l��Ԃ�

	bool IsClone(void)const;	//�����������ǂ���
	void SetIsClone(bool flag);	//��L�̃Z�b�g


private:
	Vector2F mapPos_;		//�X�e���X�V�[���ɂ�����map�̍��W�i�K�v���͂킩���j
	Vector2F mapMaxSize_;		//���ۂɕ`�悷��}�b�v�̃T�C�Y

	bool isChange_;	//�p�Y�����Z�b�g���ɂ��łɊm�肵�Ă���ꏊ�ł��邩�̔���
	bool isDrawStealth_;	//�X�e���X�V�[���ɂ����ĕ`�悷�邩�����߂�

	std::vector<std::vector<int>> map_;
	std::vector<std::vector<int>> obj_;
	int* mapchip_;
	

protected:

	TYPE type_;	//�����̎�ނ̎��ʎq


	Vector2F pzlPos_;		//�p�Y���V�[���ɂ�������W
	Vector2F pieceSize_;	//���ۂɕ`�悷���̃T�C�Y
	Vector2F pazzleSize_;	//�p�Y���V�[���ɂ�����T�C�Y(�Z�~�Z���j
	

	Vector2F mapSize_;	//�X�e���X�V�[���ɂ�����}�b�v�̃T�C�Y(�Z�~�Z���j

	bool isCursor_;			//�J�[�\���ɑI������Ă��邩�ǂ���

	int roomImg_;	//�����̉摜
	bool isDrawRoom_;	//�`�悷�邩���߂�i�����`�̓�}�X�ڗp�j
	bool isClone_;	//�{�̂���Ȃ����ǂ����𔻒f

	virtual void SetParam(void);	//�������Ƃ̃p�����[�^�ݒ�
};