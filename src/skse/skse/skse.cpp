#include "skse_version.h"
#include "CommandTable.h"
#include "SafeWrite.h"
#include "PluginManager.h"

#if RUNTIME

IDebugLog	gLog("skse.log");

STATIC_ASSERT(RUNTIME_VERSION == RUNTIME_VERSION_1_4_15_0);

#include "Hooks_Scaleform.h"
#include "Hooks_Gameplay.h"
#include "Hooks_ObScript.h"
#include "Hooks_DirectInput8Create.h"

#else

IDebugLog	gLog("skse_editor.log");

#endif

void ApplyPatch(UInt32 base, UInt8 * buf, UInt32 len)
{
	for(UInt32 i = 0; i < len; i++)
		SafeWrite8(base + i, buf[i]);
}

void FixCoopLevel(void)
{
	SafeWrite8(0x00A4E971 + 1, 0x06);
	SafeWrite8(0x00A4FA6C + 1, 0x16);
}

void WaitForDebugger(void)
{
	while(!IsDebuggerPresent())
	{
		Sleep(10);
	}

	Sleep(1000 * 2);
}

bool isInit = false;

void SKSE_Initialize(void)
{
	if(isInit) return;
	isInit = true;

#ifndef _DEBUG
	__try {
#endif

		FILETIME	now;
		GetSystemTimeAsFileTime(&now);

#if RUNTIME
		_MESSAGE("SKSE runtime: initialize (version = %d.%d.%d %08X %08X%08X)",
			SKSE_VERSION_INTEGER, SKSE_VERSION_INTEGER_MINOR, SKSE_VERSION_INTEGER_BETA, RUNTIME_VERSION,
			now.dwHighDateTime, now.dwLowDateTime);
#else
		_MESSAGE("SKSE editor: initialize (version = %d.%d.%d %08X %08X%08X)",
			SKSE_VERSION_INTEGER, SKSE_VERSION_INTEGER_MINOR, SKSE_VERSION_INTEGER_BETA, EDITOR_VERSION,
			now.dwHighDateTime, now.dwLowDateTime);
#endif
		_MESSAGE("imagebase = %08X", GetModuleHandle(NULL));

#ifdef _DEBUG
		SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS);

		FixCoopLevel();
//		WaitForDebugger();
#endif

//		Commands_Dump();

		Hooks_ObScript_Init();

		g_pluginManager.Init();

		Hooks_Scaleform_Commit();
		Hooks_Gameplay_Commit();
		Hooks_ObScript_Commit();
//		Hooks_DirectInput_Commit();

		FlushInstructionCache(GetCurrentProcess(), NULL, 0);

#ifndef _DEBUG
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		_ERROR("exception");
	}
#endif

	_MESSAGE("init complete");
}

void SKSE_DeInitialize(void)
{
	//
}

extern "C" {

	void StartSKSE(void)
	{
		SKSE_Initialize();
	}

	BOOL WINAPI DllMain(HANDLE hDllHandle, DWORD dwReason, LPVOID lpreserved)
	{
		switch(dwReason)
		{
		case DLL_PROCESS_ATTACH:
			SKSE_Initialize();
			break;

		case DLL_PROCESS_DETACH:
			SKSE_DeInitialize();
			break;
		};

		return TRUE;
	}

};