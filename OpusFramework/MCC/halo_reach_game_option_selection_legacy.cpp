#include "opusframework-private-pch.h"

#ifdef _WIN64

std::string format_string(const char* pFormat, ...)
{
	va_list args;
	va_start(args, pFormat);
	char stringBuffer[64 * 1024] = {};
	vsnprintf(stringBuffer, _countof(stringBuffer) - 1, pFormat, args);
	va_end(args);
	return stringBuffer;
}

e_mcc_game_mode s_currentGameMode = _mcc_game_mode_campaign;
//e_campaign_difficulty_level g_LaunchCampaignDifficultyLevel = _campaign_difficulty_level_normal;
extern e_campaign_difficulty_level g_campaign_difficulty_level; // #TODO #REFACTOR

c_map_info_manager* c_halo_reach_game_option_selection_legacy::s_pMapInfoManager = nullptr;
const MapInfo* c_halo_reach_game_option_selection_legacy::s_pSelectedMapInfo[underlying_cast(SelectedGameModeMapInfoIndex::Count)] = {};

GameTypeManager* c_halo_reach_game_option_selection_legacy::s_pGameTypeManager = nullptr;
const GameType* c_halo_reach_game_option_selection_legacy::s_pSelectedGameType[underlying_cast(SelectedGameModeMapInfoIndex::Count)] = {};

// #TODO: Remove these
std::string c_halo_reach_game_option_selection_legacy::s_launch_game_variant = "";
std::string c_halo_reach_game_option_selection_legacy::s_launch_map_variant = "";
std::string c_halo_reach_game_option_selection_legacy::s_launch_saved_film_filepath = "";

void c_halo_reach_game_option_selection_legacy::Init()
{
	// #TODO: Support more games than just Halo Reach
	s_pMapInfoManager = new c_map_info_manager("haloreach/maps/info");

	loadSettings();
}

void c_halo_reach_game_option_selection_legacy::deinit()
{
	delete s_pMapInfoManager;
}

void c_halo_reach_game_option_selection_legacy::loadSettings()
{
	for (underlying(SelectedGameModeMapInfoIndex) i = 0; i < underlying_cast(SelectedGameModeMapInfoIndex::Count); i++)
	{
		s_pSelectedMapInfo[i] = GetDefaultMapSelection(static_cast<SelectedGameModeMapInfoIndex>(i));
	}

	char pLaunchGameModeBuffer[256] = {};
	c_settings_legacy::read_string(_settings_section_legacy_launch, "GameMode", pLaunchGameModeBuffer, sizeof(pLaunchGameModeBuffer), "");
	s_currentGameMode = string_to_mcc_game_mode(pLaunchGameModeBuffer);
	if (s_currentGameMode == _mcc_game_mode_none)
	{
		s_currentGameMode = _mcc_game_mode_campaign;
	}

	char pLaunchCampaignDifficultyLevelBuffer[256] = {};
	c_settings_legacy::read_string(_settings_section_legacy_launch, "DifficultyLevel", pLaunchCampaignDifficultyLevelBuffer, sizeof(pLaunchCampaignDifficultyLevelBuffer), "normal");
	g_campaign_difficulty_level = string_to_campaign_difficulty_level(pLaunchCampaignDifficultyLevelBuffer);

	LPCSTR pDefaultHopperGameVariant = "";
	switch (s_currentGameMode)
	{
		break;
	case _mcc_game_mode_campaign:
		pDefaultHopperGameVariant = "campaign_default_054";
		break;
	case _mcc_game_mode_multiplayer:
		pDefaultHopperGameVariant = "slayer_054";
		break;
	case _mcc_game_mode_firefight:
		pDefaultHopperGameVariant = "ff_firefight_054";
		break;
	}

	// #TODO: This must persist outside of the read
	static char pLaunchGameVariantBuffer[256] = {};
	uint32_t LaunchGameVariantLength = c_settings_legacy::read_string(_settings_section_legacy_launch, "GameVariant", pLaunchGameVariantBuffer, sizeof(pLaunchGameVariantBuffer), pDefaultHopperGameVariant);
	if (LaunchGameVariantLength > 0)
	{
		s_launch_game_variant = pLaunchGameVariantBuffer;
	}
	else
	{
		s_launch_game_variant = "";
	}

	// #TODO: This must persist outside of the read
	static char pLaunchMapVariantBuffer[256] = {};
	uint32_t LaunchMapVariantLength = c_settings_legacy::read_string(_settings_section_legacy_launch, "MapVariant", pLaunchMapVariantBuffer, sizeof(pLaunchMapVariantBuffer), "");
	if (LaunchMapVariantLength > 0)
	{
		s_launch_map_variant = pLaunchMapVariantBuffer;
	}
	else
	{
		s_launch_map_variant = "";
	}
}

