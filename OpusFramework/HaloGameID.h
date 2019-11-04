#pragma once

enum class HaloGameID
{
	NotSet,
	HaloReach_2019_Jun_24,
	HaloReach_2019_Aug_20,
	HaloReach_2019_Oct_30,
	Count
};

constexpr intptr_t GetHaloBaseAddress(HaloGameID gameID)
{
	switch (gameID)
	{
	case HaloGameID::HaloReach_2019_Jun_24:
	case HaloGameID::HaloReach_2019_Aug_20:
	case HaloGameID::HaloReach_2019_Oct_30:
		return 0x180000000;
	}
	return ~intptr_t();
}

constexpr intptr_t GetHaloTopAddress(HaloGameID gameID)
{
	switch (gameID)
	{
	case HaloGameID::HaloReach_2019_Jun_24:
		return 0x184925000;
	case HaloGameID::HaloReach_2019_Aug_20:
		return 0x18450D000;
	case HaloGameID::HaloReach_2019_Oct_30:
		return 0x183985000;
	}
	return ~intptr_t();
}

constexpr const char* GetHaloExecutableString(HaloGameID gameID)
{
	switch (gameID)
	{
	case HaloGameID::HaloReach_2019_Jun_24:
	case HaloGameID::HaloReach_2019_Aug_20:
	case HaloGameID::HaloReach_2019_Oct_30:
		return "haloreach.dll";
	}
	FATAL_ERROR("Unsupported HaloGameID");
}

extern bool IsHaloExecutableLoaded(HaloGameID gameID);
extern void* GetLoadedHaloModule(HaloGameID gameID);