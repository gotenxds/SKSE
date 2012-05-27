#include "PapyrusSKSE.h"
#include "skse_version.h"
#include "PapyrusVM.h"
#include "PapyrusNativeFunctions.h"

namespace papyrusSKSE {

	UInt32 GetVersion(StaticFunctionTag* base)
	{
		return SKSE_VERSION_INTEGER;
	}
	UInt32 GetVersionMinor(StaticFunctionTag* base)
	{
		return SKSE_VERSION_INTEGER_MINOR;
	}

	UInt32 GetVersionBeta(StaticFunctionTag* base)
	{
		return SKSE_VERSION_INTEGER_BETA;
	}

	UInt32 GetVersionRelease(StaticFunctionTag* base)
	{
		return SKSE_VERSION_RELEASEIDX;
	}

	void RegisterFuncs(VMClassRegistry* registry)
	{
		registry->RegisterFunction(
			new NativeFunction0<StaticFunctionTag, UInt32>("GetVersion", "SKSE", papyrusSKSE::GetVersion, registry));

		registry->RegisterFunction(
			new NativeFunction0<StaticFunctionTag, UInt32>("GetVersionMinor", "SKSE", papyrusSKSE::GetVersionMinor, registry));

		registry->RegisterFunction(
			new NativeFunction0<StaticFunctionTag, UInt32>("GetVersionBeta", "SKSE", papyrusSKSE::GetVersionBeta, registry));

		registry->RegisterFunction(
			new NativeFunction0<StaticFunctionTag, UInt32>("GetVersionRelease", "SKSE", papyrusSKSE::GetVersionRelease, registry));


	}

}
