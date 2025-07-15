#include "signal_manager.h"
#include <graphics.h>

SignalManager* SignalManager::manager = nullptr;

SignalManager* SignalManager::instance() {
	if (manager == nullptr) {
		manager = new SignalManager();
	}
	return manager;
}

//SignalManager::SignalManager() = default;
//SignalManager::~SignalManager() = default;

Signal* SignalManager::create_signal() {
	Signal* signal = new Signal();
	signal_list.push_back(signal);
	return signal;
}

void SignalManager::destory_signal(Signal* signal) {
	auto it = std::find(signal_list.begin(), signal_list.end(), signal);
	if (it != signal_list.end()) {
		signal_list.erase(it);
		delete signal;
	}
}

void SignalManager::process_signals() {
	
}