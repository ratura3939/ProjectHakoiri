#pragma once
#include<vector>
#include<list>
#include<fstream>
#include<sstream>
#include<string>
#include<map>
#include<memory>
#include"../Common/Vector2.h"
#include"../Utility/Utility.h"
#include"../Scene/GameScene.h"
#include"../Manager/StageManager.h"
#include"Room/RoomBase.h"

//StageBase�͊e�X�e�[�W�̏��u����Ƃ����F��

class RoomBase;

class StageBase
{
public:

	enum class CURSOR
	{
		NORMAL,
		OBLONG,
		OBLONG_2,
		MAX
	};

	//�萔
	static constexpr int FRAME_INTERVAL = 15;	//�g�_�Ŋ��o
	static constexpr int STRING_TO_INT = 10;	//�z��w�萔(string)��int�ɖ߂��悤
	static constexpr int GOAL_AROUND = 3;		//�S�[���̎���̃}�X�̐�(�S�[����艺�Ƀ}�X�͂Ȃ��̂łR����)

	StageBase(std::vector<std::vector<int>>::iterator pzlIt, int pzlSizeX, int pzlSizeY,
		std::vector<std::vector<int>> map[], std::vector<std::vector<int>> obj[],
		int* roomImg,int* mapchip[]);	//�R���X�g���N�^
	virtual ~StageBase(void);			//�f�X�g���N�^
		
	virtual bool Init(void);					//������
	virtual void Update(GameScene::MODE mode);	//�X�V
	virtual void Draw(GameScene::MODE mode);	//�`��
	virtual bool Release(void);					//���

private:
	void DrawPazzle(void);	//�p�Y��
	void DrawCursor(void);	//�J�[�\��
	void DrawStealth(void);	//�X�e���X

	void LoadImgs(void);	//�摜�ǂݍ���


	/// <summary>
	/// �A�z�z��L�[����
	/// </summary>
	/// <param name="y"></param>
	/// <param name="x"></param>
	void CreateKey(const int y, const int x);

public:
	/// <summary>
	/// �z������Ă�����w�萔���擾
	/// </summary>
	/// <returns>�z��w�萔</returns>
	std::string GetKey(void)const;

#pragma region �p�Y���֘A
	//Set&Get*************************************************************************************************************************

	/// <summary>
	/// �J�[�\���ʒu�擾
	/// </summary>
	/// <returns>�J�[�\���ʒu(�z��w�萔)</returns>
	const Vector2 GetNowCursorPos(void);

	/// <summary>
	/// �J�[�\���ړ�
	/// </summary>
	/// <param name="move">�ړ���</param>
	/// <param name="dir">����</param>
	void SetCursor(const Vector2 move, const Utility::DIR dir);

	/// <summary>
	/// ��̈ړ�
	/// </summary>
	/// <param name="move">�ړ���</param>
	/// <param name="dir">����</param>
	void SetPiece(const Vector2 move, const Utility::DIR dir);

	/// <summary>
	/// �_�ł����邩�ǂ���
	/// </summary>
	/// <param name="flag">true=������/false=�����Ȃ�</param>
	void SetFrameFlash(const bool flag);

private:
	/// <summary>
	/// �J�[�\���̌`�ݒ�
	/// </summary>
	/// <param name="type">�����`�por�����`�p</param>
	void SetCursorType(const CURSOR type);
public:
	/// <summary>
	/// ���Z�b�g
	/// </summary>
	void ResetPazzl(void);

private:
	/// <summary>
	/// ��̈ړ�
	/// </summary>
	/// <param name="csr">�ړ���̃J�[�\���ʒu</param>
	/// <param name="bfr">�ړ��O�̔z��L�[</param>
	/// <param name="aft">�ړ���̔z��L�[</param>
	/// <returns></returns>
	const bool MovePiece(const Vector2 csr,
		const std::string bfr, const std::string aft);	//���ۂ̈ړ������@�ړ���̃J�[�\���A�ړ��O��Key�A�ړ����Key�ς���

public:
	/// <summary>
	/// �����ւ�(�����ʒu)
	/// </summary>
	/// <param name="nowKey">���݂̔z��ʒu(string)</param>
	void SwapPazzle(const std::string nowKey);

