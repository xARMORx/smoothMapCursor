#include "main.h"

LRESULT AsiPlugin::wndProc(const decltype(wndProcHook)& hook, HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (uMsg == WM_MOUSEWHEEL && *(char*)(0xBA68A5) == 5) {
		int delta = GET_WHEEL_DELTA_WPARAM(wParam);
		float v103 = 320.0 - *(float*)(0xBA67B0);
		float v115 = 224.0 - *(float*)(0xBA67B4);	
		float v6 = 1.0 / *(float*)(0xBA67AC);
		float v82 = v6 * v115;
		float v117 = v103 * v6;

		if (delta > 0)
			*(float*)(0xBA67AC) >= 1100.0 ? *(float*)(0xBA67AC) = 1100.0 : *(float*)(0xBA67AC) = *(float*)(0xBA67AC) + 50;
		else
			*(float*)(0xBA67AC) <= 300.0 ? *(float*)(0xBA67AC) = 300.0 : *(float*)(0xBA67AC) = *(float*)(0xBA67AC) - 50;

		*(float*)(0xBA67B0) = *(float*)(0xBA67B0) - (v117 * *(float*)(0xBA67AC) - v103);
		*(float*)(0xBA67B4) = *(float*)(0xBA67B4) - (v82 * *(float*)(0xBA67AC) - v115);
	}

	return hook.get_trampoline()(hwnd, uMsg, wParam, lParam);
}

void AsiPlugin::CTimer__Update(const decltype(CTimerHook)& hook) {
	static bool init{};
	if (!init) {
		*(float*)(*(uint32_t*)(0x57808D)) = -1.0f; // mouseY patch
		*(float*)(*(uint32_t*)(0x57813D)) = 1.0f; // mouseX patch

		memset(reinterpret_cast<void*>(0x57762B), 0x90, 2); // wheel up nop
		memset(reinterpret_cast<void*>(0x57795E), 0x90, 2); // wheel down nop

		wndProcHook.set_cb([this](auto&...args) { return AsiPlugin::wndProc(args...); });
		wndProcHook.install();
		init = { true };
	}

	return hook.get_trampoline()();
}

AsiPlugin::AsiPlugin() {
	CTimerHook.set_cb([this](auto&...args) { return AsiPlugin::CTimer__Update(args...); });
	CTimerHook.install();
}

AsiPlugin::~AsiPlugin() {
	CTimerHook.remove();
	wndProcHook.remove();

	// return original bytes
	memcpy(reinterpret_cast<void*>(0x57762B), "\x75\x1E", 2);
	memcpy(reinterpret_cast<void*>(0x57795E), "\x75\x1E", 2);

	// return original value to mouse pos 
	*(float*)(*(uint32_t*)(0x57808D)) = -14.0f;
	*(float*)(*(uint32_t*)(0x57813D)) = 14.0f;
}
