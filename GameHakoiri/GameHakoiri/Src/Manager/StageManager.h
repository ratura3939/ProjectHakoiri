#pragma once
#include<memory>
#include"../Utility/Utility.h"
#include"../Scene/GameScene.h"
#include"../Stage/Room/RoomBase.h"

class GameScene;
class StageBase;

class StageManager
{
public:

	//�񋓌^
	//��������X�e�[�W
	enum class STAGENUM
	{
		TUTORIAL
		, FIRST
		, SECOND
		, THIRD
		, MAX
	};

	//�}�b�v�Ɏg�p����}�b�v�`�b�v�̎��
	enum class MAPCHIP
	{
		BATH,
		EXTERIA,
		INTERIA,
		MAX
	};

	//�I�u�W�F�N�g�̎��
	enum class OBJECT
	{
		OBSTACLE,
		THROUGH,
		EVENT,
		MAX
	};

	//���̈ʒu
	enum class DOOR_X
	{
		NONE,
		LEFT,
		RIGHT
	};

	enum class DOOR_Y
	{
		NONE,
		TOP,
		MIDDLE,
		BOTTOM
	};

	struct DOOR
	{
		DOOR_X x;
		DOOR_Y y;
	};

	//�萔
	//�e�X�e�[�W�ɂ�����p�Y���̃T�C�Y
	static constexpr int TUTORIAL_PAZZLE_SIZE_X = 6;
	static constexpr int TUTORIAL_PAZZLE_SIZE_Y = 6;
	static constexpr int FIRST_PAZZLE_SIZE_X = 6;
	static constexpr int FIRST_PAZZLE_SIZE_Y = 6;
	static constexpr int SECOND_PAZZLE_SIZE_X = 6;
	static constexpr int SECOND_PAZZLE_SIZE_Y = 6;
	static constexpr int THIRD_PAZZLE_SIZE_X = 6;
	static constexpr int THIRD_PAZZLE_SIZE_Y = 6;
	//�����̎�ޕʂ̃p�Y���ɂ�����傫��
	static constexpr int NOMAL_PAZZLE_X = 1;
	static constexpr int NOMAL_PAZZLE_Y = 1;
	static constexpr int OBLONG_PAZZLE_X = 1;
	static constexpr int OBLONG_PAZZLE_Y = 2;
	static constexpr int OBLONG_2_PAZZLE_X = 2;
	static constexpr int OBLONG_2_PAZZLE_Y = 1;
	//�����̎�ޕʂ̃}�b�v�ɂ�����傫��
	static constexpr int NOMAL_MAP_X = 30;
	static constexpr int NOMAL_MAP_Y = 30;
	static constexpr int OBLONG_MAP_X = 30;
	static constexpr int OBLONG_MAP_Y = 60;
	static constexpr int OBLONG_2_MAP_X = 60;
	static constexpr int OBLONG_2_MAP_Y = 30;

	//�e���[�h�ɂ������{�T�C�Y
	static constexpr int UNIT_PAZZLE_SIZE_X = 64;
	static constexpr int UNIT_PAZZLE_SIZE_Y = 64;
	static constexpr int UNIT_STEALTH_SIZE_X = 32;
	static constexpr int UNIT_STEALTH_SIZE_Y = 32;

	//���̈ʒu�����̍ۂ̕����̕�����
	static constexpr int SPLIT_ROOM_X = 2;
	static constexpr int SPLIT_ROOM_Y = 3;


	bool Init(STAGENUM);				//������
	void Update(GameScene::MODE mode);	//�X�V
	void Draw(GameScene::MODE mode);	//�`��
	void DrawObject(void);				//�`��
	bool Release(void);					//���

	void MoveCursor(Utility::DIR dir);	//�J�[�\���̈ړ�
	void MovePiece(Utility::DIR dir);	//��̈ړ�
	void PazzleReset(void);		//�Ֆʃ��Z�b�g
	void SetFlash(bool flag);	//�g�_��
	
	bool CanGoal(void);	//�S�[���\���𔻒f
	void ChangeModeInit(void);	//�V�[���؂�ւ����̏�����
	void ChangeMap(Vector2 pMapPos);	//�����̐؂�ւ�
	Vector2F GetMapMaxSize(void)const;	//�}�b�v�̍ő�T�C�Y���擾

	bool IsCollisionObject(const Vector2 pMapPos)const;	//���W�������̃I�u�W�F�N�g�ƏՓ˂��Ă��邩
	bool IsCollisionWall(const Vector2 pMapPos)const;	//���W���ǂƏՓ˂��Ă��邩
	Vector2 GetVector2MapPos(const Vector2 pPos)const;	//���W���}�b�v�̔z��ɕϊ�
	Vector2 GetMapPos2Vector(const Vector2 pPos)const;	//�}�b�v�̔z������W�ɕϊ�
	OBJECT GetObjectType(const Vector2 pMapPos)const;	//�I�u�W�F�N�g�̃^�C�v��ԋp
	bool IsBottomObject(const Vector2 pMapPos)const;	//�I�u�W�F�N�g�̃^�C�v��ԋp
	bool IsMove(void);				//�}�b�v�ړ����������ǂ�����ԋp
	RoomBase::ROOM_SHAPE GetShape(void);//�����̌`���擾�i�����`�������`���j
	std::string GetKey(void)const;	//roomKey�̎擾
	DOOR GetDoor(void)const;		//�ړ��Ɏg�p�����h�A�̈ʒu��ԋp
	DOOR_Y GetDoorSecond(void)const;//��L�̕������c���������ꍇ�̕⑫��
	bool IsSecondEvidence(void)const;//�����`�̖{�̂���Ȃ�����ʂ�����
	bool IsClear(void)const;		//�N���A������

	//�V���O���g����
	static bool CreateInstance(STAGENUM);	//�O������ÓI�C���X�^���X�𐶐�
	static StageManager& GetInstance(void);	//�C���X�^���X�̎擾
	
private:

	//�C���X�^���X
	StageBase* stage_;

	STAGENUM num_;	//��������X�e�[�W�ԍ���ێ�

	Vector2 dir_[static_cast<int>(Utility::DIR::MAX)];

	//IMG
	int roomImg_[static_cast<int>(RoomBase::TYPE::MAX)];
	
	//Csv
	//�p�Y���X�e�[�W�ێ�
	std::vector<std::vector<int>> stageCsv_[static_cast<int>(STAGENUM::MAX)];

	//�}�b�v��Csv�f�[�^�̐擪�A�h���X�i�[
	std::vector<std::vector<int>> mapCsv_[static_cast<int>(RoomBase::TYPE::MAX)];	
	//�I�u�W�F�N�g��Csv�f�[�^�̐擪�A�h���X�i�[
	std::vector<std::vector<int>> objCsv_[static_cast<int>(RoomBase::TYPE::MAX)];	
	//�}�b�v�摜���擾
	int* mapTile_[static_cast<int>(MAPCHIP::MAX)];	
	//�}�b�v�`�b�v���Ƃ̓����蔻��CSV�i�[�p
	std::vector<std::vector<int>>mapchipObj_[static_cast<int>(MAPCHIP::MAX)][static_cast<int>(OBJECT::MAX)];	

	void LoadImg(void);
	void LoadCsv(void);



	//�V���O���g����
	StageManager(void);	//�R���X�g���N�^
	StageManager(const StageManager&);	//�R�s�[�R���X�g���N�^
	void Destroy(void);	//�f�X�g���N�^

	static  StageManager* instance_;	//���̂��m��
};