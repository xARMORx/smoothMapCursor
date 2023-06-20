#ifndef _MAIN_H_
#define _MAIN_H_

#include <Windows.h>
#include <memory>
#include <kthook/kthook.hpp>\

using CHud__DrawRadarPrototype = void(__cdecl*)();

class AsiPlugin{
public:
	kthook::kthook_simple<CHud__DrawRadarPrototype> CHudHook{ 0x58A330 };
	kthook::kthook_simple<WNDPROC> wndProcHook{};

	void CHud__DrawRadar(const decltype(CHudHook)& hook);
	explicit AsiPlugin();
	virtual ~AsiPlugin();
} AsiPlugin;

#endif // !_MAIN_H_