#pragma once
#include<vector>
#include"../../Common/Vector2F.h"


class RoomBase
{
public:
	//�萔
	static constexpr int ROOM_TYPES = 7;	//�����̎�ސ�

	//�񋓌^
	
	/// <summary>
	/// �����̎��
	/// </summary>
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

	/// <summary>
	/// �����̌`
	/// </summary>
	enum class ROOM_SHAPE
	{
		NOMAL,
		OBLONG,
		OBLONG_SIDE,
		MAX
	};

	RoomBase(int roomImg, int sizeX, int sizeY,
		std::vector<std::vector<int>> map, std::vector<std::vector<int>> obj,
		int* mapchip);			//�R���X�g���N�^
	RoomBase(int roomImg);		//�R�s�[�R���X�g���N�^
	virtual ~RoomBase(void);	//�f�X�g���N�^

	bool Init(void);	//������
	//�����̕`��
	virtual void DrawPazzle(void);	//�p�Y��
	void DrawStealth(void);			//�X�e���X
	void DrawStealthObject(void);	//��Q��

	bool Release(void);				//���


	//�Z�b�^�[�E�Q�b�^�[

	/// <summary>
	/// ��ސݒ�
	/// </summary>
	/// <param name="type">���</param>
	void SetRoomType(const TYPE type);

	/// <summary>
	/// ��ގ擾
	/// </summary>
	/// <returns>���</returns>
	const TYPE GetRoomType(void)const;	//�����̎�ނ�ԋp

	/// <summary>
	/// ���W�ݒ�(�p�Y����)
	/// </summary>
	/// <param name="pos">���W</param>
	void SetPzlPos(const Vector2F pos);

	/// <summary>
	/// ���W�擾
	/// </summary>
	/// <returns>���</returns>
	const Vector2F GetPzlPos(void)const;

	/// <summary>
	/// �J�[�\���t���O�ݒ�
	/// </summary>
	/// <param name="flag">true=�J�[�\�����/false=��J�[�\�����</param>
	void SetIsCursor(const bool flag);

	/// <summary>
	/// �J�[�\���t���O�擾
	/// </summary>
	/// <returns>true=�J�[�\�����/false=��J�[�\�����</returns>
	const bool GetIsCursor(void)const;

	/// <summary>
	/// �ύX�����ɂ��ꂽ���̐ݒ�
	/// </summary>
	/// <param name="flag">true=����/false=���Ă��Ȃ�</param>
	void SetIsChange(const bool flag);

	/// <summary>
	/// �ύX�����ɂ��ꂽ���̎擾
	/// </summary>
	/// <returns>true=����Ă���/false=����Ă��Ȃ�</returns>
	const bool IsChange(void)const;
	
	/// <summary>
	/// ������`�悷�邩�̃t���O
	/// </summary>
	/// <param name="flag">true=����/false=���Ȃ�</param>
	void SetIsDrawRoom(const bool flag);

	/// <summary>
	/// ���݂̕����̃T�C�Y�擾
	/// </summary>
	/// <returns>�T�C�Y</returns>
	Vector2F GetRoomSize(void)const;

	/// <summary>
	/// �w��ꏊ�̃I�u�W�F�N�g��Ԃ�
	/// </summary>
	/// <param name="pos">�w��ꏊ</param>
	/// <returns>�w��̃I�u�W�F�N�gCSV�l</returns>
	const int GetObj(const Vector2 pos)const;

	/// <summary>
	/// �w��ꏊ�̃}�b�v�`�b�v��Ԃ�
	/// </summary>
	/// <param name="pos">�w��ꏊ</param>
	/// <returns>�w��̃}�b�vCSV�l</returns>
	const int GetMapchip(const Vector2 pos)const;

	/// <summary>
	/// �w��ꏊ�̈���̃I�u�W�F�N�g��Ԃ�
	/// </summary>
	/// <param name="pos">�w��ꏊ</param>
	/// <returns>�w��̈���̃I�u�W�F�N�gCSV�l</returns>
	const bool IsOneDownObj(const Vector2 pos)const;	//�w�肳�ꂽ�ꏊ�̃I�u�W�F�N�gCSV�̒l��Ԃ�

	/// <summary>
	/// �_�~�[�t���O�擾
	/// </summary>
	/// <returns>true=�_�~�[�ł͂Ȃ�/false=�_�~�[�ł���</returns>
	const bool IsClone(void)const;

	/// <summary>
	/// �_�~�[�t���O�ݒ�
	/// </summary>
	/// <param name="flag">true=�_�~�[/false=��_�~�[</param>
	void SetIsClone(const bool flag);


private:
	Vector2F mapMaxSize_;	//���ۂɕ`�悷��}�b�v�̃T�C�Y

	bool isChange_;			//�p�Y�����Z�b�g���ɂ��łɊm�肵�Ă���ꏊ�ł��邩�̔���
	bool isDrawStealth_;	//�X�e���X�V�[���ɂ����ĕ`�悷�邩�����߂�

	std::vector<std::vector<int>> map_;		//�}�b�v�f�[�^
	std::vector<std::vector<int>> obj_;		//�I�u�W�F�N�g�f�[�^
	int* mapchip_;	//�}�b�v�C���X�g
	

protected:

	TYPE type_;				//�����̎�ނ̎��ʎq


	Vector2F pzlPos_;		//�p�Y���V�[���ɂ�������W
	Vector2F pieceSize_;	//���ۂɕ`�悷���̃T�C�Y
	Vector2F pazzleSize_;	//�p�Y���V�[���ɂ�����T�C�Y(�Z�~�Z���j
	

	Vector2F mapSize_;		//�X�e���X�V�[���ɂ�����}�b�v�̃T�C�Y(�Z�~�Z���j

	bool isCursor_;			//�J�[�\���ɑI������Ă��邩�ǂ���

	int roomImg_;			//�����̉摜
	bool isDrawRoom_;		//�`�悷�邩���߂�i�����`�̓�}�X�ڗp�j
	bool isClone_;			//�{�̂���Ȃ����ǂ����𔻒f

	virtual void SetParam(void);	//�������Ƃ̃p�����[�^�ݒ�
};