e_mcc_game_mode c_halo_reach_game_option_selection_legacy::get_selected_game_mode()
{
	return s_currentGameMode;
}

void c_halo_reach_game_option_selection_legacy::SelectGameMode()
{
	if (c_command_line::has_command_line_arg("-showallmodes"))
	{
		const char* selected_mcc_game_mode_string = mcc_mcc_game_mode_to_local_string(s_currentGameMode);
		if (ImGui::BeginCombo("###MODE", selected_mcc_game_mode_string))
		{
			for (underlying(e_mcc_game_mode) i = 0; i < k_number_of_mcc_game_modes; i++)
			{
				const char* current_mcc_game_mode_string = mcc_mcc_game_mode_to_local_string(static_cast<e_mcc_game_mode>(i));
				DEBUG_ASSERT(current_mcc_game_mode_string != nullptr);

				bool selected = selected_mcc_game_mode_string == current_mcc_game_mode_string;
				if (ImGui::Selectable(current_mcc_game_mode_string, &selected))
				{
					s_currentGameMode = static_cast<e_mcc_game_mode>(i);
					c_settings_legacy::write_string(_settings_section_legacy_launch, "GameMode", mcc_mcc_game_mode_to_string(s_currentGameMode));
				}
			}

			ImGui::EndCombo();
		}
	}
	else
	{
		LPCSTR s_pCurrentGameModeStr = mcc_mcc_game_mode_to_local_string(s_currentGameMode);
		if (ImGui::BeginCombo("###MODE", s_pCurrentGameModeStr))
		{
			for (underlying(SelectedGameModeMapInfoIndex) i = 0; i < underlying_cast(SelectedGameModeMapInfoIndex::Count); i++)
			{
				if (static_cast<SelectedGameModeMapInfoIndex>(i) == SelectedGameModeMapInfoIndex::Unknown)
				{
					continue;
				}

				e_mcc_game_mode gameMode = SelectedGameModeMapInfoIndexToGameMode(static_cast<SelectedGameModeMapInfoIndex>(i));
				LPCSTR pGameModeStr = mcc_mcc_game_mode_to_local_string(gameMode);
				if (pGameModeStr)
				{
					bool selected = s_pCurrentGameModeStr == pGameModeStr;
					if (ImGui::Selectable(pGameModeStr, &selected))
					{
						s_currentGameMode = gameMode;
						c_settings_legacy::write_string(_settings_section_legacy_launch, "GameMode", mcc_mcc_game_mode_to_string(s_currentGameMode));
					}
				}
			}

			ImGui::EndCombo();
		}
	}
}

void c_halo_reach_game_option_selection_legacy::Render()
{


	SelectSavedFilm();

	//ImGui::Separator();

	//if (s_currentGameMode != GameMode::Multiplayer)
	//{
	//	ImGui::PushItemWidth((width / 100) * 25 * 0.938f);
	//}
	//else
	//{
	//	ImGui::PushItemWidth((width / 100) * 25 * 1.415f);
	//}
	SelectGameMode();
	//ImGui::SameLine();
	SelectMap();

	//if (s_currentGameMode != GameMode::Multiplayer)
	//{
	//	ImGui::SameLine();
	//}
	SelectDifficulty();
	//ImGui::PopItemWidth();

	//ImGui::Separator();

	SelectGameVariant();
	SelectMapVariant();
}

