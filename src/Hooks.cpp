#include "Hooks.h"
#include "Manager.h"
#include "RE.h"

namespace Hooks
{
	struct MapMarkerData__GetLocationName
	{
		static const char* thunk(RE::MapMarkerData* a_mapMarkerData)
		{
			Manager::GetSingleton()->SendLocationPopup(a_mapMarkerData);

			return nullptr;
		}
		static inline REL::Relocation<decltype(thunk)> func;

		static void Install()
		{
			REL::Relocation<std::uintptr_t> target{ RELOCATION_ID(39663, 40750), OFFSET(0x1CC, 0x1EC) };  // PlayerCharacter::UpdateNearbyMapMarkers
			stl::write_thunk_call<MapMarkerData__GetLocationName>(target.address());
		}
	};

	struct SendHUDMessage__ShowLocationName
	{
		static void thunk(const char*)
		{
			return;
		}
		static inline REL::Relocation<decltype(thunk)> func;

		static void Install()
		{
			REL::Relocation<std::uintptr_t> target{ RELOCATION_ID(39663, 40750), OFFSET(0x1D4, 0x1F4) };  // PlayerCharacter::UpdateNearbyMapMarkers
			stl::write_thunk_call<SendHUDMessage__ShowLocationName>(target.address());
		}
	};

	struct PushNotification
	{
		static void thunk(RE::BSTArray<RE::HUDNotifications::Notification>& a_array, std::uint32_t a_index, std::uint32_t a_capacity, RE::HUDNotifications::Notification& a_notification)
		{
			if (a_notification.type == RE::HUD_MESSAGE_TYPE::kLocationDiscovery && Manager::GetSingleton()->ShouldMuteJingle()) {
				a_notification.sound = "";
			}

			func(a_array, a_index, a_capacity, a_notification);
		}
		static inline REL::Relocation<decltype(thunk)> func;

		static void Install()
		{
			REL::Relocation<std::uintptr_t> target{ RELOCATION_ID(50721, 51653), OFFSET(0x559, 0x4E6) };  // HUDMenu::Process
			stl::write_thunk_call<PushNotification>(target.address());
		}
	};

	void Install()
	{
		Manager::GetSingleton()->LoadSettings();
		
		MapMarkerData__GetLocationName::Install();
		SendHUDMessage__ShowLocationName::Install();
		PushNotification::Install();
	}
}
