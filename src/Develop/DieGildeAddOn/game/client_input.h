#ifndef CLIENT_INPUT_H
#define CLIENT_INPUT_H

#include <windows.h>
#include <dinput.h>

/* Inferred subsystem header. These are the observed COM interface prefixes,
 * not complete allocations or complete DirectInput vtables. The used methods
 * have the same ABI in Gold's DirectInput 7 and TL's DirectInput 8 interfaces.
 * The factories and versions remain distinct. */
typedef struct INPUT_DEVICE INPUT_DEVICE;
typedef struct INPUT_SYSTEM INPUT_SYSTEM;

/* Observed device vtable prefix: 0x38 bytes on x86. */
typedef struct INPUT_DEVICE_VTABLE {
    HRESULT (__stdcall* QueryInterface)(INPUT_DEVICE*, REFIID, void**);
    ULONG (__stdcall* AddRef)(INPUT_DEVICE*);
    ULONG (__stdcall* Release)(INPUT_DEVICE*);
    HRESULT (__stdcall* GetCapabilities)(INPUT_DEVICE*, LPDIDEVCAPS);
    HRESULT (__stdcall* EnumObjects)(INPUT_DEVICE*, LPDIENUMDEVICEOBJECTSCALLBACKA, void*, DWORD);
    HRESULT (__stdcall* GetProperty)(INPUT_DEVICE*, REFGUID, LPDIPROPHEADER);
    HRESULT (__stdcall* SetProperty)(INPUT_DEVICE*, REFGUID, LPCDIPROPHEADER);
    HRESULT (__stdcall* Acquire)(INPUT_DEVICE*);
    HRESULT (__stdcall* Unacquire)(INPUT_DEVICE*);
    HRESULT (__stdcall* GetDeviceState)(INPUT_DEVICE*, DWORD, void*);
    HRESULT (__stdcall* GetDeviceData)(INPUT_DEVICE*, DWORD, LPDIDEVICEOBJECTDATA, LPDWORD, DWORD);
    HRESULT (__stdcall* SetDataFormat)(INPUT_DEVICE*, LPCDIDATAFORMAT);
    HRESULT (__stdcall* SetEventNotification)(INPUT_DEVICE*, HANDLE);
    HRESULT (__stdcall* SetCooperativeLevel)(INPUT_DEVICE*, HWND, DWORD);
} INPUT_DEVICE_VTABLE;

/* Observed input-system vtable prefix: 0x10 bytes on x86. */
typedef struct INPUT_SYSTEM_VTABLE {
    HRESULT (__stdcall* QueryInterface)(INPUT_SYSTEM*, REFIID, void**);
    ULONG (__stdcall* AddRef)(INPUT_SYSTEM*);
    ULONG (__stdcall* Release)(INPUT_SYSTEM*);
    HRESULT (__stdcall* CreateDevice)(INPUT_SYSTEM*, REFGUID, INPUT_DEVICE**, IUnknown*);
} INPUT_SYSTEM_VTABLE;

/* Each recovered interface view is one 4-byte vtable pointer. */
struct INPUT_DEVICE { INPUT_DEVICE_VTABLE* vtbl; };
struct INPUT_SYSTEM { INPUT_SYSTEM_VTABLE* vtbl; };

extern HWND io_InputHwnd;
extern HWND io_InputHwnd;
extern HANDLE io_MouseEventHandle;
extern HANDLE io_MouseEventHandle;

extern INPUT_DEVICE* io_MouseDevice;
extern INPUT_DEVICE* io_MouseDevice;
extern INPUT_DEVICE* io_KeyboardDevice;
extern INPUT_DEVICE* io_KeyboardDevice;
extern INPUT_SYSTEM* io_DirectInput;
extern INPUT_SYSTEM* io_DirectInput;

int __cdecl io_AcquireKeyboard(int acquire);
int __cdecl io_AcquireMouse(int acquire);
#endif
