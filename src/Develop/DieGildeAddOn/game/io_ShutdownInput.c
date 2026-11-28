


#include "Develop/DieGildeAddOn/game/client_input.h"























/* ADDRESS: GOLDDE 0x00410770 */
void __cdecl io_ShutdownInput(void)
{
	io_InputHwnd = 0;
	io_AcquireMouse(0);
	io_AcquireKeyboard(0);
	if (io_KeyboardDevice != 0) {
		io_KeyboardDevice->vtbl->Release(io_KeyboardDevice);
		io_MouseDevice = 0;
	} else if (io_MouseDevice != 0) {
		io_MouseDevice->vtbl->Release(io_MouseDevice);
		io_MouseDevice = 0;
	}
	if (io_DirectInput != 0) {
		io_DirectInput->vtbl->Release(io_DirectInput);
		io_DirectInput = 0;
	}
	if (io_MouseEventHandle != 0) {
		CloseHandle(io_MouseEventHandle);
		io_MouseEventHandle = 0;
	}
}
