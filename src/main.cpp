#pragma once

#include "LoadGame.h"


#include <SKSE/SKSE.h>
#include <stddef.h>

using namespace SKSE;
using namespace SKSE::log;

SKSEPluginLoad(const LoadInterface* skse){
#ifndef NDEBUG
	while (!IsDebuggerPresent()) {
		Sleep(100);
	}
#endif

	auto* plugin = SKSE::PluginDeclaration::GetSingleton();
	auto pName = plugin->GetName();
	auto pVersion = plugin->GetVersion().string();

	DKUtil::Logger::Init(pName, pVersion);

	SKSE::Init(skse);

	INFO("{} v{} loaded", pName, pVersion);

	// do stuff
	auto g_message = SKSE::GetMessagingInterface();
	if (!g_message) {
		ERROR("Messaging Interface Not Found!");
		return false;
	}

	g_message->RegisterListener(CombatPathing::EventCallback);

	return true;
}
