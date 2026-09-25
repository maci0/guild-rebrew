#include "../Units/Error/error.h"
#include "../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
#include "server_internal.h"

void __cdecl srv_LogWinsockError(int err_code);
void __cdecl srv_InitBuildingTypeTable(void);

extern char s_Unknown_winsock_error_u_10028bdc[];
extern char s_WSANOTINITIALISED_100293b0[];
extern char s_WSAENETDOWN_10029380[];
extern char s_WSAEFAULT_1002931c[];
extern char s_WSAENOTCONN_100292f0[];
extern char s_WSAEINTR_100292a4[];
extern char s_WSAEINPROGRESS_1002921c[];
extern char s_WSAENETRESET_10029194[];
extern char s_WSAENOTSOCK_10029164[];
extern char s_WSAEOPNOTSUPP_10029068[];
extern char s_WSAESHUTDOWN_10028fc8[];
extern char s_WSAEWOULDBLOCK_10028f6c[];
extern char s_WSAEMSGSIZE_10028f10[];
extern char s_WSAEINVAL_10028e3c[];
extern char s_WSAECONNABORTED_10028da0[];
extern char s_WSAETIMEDOUT_10028d24[];
extern char s_WSAECONNRESET_10028bf8[];

// FUNCTION: GOLDTL 0x4e7810
// SIZE: 372
// FUNCTION: SERVER 0x1000b040

// srv_InitBuildingTypeTable

#pragma optimize("y", off)
void __cdecl srv_InitBuildingTypeTable(void)
{
	char* slot_cursor;
	int i;
	volatile int n;

	n = 0x3f0;
	/*
	 * TODO: replace this inline-asm fill with proper C once a spelling is
	 * found; no msvc6 C memset/memcpy form emits the prelude
	 * (docs/msvc6-allocator.md Finding 19).
	 */
	__asm {
		mov edi, offset g_office_slots
		mov ebx, n
		xor eax, eax
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep stosb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep stosd
	L1:
		add ecx, ebx
		rep stosb
	}
	i = 0;
	slot_cursor = g_office_slots + 4;
	do {
		*(slot_cursor - 4) = (char) i;
		*(int*) slot_cursor = -1;
		*(int*) (slot_cursor + 0x10) = -1;
		slot_cursor += 0x18;
		i++;
	} while ((int) slot_cursor < (int) (g_office_slots + 0x3f4));

	*(unsigned char*) (g_office_slots + 0x8) = 0x1;
	*(unsigned char*) (g_office_slots + 0x20) = 0x1;
	*(unsigned char*) (g_office_slots + 0x38) = 0x2;
	*(unsigned char*) (g_office_slots + 0x50) = 0x3;
	*(unsigned char*) (g_office_slots + 0x68) = 0x4;
	*(unsigned char*) (g_office_slots + 0x80) = 0x4;
	*(unsigned char*) (g_office_slots + 0x98) = 0x5;
	*(unsigned char*) (g_office_slots + 0xb0) = 0x6;
	*(unsigned char*) (g_office_slots + 0xc8) = 0x7;
	*(unsigned char*) (g_office_slots + 0xe0) = 0x7;
	*(unsigned char*) (g_office_slots + 0xf8) = 0x8;
	*(unsigned char*) (g_office_slots + 0x110) = 0x9;
	*(unsigned char*) (g_office_slots + 0x128) = 0xa;
	*(unsigned char*) (g_office_slots + 0x140) = 0xb;
	*(unsigned char*) (g_office_slots + 0x158) = 0xc;
	*(unsigned char*) (g_office_slots + 0x170) = 0xd;
	*(unsigned char*) (g_office_slots + 0x188) = 0xe;
	*(unsigned char*) (g_office_slots + 0x1a0) = 0xf;
	*(unsigned char*) (g_office_slots + 0x1b8) = 0x10;
	*(unsigned char*) (g_office_slots + 0x1d0) = 0x11;
	*(unsigned char*) (g_office_slots + 0x1e8) = 0x12;
	*(unsigned char*) (g_office_slots + 0x200) = 0x13;
	*(unsigned char*) (g_office_slots + 0x218) = 0x14;
	*(unsigned char*) (g_office_slots + 0x230) = 0x15;
	*(unsigned char*) (g_office_slots + 0x248) = 0x16;
	*(unsigned char*) (g_office_slots + 0x260) = 0x17;
	*(unsigned char*) (g_office_slots + 0x278) = 0x18;
	*(unsigned char*) (g_office_slots + 0x290) = 0x19;
	*(unsigned char*) (g_office_slots + 0x2a8) = 0x1a;
	*(unsigned char*) (g_office_slots + 0x2c0) = 0x1b;
	*(unsigned char*) (g_office_slots + 0x2d8) = 0x1c;
	*(unsigned char*) (g_office_slots + 0x2f0) = 0x1d;
	*(unsigned char*) (g_office_slots + 0x308) = 0x1e;
	*(unsigned char*) (g_office_slots + 0x320) = 0x1f;
	*(unsigned char*) (g_office_slots + 0x338) = 0x20;
	*(unsigned char*) (g_office_slots + 0x350) = 0x21;
	*(unsigned char*) (g_office_slots + 0x368) = 0x22;
	*(unsigned char*) (g_office_slots + 0x380) = 0x23;
	*(unsigned char*) (g_office_slots + 0x398) = 0x24;
	*(unsigned char*) (g_office_slots + 0x3b0) = 0x25;
	*(unsigned char*) (g_office_slots + 0x3c8) = 0x26;
	*(unsigned char*) (g_office_slots + 0x3e0) = 0x27;
}
#pragma optimize("", on)
