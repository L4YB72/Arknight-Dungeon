#pragma once
#include "Signal.h"
#include <vector>

class SignalManager {
public:
	static SignalManager* instance();

private:
	static SignalManager* manager;
	
	Signal* create_signal();
	void destory_signal(Signal* signal);

	void process_signals();
	void on_debug_render();

	std::vector<Signal*> signal_list;

private:
	SignalManager() = default;
	~SignalManager() = default;
};