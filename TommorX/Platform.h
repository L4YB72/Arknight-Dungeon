#pragma once
#include "Camera.h"
#include <graphics.h>
#include "Camera.h"

extern bool is_debug; // �Ƿ���debugģʽ


class Platform {
private:
public:
	Platform() = default; // Ĭ�Ϲ��캯��
	~Platform() = default; // Ĭ����������

	struct CollisionShape//��ײ����
	{
		float y;//y����
		float left; // ��߽�
		float right; // �ұ߽�
	};

	CollisionShape collision_shape; // ��ײ����
	IMAGE* img = nullptr; // ƽ̨ͼƬ
	POINT render_posiiton = {0}; // ƽ̨λ��


	void on_render(const Camera& camera) const {
		if (is_debug) {
			setlinecolor(RED);
			line(camera,(int)collision_shape.left,(int)collision_shape.y,
				(int)collision_shape.right,(int)collision_shape.y);
		}
	}

};