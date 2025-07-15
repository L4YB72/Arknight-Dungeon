#pragma once
#include <iostream>
#include "Camera.h"
#include "graphics.h"
#include "Vector2.h"
#include "Animation.h"
#include "immmma.h"
#include "Map.h"
#include <functional>
#include "DamageManager.h"
#include "Timer.h"

class Enemy {
private:
	
public:
	
	Enemy(int level=0); // Ĭ�Ϲ��캯��;
	~Enemy(); // Ĭ����������

	virtual void on_load(int x,int y); // ���ص�����Դ

	virtual void on_update(int delta);
 // ���µ���״̬

	virtual void on_render(const Camera& camera);
 // ��Ⱦ����

	virtual void on_unload(); // ж�ص�����Դ

	virtual void on_event(const ExMessage& msg); // �����¼�
	virtual void move(Map* &map)=0; // �ƶ�����
	void move_to_block(int delta);

protected:
	Vector2 current_block; // ����λ��
	Vector2 current_position; // ��������λ��
	Vector2 delta_position;

	Animation animation_idle_right; // �Ҳ��������
	Animation animation_idle_left; // ����������
	Animation animation_move_right; // �Ҳ��ƶ�����
	Animation animation_move_left; // ����ƶ�����
	Animation animation_attack_right;
	Animation animation_attack_left;


	Animation* current_animation = nullptr; // ��ǰ����ָ��
	



	//�߸���ģ��
	Vector2 target_block; // Ŀ�����λ��
	Vector2 target_position; // Ŀ������λ��
	const int block_size = block_pixel; // ���Ӵ�С
	const double block_velocity = 0.5; // �ƶ������ٶ�
	Timer move_timer;
	bool can_move;
	bool is_facing_right = true;//�Ƿ������Ҳ�
	

	//ս��
friend class DamageManager; // ������Ԫ��DamageManager
protected:
	bool have_attacked = false; // �Ƿ����ڹ���
	bool ready_to_attack = false;
	bool remote_ready_to_attack =false;
	virtual void attact() = 0;// ��������
	int attack_power = 100; // ������
	int Hp = 100;// ����ֵ
	std::function<void()> on_dead_callback; // �����ص�����


	
public:
	void set_on_dead_callback(std::function<void()> callback);

	

};