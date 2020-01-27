#pragma once

class VirtualMemoryContainer;

class CacheFile
{
public:
	friend class TagInterface;
	friend class GroupInterface;

	CacheFile(const std::wstring& mapFilePath);
	~CacheFile();

	void SaveMap();

	bool IsLoading() const { return m_isMapLoading; }
	uint64_t GetVirtualAddressSpace(bool ignoreLoadingCheck = false) const { return (!ignoreLoadingCheck && IsLoading()) ? 0 : m_pHeader->virtual_base_address; }
	uint64_t ConvertPageOffset(uint32_t pageOffset, bool ignoreLoadingCheck = false) const
	{
		if (!ignoreLoadingCheck && IsLoading()) return 0;
		else return (static_cast<uint64_t>(pageOffset) * 4ull) - (GetVirtualAddressSpace(ignoreLoadingCheck) - 0x50000000ull);
	}
	using SectionCache = std::pair<char*, size_t>;
	inline SectionCache& GetSection(e_cache_file_section cache_file_section) { return m_pSectionCache[underlying_cast(cache_file_section)]; };
	inline SectionCache& GetDebugSection() { return GetSection(e_cache_file_section::_cache_file_section_debug); };
	inline SectionCache& GetTagsSection() { return GetSection(e_cache_file_section::_cache_file_section_tags); };
	inline SectionCache& GetResourcesSection() { return GetSection(e_cache_file_section::_cache_file_section_resource); };
	inline SectionCache& GetLocalizationSection() { return GetSection(e_cache_file_section::_cache_file_section_localization); };
	inline size_t GetTagCount() const { return IsLoading() ? 0 : m_tagInterfaces.size(); }
	inline TagInterface* GetTagInterface(uint16_t index) const { return (IsLoading() || index == 0xFFFFui16) ? nullptr : m_tagInterfaces[index]; }
	inline const std::vector<TagInterface*> GetTagInterfaces(bool ignoreLoadingCheck = false) const
	{
		if (!ignoreLoadingCheck && IsLoading())
		{
			static std::vector<TagInterface*> sEmptyVector;
			return sEmptyVector;
		}
		return m_tagInterfaces;
	}
	inline const std::vector<GroupInterface*> GetGroupInterfaces(bool ignoreLoadingCheck = false) const
	{
		if (!ignoreLoadingCheck && IsLoading())
		{
			static std::vector<GroupInterface*> sEmptyVector;
			return sEmptyVector;
		}
		return m_groupInterfaces;
	}
	inline GroupInterface* GetGroupInterfaceByGroupID(TagGroupName groupName)
	{
		if (groupName != TagGroupName::Invalid)
		{
			for (GroupInterface* pGroupInterface : GetGroupInterfaces())
			{
				if (pGroupInterface->m_groupMagic == underlying_cast(groupName))
				{
					return pGroupInterface;
				}
			}
		}
		return nullptr;
	}
	
	template<typename R, typename T>
	inline R* GetTagBlockData(s_tag_block_definition<T>& rTagBlock)
	{
		return reinterpret_cast<R*>(getTagBlockDataInternal(*reinterpret_cast<s_tag_block_definition<>*>(&rTagBlock)));
	}

	template<typename T>
	inline T* GetTagBlockData(s_tag_block_definition<T>& rTagBlock)
	{
		return reinterpret_cast<T*>(getTagBlockDataInternal(*reinterpret_cast<s_tag_block_definition<>*>(&rTagBlock)));
	}

	inline const wchar_t* GetFilePath() const { return m_mapFilePath.c_str(); }
	inline const wchar_t* GetFileName() const { return m_mapFileName.c_str(); }
	inline const char* GetFilePathChar() const { return m_mapFilePathChar.c_str(); }
	inline const char* GetFileNameChar() const { return m_mapFileNameChar.c_str(); }

	inline const char* GetStringIDStr(uint32_t id)
	{
		long const k_string_id_set_string_counts[17] = { 1225, 1637, 217, 106, 217, 38, 5, 1727, 368, 20, 98, 24, 0, 13, 41, 97, 115 };

		uint32_t set = (id >> _countof(k_string_id_set_string_counts)) & 0xFF;
		uint32_t index = id & ((1 << _countof(k_string_id_set_string_counts)) - 1);

		int set_base_index = 0;

		if (set == 0 && index >= k_string_id_set_string_counts[set])
		{
			for (int i = 0; i < _countof(k_string_id_set_string_counts); i++)
				set_base_index += k_string_id_set_string_counts[i];

			index -= k_string_id_set_string_counts[set];
		}
		else
		{
			for (int i = 0; i < set; i++)
				set_base_index += k_string_id_set_string_counts[i];
		}

		return m_pStringIDBuffer + m_pStringIDIndices[set_base_index + index];
	}

//private:

	inline char* getTagBlockDataInternal(s_tag_block_definition<>& rTagBlock)
	{
		const CacheFile::SectionCache& rSectionInfo = GetSection(e_cache_file_section::_cache_file_section_tags);
		char* pTagsSection = rSectionInfo.first;

		uint64_t pageOffset = ConvertPageOffset(rTagBlock.address);
		char* pTagBlockData = pTagsSection + pageOffset;

		return pTagBlockData;
	}

	void loadMap(const std::wstring& mapFilePath);


	/* initialize each group instance */
	void initGroupInstances();
	/* initialize each tag instance */
	void initTagInstances();
	/* for each tag group store which tags are represented by it into the vector */
	void initTagGroupRelationship();
	volatile bool m_isMapLoading;
	std::wstring m_mapFilePath;
	std::wstring m_mapFileName;
	std::string m_mapFilePathChar;
	std::string m_mapFileNameChar;
	VirtualMemoryContainer& m_rVirtualMemoryContainer;

	// raw data
	long* m_pTagNameIndices;
	char* m_pTagNameBuffer;
	long *m_pStringIDIndices;
	char *m_pStringIDBuffer;
	s_cache_file_header* m_pHeader;
	s_cache_file_tags_header* m_pTagFilesHeader;
	s_cache_file_tag_instance* m_pTagInstances;
	s_cache_file_tag_group* m_pGroupInstances;

	// interface types
	SectionCache m_pSectionCache[underlying_cast(e_cache_file_section::k_number_of_cache_file_sections)];
	std::vector<TagInterface*> m_tagInterfaces;
	std::vector<GroupInterface*> m_groupInterfaces;

};
