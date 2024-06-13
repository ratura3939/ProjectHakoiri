//#pragma once

class Player;

class Stealth
{
public:

	//�萔
	static constexpr int DOOR_DISTANCE = 32 * 15;	//�h�A�̈ʒu�͒[����}�b�v�`�b�v15�}�X���̈ʒu�ɂ���
	static constexpr int INIT_ROOM_POS = 32 * 4;	//�����ړ���̏����ʒu
	static constexpr int INIT_ROOM_POS_SIDE = 32 * 2;	//�����ړ���̏����ʒu

	Stealth(void);	//�R���X�g���N�^
	~Stealth(void);	//�f�X�g���N�^

	bool Init(void);	//������
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool Release(void);	//���

private:
	Player* player_;
	Vector2F prevPlayerPos_;

	void Collision(void);
	void CollisionObstacle(void);
	void CollisionTrough(Vector2 pCol);
	void CollisionEvent(Vector2 pCol);
	void ChangeRoom(void);

	void DrawDebug(void);
};