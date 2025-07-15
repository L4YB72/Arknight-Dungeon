#include "Vector2.h"
#include "Timer.h"



class Camera {
private:
	Vector2 position; //���λ��
	Timer timer_shake;//������ʱ��
	bool is_shake = false;//�Ƿ񶶶�
	float shaking_strenth = 0;//����ǿ��

public:
	Camera() {
		position = Vector2(0, 0); //��ʼ�����λ��
		timer_shake.set_one_shot(true); //����Ϊ����ִ��
		timer_shake.set_callback([&]() {
			is_shake = false; //��������
			reset(); //�������λ��
			});
	}
	~Camera() = default;//Ĭ����������

	const Vector2& get_poisition() const {//��ȡ���λ��
		return position;
	}

	void set_position(const Vector2& new_position) {//�������λ��
		position = new_position;
	}

	void reset() {//�������λ��
		position = Vector2(0, 0);
	}

	void on_update(int delta) {//�������λ��
		timer_shake.on_update(delta); //���¶�����ʱ��

		if (is_shake) {
			//������ڶ��������ƫ�����λ��
			position.x += (rand() % 100 - 50) * shaking_strenth / 100.0f;
			position.y += (rand() % 100 - 50) * shaking_strenth / 100.0f;
		}
	}

	void shake(float strength, int duration) {//�������
		if (is_shake) return; //������ڶ����򲻴���
		is_shake = true; //����Ϊ���ڶ���
		shaking_strenth = strength; //���ö���ǿ��
		timer_shake.set_wait_time(duration); //���õȴ�ʱ��
		timer_shake.restart(); //������ʱ��
	}
};