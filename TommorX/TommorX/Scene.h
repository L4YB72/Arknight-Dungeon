#pragma once
#include "Camera.h"
class Scene {
	//private
	
public:
	Scene() = default; //Ĭ�Ϲ��캯��
	~Scene() = default; //Ĭ����������	

	virtual void on_load(){}; //���س���
	virtual void on_update(int delta){}; //���³���
	virtual void on_render(const Camera& camera){}; //��Ⱦ����
	virtual void on_unload(){}; //ж�س���
	virtual void on_event(const ExMessage& msg) = 0; //�����¼�
 };