	/// <summary>
	/// ���͇@�}�X�ɋ���邩�i�S�[���ł��邩�̔���݂̂Ɏg�p�j
	/// </summary>
	/// <param name="nowPos">�S�[���ʒu</param>
	/// <returns>true=����/false=�Ȃ�</returns>
	const bool CheckAroundRoomAnything(const Vector2 nowPos);

	/// <summary>
	/// �S�[���\��
	/// </summary>
	/// <returns>true=�\/fale=�s�\</returns>
	const bool CanGoal(void);

	
private:
	/// <summary>
	/// �ړ��s�ȃu���b�N���ǂ���
	/// </summary>
	/// <param name="key">���ׂ����z��v�f��(string)</param>
	/// <returns>true=�s��/false=��</returns>
	const bool IsDontMoveBlock(const std::string key);
#pragma endregion
	
#pragma region �X�e���X�֘A
public:
	/// <summary>
	/// �X�e���X���̏�����
	/// </summary>
	/// <returns>true=����/false=���s</returns>
	bool InitStealth(void);

	/// <summary>
	/// �I�u�W�F�N�g�̕`��
	/// </summary>
	void DrawObject(void);

	/// <summary>
	/// ���ݕ`�撆�̃}�b�v�T�C�Y�擾
	/// </summary>
	/// <returns>�T�C�Y{float,float}</returns>
	Vector2F GetNowDrawMapSize(void);

	/// <summary>
	/// �I�u�W�F�N�g�����邩
	/// </summary>
	/// <param name="pMapPos">���茳�̍��W</param>
	/// <returns>true=����/false=�Ȃ�</returns>
	const bool IsMapObj(const Vector2 pMapPos);

	/// <summary>
	/// �����̈ړ����\��
	/// </summary>
	/// <returns>true=�\/false=�s�\</returns>
	const bool IsMoveRoom(void)const;

	/// <summary>
	/// �I�u�W�F�N�g�̎�ނ��擾
	/// </summary>
	/// <param name="pMapPos">���茳�̍��W</param>
	/// <returns>�I�u�W�F�N�g�̎��(int)</returns>
	const int GetObjNum(const Vector2 pMapPos);

	/// <summary>
	/// ���݂̏��𓾂�
	/// </summary>
	/// <param name="pMapPos">���茳�̍��W</param>
	/// <returns>���݂̃}�b�v���(�ʏ�or�ړ��}�X)</returns>
	const int GetMapNum(const Vector2 pMapPos);	

	/// <summary>
	/// ���ݕ`�悵�Ă���}�b�v�̎��
	/// </summary>
	/// <returns>�}�b�v�̎��</returns>
	const StageManager::MAPCHIP GetMapchipType(void);

	/// <summary>
	/// �����̌`���擾
	/// </summary>
	/// <returns>�����̌`(�����`or�����`)</returns>
	const RoomBase::ROOM_SHAPE GetNowShape(void);

	/// <summary>
	/// ���ɃI�u�W�F�N�g�����邩(�c���̏�Q���p)
	/// </summary>
	/// <param name="pMapPos">���茳�̍��W</param>
	/// <returns>true=����/false=�Ȃ�</returns>
	const bool CheckOneDownObject(const Vector2 pMapPos);

	/// <summary>
	/// �����̈ړ�
	/// </summary>
	/// <param name="after"></param>
	/// <param name="prvKey"></param>
	void MoveRoom(const Vector2 after, const std::string prvKey);	//�X�e���X

	/// <summary>
	/// �����̕ύX
	/// </summary>
	/// <param name="pMapPos">�v���C���[�ʒu</param>
	void ChangeRoom(const Vector2 pMapPos);

