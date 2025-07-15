#pragma once
#include "Enemy.h"
#include <iostream>
#include "Camera.h"
#include "Vector2.h"
#include "graphics.h"
#include "Animation.h"

class B2 : public Enemy {
private:
    // �޸�Ϊ 4 �������ϡ��¡�����
    const Vector2 move_direction[4] = { {0,1}, {0,-1}, {1,0}, {-1,0} };
public:
    B2(int level = 0);
    ~B2(); // Ĭ����������

    void on_update(int delta);
    void on_render(const Camera& camera);

    void move(Map*& map) override;
    void attact() override; // ��������
    void Get_P_Block();
};