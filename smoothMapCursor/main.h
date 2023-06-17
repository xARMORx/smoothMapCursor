#ifndef _MAIN_H_
#define _MAIN_H_

#include <Windows.h>
#include <memory>
#include <kthook/kthook.hpp>

using CTimer__UpdatePrototype = void(__cdecl*)();
using wndProcPrototype = LRESULT(__stdcall*)(HWND, UINT, WPARAM, LPARAM);

class AsiPlugin{
public:
	kthook::kthook_simple<CTimer__UpdatePrototype> CTimerHook{ 0x561B10 };
	kthook::kthook_simple<wndProcPrototype> wndProcHook{ 0x747EB0 };

	void CTimer__Update(const decltype(CTimerHook)& hook);
	LRESULT wndProc(const decltype(wndProcHook)& hook, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	explicit AsiPlugin();
	virtual ~AsiPlugin();
} AsiPlugin;

#endif // !_MAIN_H_