	/// <summary>
	/// �h�A�̈ʒu�擾
	/// </summary>
	/// <returns>�h�A�̈ʒu�擾(�h�A���ǂ̕����ɂ�������)</returns>
	const StageManager::DOOR GetDoorPos(void)const;			//�h�A�̈ړ��ꏊ�ԋp

	/// <summary>
	/// GetDoorPos�⑫�p
	/// </summary>
	/// <returns>�h�A�̈ʒu�擾(�h�A���ǂ̕����ɂ�������)</returns>
	const StageManager::DOOR_Y GetDoorPosSecond(void)const;

	/// <summary>
	/// �����`�̂Ƀ}�X��(��{��)���ǂ���
	/// </summary>
	/// <returns>true=��{��/false=�{��</returns>
	const bool IsSecondRoom(void)const;

	/// <summary>
	/// �S�[�����Ă��邩
	/// </summary>
	/// <returns>true=���Ă���/false=���Ă��Ȃ�</returns>
	const bool IsGoal(void)const;
#pragma endregion

#pragma region ���ʍ���
private:
	//�����`�̋�
	
	/// <summary>
	/// �����`�̔�{�̗p�̋�̃C���X�^���X�̐���
	/// </summary>
	/// <param name="r">�������镔��</param>
	/// <returns>��̕���</returns>
	std::unique_ptr<RoomBase> GetSecondRoomInstance(const RoomBase& r);	

	/// <summary>
	/// ����̒����`�v�f����ɂ��邩
	/// </summary>
	/// <param name="y">����Y��</param>
	/// <param name="x">����X��</param>
	/// <param name="r">���邩������Ȃ������̎��</param>
	/// <returns>true=����/false=�Ȃ�</returns>
	const bool CheckInstanceUp(int y, const int x, RoomBase& r);

	/// <summary>
	/// ����̒����`�v�f�����ɂ��邩
	/// </summary>
	/// <param name="y">����Y��</param>
	/// <param name="x">����X��</param>
	/// <param name="r">���邩������Ȃ������̎��</param>
	/// <returns>true=����/false=�Ȃ�</returns>
	const bool CheckInstanceDown(int y, const int x, RoomBase& r);

	/// <summary>
	/// ����̒����`�v�f�����ɂ��邩
	/// </summary>
	/// <param name="y">����Y��</param>
	/// <param name="x">����X��</param>
	/// <param name="r">���邩������Ȃ������̎��</param>
	/// <returns>true=����/false=�Ȃ�</returns>
	const bool CheckInstanceLeft(const int y, int x, RoomBase& r);

	/// <summary>
	/// ����̒����`�v�f���E�ɂ��邩
	/// </summary>
	/// <param name="y">����Y��</param>
	/// <param name="x">����X��</param>
	/// <param name="r">���邩������Ȃ������̎��</param>
	/// <returns>true=����/false=�Ȃ�</returns>
	const bool CheckInstanceRight(const int y, int x, RoomBase& r);

	//�����̌`*********************************************************************************************************************

	/// <summary>
	/// �����̌`�������`�������`��(�����̈ʒu����)
	/// </summary>
	/// <param name="key">�z��w��v�f��(string)</param>
	/// <returns>�����`or�����`</returns>
	const RoomBase::ROOM_SHAPE GetRoomShape(const std::string key);	//�����̌`������(������)

	/// <summary>
	/// �����̌`�������`�������`��(�����̎�ތ���)
	/// </summary>
	/// <param name="type">�`�𒲂ׂ��������̎��</param>
	/// <returns>�����`or�����`</returns>
	const RoomBase::ROOM_SHAPE GetRoomShape(const RoomBase::TYPE type)const;

	//�����ړ��̂��߂̃h�A�֘A**************************************************************************************************

	/// <summary>
	/// ���̔���ꏊ����ړ�������
	/// </summary>
	/// <param name="door">�h�A�����݂���ʒu(���E�̓��)</param>
	/// <returns>�ړ���</returns>
	const Vector2 MoveLeftOrRight(const StageManager::DOOR_X door)const;

