#pragma once

class Manager : public RE::BSTEventSink<RE::LocationDiscovery::Event>
{
public:
	static Manager* GetSingleton()
	{
		return &instance;
	};

	void Register();
	void LoadSettings();

	bool ShouldMuteJingle();
	void SendLocationPopup(RE::MapMarkerData* a_mapMarkerData);

private:
	const char* GetLocationOnEntry(RE::MapMarkerData* a_mapMarkerData);

	virtual RE::BSEventNotifyControl ProcessEvent(const RE::LocationDiscovery::Event* a_event, RE::BSTEventSource<RE::LocationDiscovery::Event>* a_eventSource) override;

	// members
	std::uint32_t   mode{ 1 };
	bool            muteJingle{ false };
	std::uint32_t   currentCRC{ 0 };
	std::uint32_t   lastCRC{ 0 };
	RE::MARKER_TYPE lastMarkerType{ RE::MARKER_TYPE::kNone };
	bool            showLocationPopUp{ false };

	static Manager instance;
};

inline constinit Manager Manager::instance;
