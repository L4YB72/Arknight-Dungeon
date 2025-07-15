#pragma once
#include "Enemy.h"
#include <iostream>
#include "Camera.h"
#include "Vector2.h"
#include "graphics.h"
#include "Animation.h"

class B2 : public Enemy {
private:
    // 修改为 4 个方向：上、下、左、右
    const Vector2 move_direction[4] = { {0,1}, {0,-1}, {1,0}, {-1,0} };
public:
    B2(int level = 0);
    ~B2(); // 默认析构函数

    void on_update(int delta);
    void on_render(const Camera& camera);

    void move(Map*& map) override;
    void attact() override; // 攻击方法
    void Get_P_Block();
};