	/// <summary>
	/// �ǂ��̃h�A�ɐG�ꂽ������
	/// </summary>
	/// <param name="pMapPos">�L�����N�^�[�ʒu</param>
	/// <returns>�G�ꂽ�h�A�ʒu</returns>
	const StageManager::DOOR SearchDoor(const Vector2 pMapPos);

	/// <summary>
	/// �����̂��߂ɔ͈͂𕪊�����
	/// </summary>
	/// <param name="pMapPos">�L�����N�^�[�ʒu</param>
	/// <param name="size">������̂��͈̔͂̑傫��</param>
	/// <param name="startPos">���������ʒu</param>
	/// <returns></returns>
	const StageManager::DOOR SplitRoom(const Vector2 pMapPos, const Vector2 size, const Vector2 startPos)const;	//�����̕���


	//�t���O�֌W********************************************************************************************************************************
	
	/// <summary>
	/// �ړ��\����ݒ肷��
	/// </summary>
	/// <param name="flag">true=�\/false=�s�\</param>
	void SetIsMoveRoom(const bool flag);

	/// <summary>
	/// �����`�̔�{�̂ł��邩������
	/// </summary>
	/// <param name="flag">true=��{��/false=�{��</param>
	void SetIsSecondRoom(const bool flag);

	void SetIsGoal(const bool flag);

#pragma endregion


private:
	std::map<std::string, std::unique_ptr<RoomBase>> roomMng_;			//�����̏��ꊇ�Ǘ�
	std::map<std::string, RoomBase::TYPE> resetRoom_;	//�����̃��Z�b�g�p
	std::map<std::string, bool> resetRoomClone_;		//�����̃��Z�b�g�p
	std::string roomKey_;								//�A�z�z��̃L�[
	Vector2 goalPos_;		//�S�[���̈ʒu�L�^

	
	std::map<std::string, Vector2F>pzlPos_;	//��̕`��ʒu�Ǘ�

	CURSOR type_;		//�J�[�\�������݉����w���Ă��邩��ێ�
	int frame_[static_cast<int>(CURSOR::MAX)];	//�J�[�\���t���[���̉摜��ێ�
	bool frameFlash_;							//�J�[�\����_�ł����邩�ǂ���
	int frameAnim_;								//�J�[�\���_�ŃJ�E���g�p

	bool isMoveRoom_;			//�����̈ړ����\��������
	StageManager::DOOR door_;	//�ړ��Ɏg�p����h�A�̈ʒu
	bool isSecondRoom_;			//�����`�̓�}�X�ڂɏo����
	bool isGoal_;				//�S�[���ɂ��ǂ蒅������

	//Get&Set

	

	//�����`�Q�R�}�ڂ��𔻒f���邽�߂ɕK�v�ȃC���X�^���X�𐶐�����
	RoomBase& CreateInstance4Confirmation(const RoomBase::TYPE type);

	
	const StageManager::DOOR_Y GetDoorSpare(void)const;			//�c���p�̒ǉ�����̃h�A���m��ԋp
	


protected:

	std::vector<std::vector<int>>::iterator pzlCsv_;
	Vector2 size_;
	virtual void SetParam(void);			//�������Ƃ̃p�����[�^�ݒ�

	std::vector<std::vector<int>>* mapCsv_;	//�}�b�v��Csv�f�[�^�̐擪�A�h���X�i�[
	std::vector<std::vector<int>>* objCsv_;	//�I�u�W�F�N�g��Csv�f�[�^�̐擪�A�h���X�i�[
	int* roomImg_;		//�p�Y���V�[���̋�摜�󂯎��
	int** mapchip_;		//�X�e���X�V�[���̃}�b�v�`�b�v�󂯎��

	StageManager::DOOR_Y doorSpare_;	//�h�A����c���p(�����`�Ɖ�����NONE)
};