const MapInfo* c_halo_reach_game_option_selection_legacy::GetDefaultMapSelection(SelectedGameModeMapInfoIndex gameModeMapInfoIndex)
{
	int previousMapID = c_settings_legacy::read_integer(_settings_section_legacy_launch, s_kpMapInfoSettingsName[underlying_cast(gameModeMapInfoIndex)], -1);
	for (const MapInfo& rMapInfo : s_pMapInfoManager->map_infos)
	{
		if (rMapInfo.GetMapID() == previousMapID)
		{
			return &rMapInfo;
		}
	}

	return nullptr;
}

const MapInfo* c_halo_reach_game_option_selection_legacy::GetDefaultHaloReachGameOptionSelection(SelectedGameModeMapInfoIndex gameModeMapInfoIndex)
{
	int previousMapID = c_settings_legacy::read_integer(_settings_section_legacy_launch, s_kpMapInfoSettingsName[underlying_cast(gameModeMapInfoIndex)], -1);
	for (const MapInfo& rMapInfo : s_pMapInfoManager->map_infos)
	{
		if (rMapInfo.GetMapID() == previousMapID)
		{
			return &rMapInfo;
		}
	}

	return nullptr;
}

c_halo_reach_game_option_selection_legacy::SelectedGameModeMapInfoIndex c_halo_reach_game_option_selection_legacy::GameModeToSelectedGameModeMapInfoIndex(e_mcc_game_mode gameMode)
{
	switch (gameMode)
	{
	case _mcc_game_mode_campaign:
		return SelectedGameModeMapInfoIndex::Campaign;
		break;
	case _mcc_game_mode_multiplayer:
		return SelectedGameModeMapInfoIndex::Multiplayer;
		break;
	case _mcc_game_mode_firefight:
		return SelectedGameModeMapInfoIndex::Firefight;
		break;
	default:
		return SelectedGameModeMapInfoIndex::Unknown;
		break;
	}
}

e_mcc_game_mode c_halo_reach_game_option_selection_legacy::SelectedGameModeMapInfoIndexToGameMode(SelectedGameModeMapInfoIndex selectedGameModeMapInfoIndex)
{
	switch (selectedGameModeMapInfoIndex)
	{
	case SelectedGameModeMapInfoIndex::Campaign:
		return _mcc_game_mode_campaign;
		break;
	case SelectedGameModeMapInfoIndex::Multiplayer:
		return _mcc_game_mode_multiplayer;
		break;
	case SelectedGameModeMapInfoIndex::Firefight:
		return _mcc_game_mode_firefight;
		break;
	default:
		return _mcc_game_mode_none;
	}
}

const MapInfo*& c_halo_reach_game_option_selection_legacy::GetSelectedMapInfoBySelectedGameModeMapInfoIndex(SelectedGameModeMapInfoIndex selectedGameModeMapInfoIndex)
{
	const MapInfo*& pSelectedMapInfo = s_pSelectedMapInfo[underlying_cast(selectedGameModeMapInfoIndex)];
	return pSelectedMapInfo;
}

const MapInfo*& c_halo_reach_game_option_selection_legacy::GetSelectedMapInfoByGameMode(e_mcc_game_mode gameMode)
{
	return GetSelectedMapInfoBySelectedGameModeMapInfoIndex(GameModeToSelectedGameModeMapInfoIndex(s_currentGameMode));
}

const MapInfo* c_halo_reach_game_option_selection_legacy::get_selected_map_info()
{
	return GetSelectedMapInfoByGameMode(s_currentGameMode);
}

const MapInfo* c_halo_reach_game_option_selection_legacy::GetFirstSuitableGameModeMapInfo(e_mcc_game_mode gameMode)
{
	for (const MapInfo& rMapInfo : s_pMapInfoManager->map_infos)
	{
		if (isMapInfoCompatibleWithGameMode(gameMode, rMapInfo))
		{
			return &rMapInfo;
		}
	}
	return nullptr;
}

