#pragma once
#include "Vector2.h"
#include <functional>

enum class SignalLayer {
	None = 0,
	Player,
	Enermy,
	Item
};

class Signal {

	friend class SignalManager;

private:
	Vector2 target_block;
	bool enable = true;
	std::function<void()> on_signal;
	SignalLayer layer_src = SignalLayer::None;
	SignalLayer layer_dst = SignalLayer::None;

private:
	Signal() = default;
	~Signal() = default;

public:
	void set_enable(bool flag) {
		enable = flag;
	}

	void set_layer_src(SignalLayer layer) {
		layer_src = layer;
	}

	void set_layer_dst(SignalLayer layer) {
		layer_dst = layer;
	}

	void set_signal_contact(std::function<void()> on_signal) {
		this->on_signal = on_signal;
	}

	void set_target_block(const Vector2& block) {
		this->target_block = block;
	}

	const Vector2& get_target_block() const {
		return target_block;
	}


};