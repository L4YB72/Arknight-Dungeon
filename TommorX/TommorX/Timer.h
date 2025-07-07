#pragma once
#include <functional>

class Timer {
private:
	int elapsed_time = 0;	//����ʱ��
	int start_time = 0;	//��ʼʱ��
	int end_time = 0;	//����ʱ��
	int waite_time = 0;	//�ȴ�ʱ��
	bool paused = 0;	//�Ƿ���ͣ
	bool shotted = 0;	//�Ƿ���ִ��
	bool one_shot = 0;	//�Ƿ񵥴�ִ��
	std::function<void()> callback; //�ص�����
public:
	Timer() = default;//Ĭ�Ϲ��캯��
	~Timer() = default; //Ĭ����������

	void restart() {
		elapsed_time = 0;
		shotted = false;
	}

	void set_wait_time(int time) {
		waite_time = time;
	}


	void set_one_shot(bool one_shot) {
		this->one_shot = one_shot;
	}

	void set_callback(std::function<void()> callback) {
		this->callback = callback;
	}
	
	void pause() {
		paused = true;
	}

	void resume() {
		paused = false;
	}

	void on_update(int delta) {
		if (paused) return; //�����ͣ����ִ���򲻸���
		   
		elapsed_time += delta; //��������ʱ��
		if (elapsed_time >= waite_time) { //�������ʱ�䳬���ȴ�ʱ��
			if (!one_shot || (one_shot && !shotted) && callback) {
				callback();
			}
			shotted = true;
			elapsed_time = 0;
		}
	}
	
};