void c_halo_reach_game_option_selection_legacy::SaveSelectedMap(e_mcc_game_mode gameMode, const MapInfo* pMapInfo)
{
	switch (gameMode)
	{
	case _mcc_game_mode_campaign:
		c_settings_legacy::write_integer(_settings_section_legacy_launch, s_kpMapInfoSettingsName[underlying_cast(SelectedGameModeMapInfoIndex::Campaign)], pMapInfo ? pMapInfo->GetMapID() : -1);
		break;
	case _mcc_game_mode_multiplayer:
		c_settings_legacy::write_integer(_settings_section_legacy_launch, s_kpMapInfoSettingsName[underlying_cast(SelectedGameModeMapInfoIndex::Multiplayer)], pMapInfo ? pMapInfo->GetMapID() : -1);
		break;
	case _mcc_game_mode_firefight:
		c_settings_legacy::write_integer(_settings_section_legacy_launch, s_kpMapInfoSettingsName[underlying_cast(SelectedGameModeMapInfoIndex::Firefight)], pMapInfo ? pMapInfo->GetMapID() : -1);
		break;
	default:
		c_settings_legacy::write_integer(_settings_section_legacy_launch, s_kpMapInfoSettingsName[underlying_cast(SelectedGameModeMapInfoIndex::Unknown)], pMapInfo ? pMapInfo->GetMapID() : -1);
		break;
	}
}

bool c_halo_reach_game_option_selection_legacy::isMapInfoCompatibleWithGameMode(e_mcc_game_mode gameMode, const MapInfo& rMapInfo)
{
	switch (gameMode)
	{
	case _mcc_game_mode_campaign:
		if (!rMapInfo.IsCampaign()) return false;
		break;
	case _mcc_game_mode_multiplayer:
		if (!rMapInfo.IsMultiplayer()) return false;
		break;
	case _mcc_game_mode_firefight:
		if (!rMapInfo.IsFirefight()) return false;
		break;
	}
	return true;
}

