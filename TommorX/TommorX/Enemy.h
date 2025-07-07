#pragma once
#include "Camera.h"
#include "graphics.h"

class Enemy {
private:
public:
		Enemy() = default; // Ĭ�Ϲ��캯��
	~Enemy() = default; // Ĭ����������
	virtual void on_load() {} // ���ص�����Դ
	virtual void on_update(int delta) {} // ���µ���״̬
	virtual void on_render(const Camera& camera) {} // ��Ⱦ����
	virtual void on_unload() {} // ж�ص�����Դ
	virtual void on_event(const ExMessage& msg) = 0; // �����¼�
};