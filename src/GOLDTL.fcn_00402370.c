// FUNCTION: GOLDTL 0x00402370

#include <stdio.h>
#include <string.h>

#pragma intrinsic(memcpy, strcmp, strcpy)

// SIZE 0x10
typedef struct {
	short family;
	unsigned short port;
	unsigned long addr;
	char zero[8];
} SockAddr;

// SIZE 0x80
typedef struct {
	char name[0x10];
	char info[0x6c];
	int size;
} Host;

__declspec(dllimport) unsigned long __stdcall timeGetTime(void);
__declspec(dllimport) int __stdcall WSAStartup(unsigned short, void*);
__declspec(dllimport) int __stdcall WSAGetLastError(void);
__declspec(dllimport) int __stdcall WSACleanup(void);
__declspec(dllimport) unsigned short __stdcall htons(unsigned short);
__declspec(dllimport) int __stdcall socket(int, int, int);
__declspec(dllimport) int __stdcall bind(int, const void*, int);
__declspec(dllimport) int __stdcall ioctlsocket(int, long, unsigned long*);
__declspec(dllimport) int __stdcall recvfrom(int, char*, int, int, void*, int*);
__declspec(dllimport) char* __stdcall inet_ntoa(unsigned long);
__declspec(dllimport) int __stdcall closesocket(int);

/* Listens on the UDP port for server announcements until the timeout
 * expires or max hosts are listed; returns the host count. */
int __cdecl fcn_00402370(unsigned short port, unsigned long timeout, Host* out, int max)
{
	char wsa[0x190];
	char buf[0x100];
	SockAddr from;
	SockAddr local;
	unsigned long start;
	int fromlen;
	unsigned long nb;
	int s;
	int count;
	int i;
	Host* h;

	nb = 1;
	start = timeGetTime();
	count = 0;
	if (max <= 0) {
		return -2;
	}
	{
		int len;

		len = max << 7;
		/* Block-fill prelude no msvc6 C spelling emits (docs/codegen-walls.md 6b). */
		__asm {
			mov edi, out
			mov ebx, len
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
	}
	if (WSAStartup(2, wsa) == -1) {
		fprintf(stderr, "WSAStartup failed with error %d\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}
	local.family = 2;
	local.addr = 0;
	local.port = htons(port);
	s = socket(2, 2, 0);
	if (s == -1) {
		WSACleanup();
		return -1;
	}
	if (bind(s, &local, 0x10) == -1) {
		WSACleanup();
		return -1;
	}
	if (ioctlsocket(s, 0x8004667e, &nb) == -1) {
		WSACleanup();
		return -1;
	}
	h = out;
	while (timeGetTime() - start < timeout && count < max) {
		fromlen = 0x10;
		if ((unsigned int) recvfrom(s, buf, 0x100, 0, &from, &fromlen) < 6) {
			continue;
		}
		if (*(short*) (buf + 4) != 0x6a) {
			continue;
		}
		if (*(short*) (buf + 2) != 1 && *(short*) (buf + 2) != 4) {
			continue;
		}
		if (*(short*) buf != 1) {
			continue;
		}
		for (i = 0; i < count; i++) {
			if (strcmp(out[i].name, inet_ntoa(from.addr)) == 0) {
				goto next;
			}
		}
		strcpy(h->name, inet_ntoa(from.addr));
		if (*(short*) (buf + 2) == 1) {
			memcpy(h->info, buf, 0x2a);
			h->size = 0x3f;
		}
		else {
			memcpy(h->info, buf, 0x6a);
			h->size = 0x7f;
		}
		count++;
		h++;
	next:
		;
	}
	closesocket(s);
	WSACleanup();
	return count;
}
