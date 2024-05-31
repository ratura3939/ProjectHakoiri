//#pragma once

class Player;

class Stealth
{
public:
	Stealth(void);	//�R���X�g���N�^
	~Stealth(void);	//�f�X�g���N�^

	bool Init(void);	//������
	void Update(void);	//�X�V
	void Draw(void);	//�`��
	bool Release(void);	//���

private:
	Player* player_;

	void Collision(void);
	void ChangeRoom(void);

	void DrawDebug(void);
};