void c_halo_reach_game_option_selection_legacy::RenderHoveredTooltip(const char* pText)
{
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::Text(pText);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void c_halo_reach_game_option_selection_legacy::SelectMap()
{
	const MapInfo*& pSelectedMapInfo = GetSelectedMapInfoByGameMode(s_currentGameMode);

	if (!pSelectedMapInfo || pSelectedMapInfo && !isMapInfoCompatibleWithGameMode(s_currentGameMode, *pSelectedMapInfo))
	{
		pSelectedMapInfo = GetFirstSuitableGameModeMapInfo(s_currentGameMode);
		SaveSelectedMap(s_currentGameMode, pSelectedMapInfo);
	}

	const char* pSelectedLevelName = "<no level selected>";
	if (pSelectedMapInfo)
	{
		pSelectedLevelName = pSelectedMapInfo->GetFriendlyName();
	}

	if (ImGui::BeginCombo("###MAP", pSelectedLevelName))
	{
		// #TODO: Make a nice and beautiful interface to this for multi-game
		for (const MapInfo& rMapInfo : s_pMapInfoManager->map_infos)
		{
			if (!isMapInfoCompatibleWithGameMode(s_currentGameMode, rMapInfo))
			{
				continue;
			}

			bool isSelected = pSelectedMapInfo == &rMapInfo;
			const char* pCurrentLevelFriendlyName = rMapInfo.GetFriendlyName();

			if (ImGui::Selectable(pCurrentLevelFriendlyName, &isSelected))
			{
				pSelectedMapInfo = &rMapInfo;
				SaveSelectedMap(s_currentGameMode, pSelectedMapInfo);
			}
			RenderHoveredTooltip(rMapInfo.GetFriendlyDescription());
		}

		ImGui::EndCombo();
	}
}

void c_halo_reach_game_option_selection_legacy::SelectDifficulty()
{
	if (s_currentGameMode == _mcc_game_mode_campaign || s_currentGameMode == _mcc_game_mode_firefight)
	{
		LPCSTR pCurrentDifficultyStr = campaign_difficulty_level_to_local_string(g_campaign_difficulty_level);
		if (ImGui::BeginCombo("###DIFFICULTY", pCurrentDifficultyStr))
		{
			for (e_campaign_difficulty_level difficulty = e_campaign_difficulty_level::_campaign_difficulty_level_easy; difficulty < k_number_of_campaign_difficulty_levels; reinterpret_cast<int&>(difficulty)++)
			{
				LPCSTR pDifficultyStr = campaign_difficulty_level_to_local_string(difficulty);
				if (pDifficultyStr)
				{
					bool selected = pDifficultyStr == pCurrentDifficultyStr;
					if (ImGui::Selectable(pDifficultyStr, &selected))
					{
						g_campaign_difficulty_level = static_cast<e_campaign_difficulty_level>(difficulty);
						c_settings_legacy::write_string(_settings_section_legacy_launch, "DifficultyLevel", campaign_difficulty_level_to_string(g_campaign_difficulty_level));
					}
				}
			}

			ImGui::EndCombo();
		}
	}
}

void c_halo_reach_game_option_selection_legacy::GetVariantInfo(char* buffer, std::string* name, std::string* desc)
{
	for (size_t i = 0; i < 256; i++)
	{
		char* nameCur = &buffer[0x80 + i];
		if (nameCur[0] && !nameCur[1])
		{
			*name += nameCur;
		}
		char* descCur = &buffer[0x180 + i];
		if (descCur[0] && !descCur[1])
		{
			*desc += descCur;
		}
	}
}

int c_halo_reach_game_option_selection_legacy::ReadGameVariant(LPCSTR pName, std::string* name, std::string* desc, LPCSTR pPath)
{
	static s_game_variant gameVariant;
	IDataAccess* pDataAccess = c_halo_reach_game_host::get_data_access();
	ASSERT(pDataAccess != nullptr);
	load_game_variant(pDataAccess, "haloreach", pName, gameVariant);

	int result = gameVariant.game_engine_index;

	GetVariantInfo(gameVariant.game_engine_variant.data, name, desc);

	if (!(*name).c_str()[0])
	{
		*name = pName;
	}

	return result;
}

int c_halo_reach_game_option_selection_legacy::ReadMapVariant(LPCSTR pName, std::string* name, std::string* desc, LPCSTR pPath)
{
	static s_map_variant mapVariant;
	IDataAccess* pDataAccess = c_halo_reach_game_host::get_data_access();
	ASSERT(pDataAccess != nullptr);
	load_map_variant(pDataAccess, "haloreach", pName, mapVariant);

	int result = *reinterpret_cast<int*>(&mapVariant.data[0x2C]);
	GetVariantInfo(mapVariant.data, name, desc);

	return result;
}

int c_halo_reach_game_option_selection_legacy::ReadSavedFilm(LPCSTR pName, std::string* name, std::string* desc, LPCSTR pPath)
{
	IDataAccess* pDataAccess = c_halo_reach_game_host::get_data_access();
	if (pDataAccess)
	{
		char* out_data = { 0 };

		c_file_reference filo(pPath);
		if (filo.open_file())
		{
			out_data = pDataAccess->SaveFilmMetadataCreateFromFile(filo.buffer, static_cast<int>(filo.buffer_size))->data;

			filo.read_string_long_as_string(name, 256, 0xC0);
			filo.read_string_long_as_string(desc, 256, 0x1C0);

			filo.close_file();
		}
	}

	return -1;
}

void c_halo_reach_game_option_selection_legacy::SelectGameVariant()
{
	const char* pEngineName = "haloreach"; // #TODO: Set this up properly
	static std::vector<std::string> pfilePaths = {
		format_string("%s/game_variants", pEngineName/*"haloreach"*/),
		format_string("%s/hopper_game_variants", pEngineName/*"haloreach"*/),
		format_string("%s/AppData/LocalLow/MCC/Temporary/UserContent/%s/GameType/", GetUserprofileVariable(), pEngineName/*"haloreach"*/)
	};
	static c_file_array fileArray = c_file_array(pfilePaths, { ".bin" }, &ReadGameVariant);
	static LPCSTR pLast = s_launch_game_variant.c_str();

	if (s_currentGameMode == _mcc_game_mode_campaign)
	{
		return;
	}

	if (ImGui::BeginCombo("###GAME VARIANT", fileArray.get_name(pLast)))
	{
		for (size_t i = 0; i < fileArray.Count; i++)
		{
			int shouldShow = s_currentGameMode == _mcc_game_mode_multiplayer && fileArray.GetType(i) == _game_engine_type_sandbox;
			shouldShow |= s_currentGameMode == _mcc_game_mode_multiplayer && fileArray.GetType(i) == _game_engine_type_megalo;
			shouldShow |= s_currentGameMode == _mcc_game_mode_campaign && fileArray.GetType(i) == _game_engine_type_campaign;
			shouldShow |= s_currentGameMode == _mcc_game_mode_firefight && fileArray.GetType(i) == _game_engine_type_survival;

			if (fileArray.GetFileName(i) && shouldShow)
			{
				bool selected = fileArray.GetFileName(i) == fileArray.GetFileName(pLast);

				std::string pSelectedGameVariantName = std::string(fileArray.get_name(i)).append(" (").append(fileArray.GetFileName(i)).append(")###").append(std::to_string(i));
				if (ImGui::Selectable(pSelectedGameVariantName.c_str(), &selected))
				{
					pLast = fileArray.GetFileName(i);
				}

				RenderHoveredTooltip(fileArray.GetDesc(i));
			}
		}

		ImGui::EndCombo();
	}

	s_launch_game_variant = pLast;
}

void c_halo_reach_game_option_selection_legacy::SelectMapVariant()
{
	const char* pEngineName = "haloreach"; // #TODO: Set this up properly
	static std::vector<std::string> pfilePaths = {
		format_string("%s/map_variants", pEngineName/*"haloreach"*/),
		format_string("%s/map_game_variants", pEngineName/*"haloreach"*/),
		format_string("%s/AppData/LocalLow/MCC/Temporary/UserContent/%s/Map/", GetUserprofileVariable(), pEngineName/*"haloreach"*/)
	};
	static c_file_array fileArray = c_file_array(pfilePaths, { ".mvar" }, &ReadMapVariant);
	static LPCSTR pLast = s_launch_map_variant.c_str();

	if (s_currentGameMode != _mcc_game_mode_multiplayer)
	{
		return;
	}

	const MapInfo* pSelectedMapInfo = GetSelectedMapInfoByGameMode(s_currentGameMode);

	LPCSTR lastMapName = fileArray.get_name(pLast);
	if (!lastMapName || pLast[0] == 0)
	{
		pLast = "";
		lastMapName = "<Default Variant>";
	}
	if (ImGui::BeginCombo("###MAP VARIANT", lastMapName))
	{
		bool defaultSelected = false;
		if (ImGui::Selectable("<Default Variant>", &defaultSelected))
		{
			pLast = "";
		}

		for (size_t i = 0; i < fileArray.Count; i++)
		{
			int shouldShow = fileArray.GetType(i) == pSelectedMapInfo->GetMapID();

			if (fileArray.GetFileName(i) && shouldShow)
			{
				bool selected = fileArray.GetFileName(i) == fileArray.GetFileName(pLast);

				std::string pSelectedMapVariantName = std::string(fileArray.get_name(i)).append(" (").append(fileArray.GetFileName(i)).append(")###").append(std::to_string(i));
				if (ImGui::Selectable(pSelectedMapVariantName.c_str(), &selected) && !defaultSelected)
				{
					pLast = fileArray.GetFileName(i);
				}

				RenderHoveredTooltip(fileArray.GetDesc(i));
			}
		}

		ImGui::EndCombo();
	}

	s_launch_map_variant = pLast;
}

void c_halo_reach_game_option_selection_legacy::SelectSavedFilm()
{
	return;

	static std::vector<std::string> pFilePaths = {
		format_string("%s/Temporary/autosave/", "haloreach"),
		format_string("%s/AppData/LocalLow/MCC/Temporary/UserContent/%s/Movie/", GetUserprofileVariable(), "haloreach"),
		format_string("%s/AppData/LocalLow/MCC/Temporary/%s/autosave/", GetUserprofileVariable(), "haloreach")
	};

	static c_file_array fileArray = c_file_array(pFilePaths, { ".film", ".mov" }, &ReadSavedFilm);
	static LPCSTR pLast = "";

	if (s_launch_saved_film_filepath != fileArray.GetFileName(pLast))
	{
		s_launch_saved_film_filepath = fileArray.GetFileName(pLast);
	}
	if (pLast != fileArray.GetFileName(pLast))
	{
		pLast = fileArray.GetFileName(pLast);
	}

	if (ImGui::BeginCombo("###SAVED FILM", fileArray.GetDesc(pLast)))
	{
		for (size_t i = 0; i < fileArray.Count; i++)
		{
			if (fileArray.get_name(i))
			{
				bool selected = fileArray.get_name(i) == fileArray.get_name(pLast);

				std::string pSelectedSavedFilmName = std::string(fileArray.GetDesc(i)).append(" (").append(fileArray.GetFileName(i)).append(")###").append(std::to_string(i));
				if (ImGui::Selectable(fileArray.GetDesc(i), &selected))
				{
					pLast = fileArray.GetFileName(i);
				}

				RenderHoveredTooltip(fileArray.get_name(i));
			}
		}

		ImGui::EndCombo();
	}

	s_launch_saved_film_filepath = pLast;
}

void c_halo_reach_game_option_selection_legacy::load_map_variant(IDataAccess* pDataAccess, const char* engine_name, const char* pVariantName, s_map_variant& rMapVariant, bool print)
{
	memset(&rMapVariant, 0, sizeof(rMapVariant));

	if (pVariantName[0])
	{
		static std::string pFileName = "";
		if (!PathFileExists((pFileName = format_string("%s/hopper_map_variants/%s.mvar", engine_name, pVariantName)).c_str()))
		{
			if (!PathFileExists((pFileName = format_string("%s/map_variants/%s.mvar", engine_name, pVariantName)).c_str()))
			{
				if (!PathFileExists((pFileName = format_string("%s/AppData/LocalLow/HaloMCC/Temporary/UserContent/%s/Map/%s.mvar", GetUserprofileVariable(), engine_name, pVariantName)).c_str()))
				{
					if (!PathFileExists((pFileName = format_string("%s/AppData/LocalLow/MCC/Temporary/UserContent/%s/Map/%s.mvar", GetUserprofileVariable(), engine_name, pVariantName)).c_str()))
					{
						pFileName = "";
					}
				}
			}
		}

		c_file_reference filo(pFileName.c_str());
		if (filo.open_file())
		{
			if (print)
			{
				write_line_verbose("Loading map variant [%s]", pFileName.c_str());
			}

			rMapVariant = pDataAccess->MapVariantCreateFromFile(filo.buffer, static_cast<int>(filo.buffer_size))->MapVariant;
			filo.close_file();
			return;
		}
	}

	// fallback to use map ID
	{
		const MapInfo* pSelectedMapInfo = GetSelectedMapInfoByGameMode(s_currentGameMode);

		if (print)
		{
			write_line_verbose("Creating map variant for '%s'", pSelectedMapInfo->GetFriendlyName());
		}

		rMapVariant = pDataAccess->MapVariantCreateFromMapID(pSelectedMapInfo->GetMapID())->MapVariant;
	}
}

void c_halo_reach_game_option_selection_legacy::load_game_variant(IDataAccess* pDataAccess, const char* engine_name, const char* pVariantName, s_game_variant& rGameVariant, bool print)
{
	ASSERT(pDataAccess != nullptr);
	ASSERT(engine_name != nullptr);
	ASSERT(pVariantName != nullptr);

	memset(&rGameVariant, 0, sizeof(rGameVariant));
	if (pVariantName == nullptr)
	{
		return;
	}

	static std::string pFileName = "";
	if (!PathFileExists((pFileName = format_string("%s/hopper_game_variants/%s.bin", engine_name, pVariantName)).c_str()))
	{
		if (!PathFileExists((pFileName = format_string("%s/game_variants/%s.bin", engine_name, pVariantName)).c_str()))
		{
			if (!PathFileExists((pFileName = format_string("%s/AppData/LocalLow/HaloMCC/Temporary/UserContent/%s/GameType/%s.bin", GetUserprofileVariable(), engine_name, pVariantName)).c_str()))
			{
				if (!PathFileExists((pFileName = format_string("%s/AppData/LocalLow/MCC/Temporary/UserContent/%s/GameType/%s.bin", GetUserprofileVariable(), engine_name, pVariantName)).c_str()))
				{
					pFileName = "";
				}
			}
		}
	}

	c_file_reference filo(pFileName.c_str());
	if (filo.open_file())
	{
		if (print)
		{
			write_line_verbose("Loading game variant [%s]", pFileName.c_str());
		}

		IGameVariant* game_variant = pDataAccess->GameVariantCreateFromFile(filo.buffer, static_cast<int>(filo.buffer_size));
		if (game_variant)
		{

			rGameVariant = game_variant->GameVariant;
		}
		else
		{
			write_line_verbose(__FUNCTION__"> warning: failed to create game variant from file '%s'", pFileName.c_str());
		}
		filo.close_file();
	}
}

// TODO: Test, and fix if broke
void c_halo_reach_game_option_selection_legacy::load_savegame(const char* pGamestateName, GameContext& gameContext)
{
	char pFileName[MAX_PATH + 1];
	sprintf(pFileName, "%s.hdr", pGamestateName);
	pFileName[MAX_PATH] = 0;

	char* pGameStateBuffer = {};
	size_t gameStateSize = {};

	c_file_reference filo(pFileName);
	if (filo.open_file())
	{
		pGameStateBuffer = new char[filo.buffer_size];
		memset(pGameStateBuffer, 0x00, filo.buffer_size);
		pGameStateBuffer = filo.buffer;

		gameContext.game_mode = _mcc_game_mode_campaign;
		gameContext.game_state_header_size = filo.buffer_size;
		gameContext.game_state_header_ptr = pGameStateBuffer;

		filo.close_file();
	}
}

void c_halo_reach_game_option_selection_legacy::load_savefilm(const char* pSavedFilmName, GameContext& gameContext)
{
	if (!pSavedFilmName[0])
		return;

	static std::string pFileName = "";
	if (!PathFileExists((pFileName = format_string("%s/Temporary/autosave/%s.film", "haloreach", pSavedFilmName)).c_str()))
	{
		if (!PathFileExists((pFileName = format_string("%s/Temporary/autosave/%s.mov", "haloreach", pSavedFilmName)).c_str()))
		{
			if (!PathFileExists((pFileName = format_string("%s/AppData/LocalLow/HaloMCC/Temporary/UserContent/%s/Movie/%s.mov", GetUserprofileVariable(), "haloreach", pSavedFilmName)).c_str()))
			{
				if (!PathFileExists((pFileName = format_string("%s/AppData/LocalLow/MCC/Temporary/UserContent/%s/Movie/%s.mov", GetUserprofileVariable(), "haloreach", pSavedFilmName)).c_str()))
				{
					if (!PathFileExists((pFileName = format_string("%s/AppData/LocalLow/MCC/Temporary/%s/autosave/%s.film", GetUserprofileVariable(), "haloreach", pSavedFilmName)).c_str()))
					{
						pFileName = "";
					}
				}
			}
		}
	}

	if (pFileName.c_str())
	{
		write_line_verbose("Loading saved film [%s]", pFileName.c_str());
	}

	gameContext.saved_film_path_ptr = pFileName.c_str();
}

#endif
