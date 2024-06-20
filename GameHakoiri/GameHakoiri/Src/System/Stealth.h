//#pragma once
#include<vector>
#include<map>
#include"../Object/EnemyBase.h"
#include"../Common/Vector2F.h"

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

	static constexpr Position NOMAL_POS_1={0.0f,0.0f};

	Stealth(void);	//�R���X�g���N�^
	~Stealth(void);	//�f�X�g���N�^

	bool Init(void);	//������
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool Release(void);	//���

private:
	Player* player_;
	Position prevPlayerPos_;

	EnemyBase* enemyMng_[OBLONG_ENEMY_NUM*static_cast<int>(EnemyBase::TYPE::MAX)];	//�G�̍ő吔����ނ�ێ�
	std::vector<EnemyBase*> useEnemy_;		//�g�p����G��ێ�����
	std::map<std::string, std::vector<EnemyBase::TYPE>> memorizeType_;	//�������Ƃɂ����鐶�������G��ێ�
	std::map<std::string, std::vector<Position>> memorizePos_;			//�������Ƃɂ����鐶�������G��ێ�
	Position initPos_[static_cast<int>(RoomBase::ROOM_SHAPE::MAX)][OBLONG_ENEMY_NUM];

	void Collision(void);
	void CollisionObstacle(void);
	void CollisionTrough(Vector2 pCol);
	void CollisionEvent(Vector2 pCol);
	void ChangeRoom(void);

	void DrawDebug(void);
	void EnemyInit(void);
	void CreateEnemy(void);
	void SetEnemyPos(void);
	void SetEnemy(void);
	void MemorizeEnemy(std::string key);
};