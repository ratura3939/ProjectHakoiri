//#pragma once
#include<vector>
#include<map>
#include"../Object/EnemyBase.h"
#include"../Object/CharacterBase.h"
#include"../Common/Vector2F.h"

class CharacterBase;
class Player;
class EnemyBase;

class Stealth
{
public:

	//�萔
	static constexpr int DOOR_DISTANCE = 32 * 15;	//�h�A�̈ʒu�͒[����}�b�v�`�b�v15�}�X���̈ʒu�ɂ���
	static constexpr int INIT_ROOM_POS = 32 * 4;	//�����ړ���̏����ʒu
	static constexpr int INIT_ROOM_POS_SIDE = 32 * 2;	//�����ړ���̏����ʒu
	static constexpr int OBLONG_ENEMY_NUM = 3;	//�����`�̕����̓G�̐�
	static constexpr int NOMAL_ENEMY_NUM = 2;	//�����`�̕����̓G�̐�

	//�G�̏����ʒu

	static constexpr float NX1 = 672.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float NY1 = 224.0f + CharacterBase::CHARACTER_HALF_Y;
	static constexpr float NX2 = 480.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float NY2 = 608.0f + CharacterBase::CHARACTER_HALF_Y;

	static constexpr float OBX1= 480.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OBY1= 480.0f + CharacterBase::CHARACTER_HALF_Y;
	static constexpr float OBX2= 160.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OBY2= 1056.0f + CharacterBase::CHARACTER_HALF_Y;
	static constexpr float OBX3= 608.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OBY3= 1568.0f + CharacterBase::CHARACTER_HALF_Y;

	static constexpr float OB2X1 = 960.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OB2Y1 = 736.0f + CharacterBase::CHARACTER_HALF_Y;
	static constexpr float OB2X2 = 448.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OB2Y2 = 480.0f + CharacterBase::CHARACTER_HALF_Y;
	static constexpr float OB2X3 = 1376.0f + CharacterBase::CHARACTER_HALF_X;
	static constexpr float OB2Y3 = 384.0f + CharacterBase::CHARACTER_HALF_Y;

	/*static constexpr Vector2F NOMAL_POS_1=
	{672.0f + CharacterBase::CHARACTER_HALF_X,224.0f + CharacterBase::CHARACTER_HALF_Y };
	static constexpr Vector2F NOMAL_POS_2=
	{480.0f + CharacterBase::CHARACTER_HALF_X,608.0f + CharacterBase::CHARACTER_HALF_Y };

	static constexpr Vector2F OBLONG_POS_1=
	{480.0f + CharacterBase::CHARACTER_HALF_X,480.0f + CharacterBase::CHARACTER_HALF_Y };
	static constexpr Vector2F OBLONG_POS_2=
	{160.0f + CharacterBase::CHARACTER_HALF_X,1056.0f + CharacterBase::CHARACTER_HALF_Y };
	static constexpr Vector2F OBLONG_POS_3=
	{608.0f + CharacterBase::CHARACTER_HALF_X,1568.0f + CharacterBase::CHARACTER_HALF_Y };

	static constexpr Vector2F OBLONG_2_POS_1 =
	{ 960.0f + CharacterBase::CHARACTER_HALF_X,736.0f + CharacterBase::CHARACTER_HALF_Y };
	static constexpr Vector2F OBLONG_2_POS_2 =
	{ 448.0f + CharacterBase::CHARACTER_HALF_X,480.0f + CharacterBase::CHARACTER_HALF_Y };
	static constexpr Vector2F OBLONG_2_POS_3 =
	{ 1376.0f + CharacterBase::CHARACTER_HALF_X,384.0f + CharacterBase::CHARACTER_HALF_Y };*/

	Stealth(void);	//�R���X�g���N�^
	~Stealth(void);	//�f�X�g���N�^

	bool Init(void);	//������
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool Release(void);	//���

private:
	//�C���X�^���X
	Player* player_;

	//����
	bool isEnemyMove_;	//�G���Փ˂��ړ��ł��Ă��Ȃ���

	EnemyBase* enemyMng_[OBLONG_ENEMY_NUM*static_cast<int>(EnemyBase::TYPE::MAX)];	//�G�̍ő吔����ނ�ێ�
	std::vector<EnemyBase*> useEnemy_;		//�g�p����G��ێ�����
	std::map<std::string, std::vector<EnemyBase::TYPE>> memorizeType_;	//�������Ƃɂ����鐶�������G��ێ�
	std::map<std::string, std::vector<Vector2F>> memorizePos_;			//�������Ƃɂ����鐶�������G��ێ�
	Vector2F initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::MAX)][OBLONG_ENEMY_NUM];

	void Collision(void);		//�����蔻�葍��
	void CollisionMapchip(CharacterBase* character ,bool isPlayer);	//�}�b�v�`�b�v�Ƃ̓����蔻��
	void CollisionObstacle(CharacterBase* character);			//�ʂ蔲���s�ȃ}�b�v�`�b�v
	void CollisionTrough(Vector2 pCol, CharacterBase* character);		//���s��������}�b�v�`�b�v
	void CollisionEvent(Vector2 pCol);		//�C�x���g������}�b�v�`�b�v��
	void ChangeRoom(void);					//�����̕ύX

	void DrawDebug(void);
	void EnemyInit(void);		//�G�̏�����
	void CreateEnemy(void);		//�G�̏�������
	void InitEnemyPos(const RoomBase::ROOM_SHAPE type);	//�G�̏����ʒu�ݒ�
	void SetEnemy(void);		//�G�̔z�u
	void SearchSetEnemy(std::string key, int num);	//�w�肵�������ɓG�̐����L�^�����邩�𔻒�
	void MemorizeEnemy(std::string key);	//�G�̋L�^���Ăяo��

	void SetIsEnemyMove(bool flag);
	bool IsEnemyMove(void)const;
};