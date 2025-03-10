#pragma once

#include "RE/B/BSTArray.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTSingleton.h"
#include "RE/B/BSTSmartPointer.h"

namespace RE
{
	class InputEvent;
	class MenuEventHandler;
	class MenuModeChangeEvent;
	struct ClickHandler;
	struct ConsoleOpenHandler;
	struct DirectionHandler;
	struct FavoritesHandler;
	struct MenuOpenHandler;
	struct QuickSaveLoadHandler;
	struct ScreenshotHandler;

	class MenuControls :
		public BSTEventSink<InputEvent*>,         // 00
		public BSTSingletonSDM<MenuControls>,     // 10
		public BSTEventSink<MenuModeChangeEvent>  // 08
	{
	public:
		struct QueuedReg
		{
		public:
			QueuedReg(MenuEventHandler* a_handler, bool a_add);
			~QueuedReg() = default;

			// members
			MenuEventHandler* handler;  // 00
			bool              add;      // 08
			std::uint8_t      pad08;    // 09
			std::uint16_t     pad09;    // 0A
			std::uint32_t     pad0A;    // 0C
		};
		static_assert(sizeof(QueuedReg) == 0x10);

		~MenuControls() override;  // 00

		// override (BSTEventSink<InputEvent*>)
		BSEventNotifyControl ProcessEvent(InputEvent* const* a_event, BSTEventSource<InputEvent*>* a_eventSource) override;  // 01

		// override (BSTEventSink<MenuModeChangeEvent>)
		BSEventNotifyControl ProcessEvent(const MenuModeChangeEvent* a_event, BSTEventSource<MenuModeChangeEvent>* a_eventSource) override;  // 01

		static MenuControls* GetSingleton();

		void                         AddHandler(MenuEventHandler* a_handler);
		[[nodiscard]] constexpr bool InBeastForm() const noexcept { return beastForm; }
		void                         RegisterHandler(MenuEventHandler* a_handler);
		void                         RemoveHandler(MenuEventHandler* a_handler);
		bool                         QueueScreenshot();
		void                         UnregisterHandler(MenuEventHandler* a_handler);

		// members
		std::uint8_t                pad11;                 // 11
		std::uint16_t               pad12;                 // 12
		std::uint32_t               pad14;                 // 14
		BSTArray<MenuEventHandler*> handlers;              // 18
		BSTArray<QueuedReg>         regBuffer;             // 30
		ClickHandler*               clickHandler;          // 48
		DirectionHandler*           directionHandler;      // 50
		ConsoleOpenHandler*         consoleOpenHandler;    // 58
		QuickSaveLoadHandler*       quickSaveLoadHandler;  // 60
		MenuOpenHandler*            menuOpenHandler;       // 68
		FavoritesHandler*           favoritesHandler;      // 70
		ScreenshotHandler*          screenshotHandler;     // 78
#ifdef SKYRIMVR
		std::uint64_t occlusionCullingToggleHandler;  // 80
#endif
		bool          isProcessing;  // 80
		bool          beastForm;     // 81
		bool          remapMode;     // 82
		std::uint8_t  unk83;         // 83
		std::uint32_t unk84;         // 84
	private:
		KEEP_FOR_RE()
	};
	static_assert(offsetof(MenuControls, handlers) == 0x18);

#ifndef SKYRIMVR
	static_assert(sizeof(MenuControls) == 0x88);
	static_assert(offsetof(MenuControls, remapMode) == 0x82);
#else
	static_assert(offsetof(MenuControls, remapMode) == 0x8A);
	static_assert(sizeof(MenuControls) == 0x90);
#endif

}
