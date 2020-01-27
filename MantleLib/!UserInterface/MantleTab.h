#pragma once

class MantleTab
{
public:
	MantleTab(const char* pTitle, const char* pDescription)
		: m_title(pTitle)
		, m_description(pDescription)
		, m_isOpen(true)
	{

	}
	virtual ~MantleTab();
	virtual void GameRender();

	void Render(bool setSelected);
	inline const char* GetTitle() const { return m_title.c_str(); }
	inline const char* GetDescription() const { return m_description.c_str(); }

	using TabClosedCallback = std::function<void(MantleTab&)>;
	void AddTabClosedCallback(TabClosedCallback);
protected:
	virtual void RenderContents(bool setSelected) = 0;

	bool m_isOpen;
	std::string m_title;
	std::string m_description;
	std::vector<TabClosedCallback> tabClosedCallback;

	using ImGUIDynamnicData = std::pair<void*, char[32]>;
	std::vector<ImGUIDynamnicData*> m_imGuiDynamicData;

	inline ImGUIDynamnicData& GetDynamicData(void* pPosition);
	template<typename T>
	inline T& GetDynamicData(void* pPosition)
	{
		ImGUIDynamnicData& rDynamicData = GetDynamicData(pPosition);
		static_assert(sizeof(T) <= sizeof(rDynamicData.second), "Dynamic data exceeds allocated space");
		T& rDynamicTagBlockData = *reinterpret_cast<T*>(rDynamicData.second);
		return rDynamicTagBlockData;
	}

	

};

inline MantleTab::ImGUIDynamnicData& MantleTab::GetDynamicData(void* pPosition)
{
	for (ImGUIDynamnicData* pDynamicData : m_imGuiDynamicData)
	{
		if (pDynamicData->first == pPosition)
		{
			return *pDynamicData;
		}
	}

	ImGUIDynamnicData& rDynamicData = *m_imGuiDynamicData.emplace_back(new ImGUIDynamnicData{});
	rDynamicData.first = pPosition;
	return rDynamicData;
}
