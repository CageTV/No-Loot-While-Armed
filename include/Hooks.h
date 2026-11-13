#pragma once

namespace Hooks {
    void Install();

    struct InputHook {
		static void thunk(RE::BSTEventSource<RE::InputEvent*>* a_dispatcher, RE::InputEvent* const* a_event);
		static inline REL::Relocation<decltype(thunk)> func;
		static bool ProcessInput(RE::InputEvent* event);
	};

    template <typename ContainerType>
    class ActivateHook {
        public:
        static void Install();
    private:
        static bool thunk(ContainerType* a_this,
                                       RE::TESObjectREFR* a_targetRef, 
                                        RE::TESObjectREFR* a_activatorRef, 
                                        std::uint8_t a_arg3, 
                                        RE::TESBoundObject* a_object, 
                                        std::int32_t a_targetCount);
        static inline REL::Relocation<decltype(thunk)> func;
    };

	inline std::atomic_bool blocked = false;

    // Milliseconds on a steady clock (see NowMs()).
    // sheathe_started_ms: when AutoActions() asked the engine to sheathe; 0 = nothing pending. The input hook gives up waiting after kSheatheTimeoutMs.
    // ql_take_veto_until_ms: until then QuickLoot's "take item" is vetoed (it fires by itself right after we re-open its menu).
    inline std::atomic<std::int64_t> sheathe_started_ms{0};
    inline std::atomic<std::int64_t> ql_take_veto_until_ms{0};
    inline constexpr std::int64_t kSheatheTimeoutMs = 2500;
    inline constexpr std::int64_t kQuickLootTakeVetoMs = 400;
    inline std::int64_t NowMs() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    }
    void ReleaseStuckSheathe();
    inline RE::TESObjectREFRPtr crosshair_ref = nullptr;
    inline RE::TESObjectREFRPtr saved_ref = nullptr;
    inline const SKSE::CrosshairRefEvent my_event{nullptr};
    inline SKSE::CrosshairRefEvent my_event2{nullptr};
    
    bool OnActivate();
}