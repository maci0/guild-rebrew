#include <string.h>
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"

extern int gm_GameTime;
extern int g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern unsigned char g_7f4ca2[];
extern unsigned int g_7f4ca4[];

int __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl d2_RunCityScrollMapDialog(int, int*, char*, int, int);
int __cdecl cm_SendCopyEntityData(char*);
int __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl cm_AppendPacketFieldDelta(unsigned char, unsigned char, unsigned short, char*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);

static __inline void fill0_5dc5e0(char* dst, int size)
{
	char* d;
	int n;

	n = size;
	d = dst;
	__asm {
		mov edi, d
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
}

#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x005dc5e0 */
int __cdecl gm_UseSmokeOrUnkendunkEffect(char* entity, int* target)
{
	char buf[0xf8];
	char* pkt;
	unsigned int ent;
	char kind;
	int res;

	res = 0;
	if (*(char*) (entity + 2) == 6) {
		int set[0x14];
		char name[0x100];

		memset(set, 0, sizeof(set));
		memset(&set[7], 0xff, 0x20);
		io_FormatTextBuffer(name, 0x9b);
		set[0] = 1;
		set[1] = -1;
		set[4] = 6;
		set[2] = 0xa0744300;
		set[3] = 1;
		pkt = (char*) d2_RunCityScrollMapDialog(1, set, name, 0, 0);
		if (pkt == 0) {
			goto done;
		}
		fill0_5dc5e0(buf, 0xf8);
		*(int*) (buf + 0x28) = gm_GameTime;
		*(int*) (buf + 8) = *(int*) (entity + 4);
		*(int*) (buf + 0x30) = g_7f4c08;
		*(int*) (buf + 0x2c) = g_7f4c04;
		*(char*) (buf + 4) = 0x76;
		*(int*) (buf + 0xc) = -1;
		*(unsigned short*) (buf + 0x34) = g_7f4c0c;
		*(char*) (buf + 0x36) = 0x0a;
		*(int*) (buf + 0x58) = *(int*) (pkt + 1);
		*(unsigned short*) (buf + 0x6e) = 0x178;
		cm_SendCopyEntityData(buf); fill0_5dc5e0(buf, 0xf8);
	} else {
		pkt = (char*) gm_StartFilteredEntitySearch(1, 1, target[1]);
		if (pkt == 0) {
			goto done;
		}
		fill0_5dc5e0(buf, 0xf8);
		*(int*) (buf + 0x28) = gm_GameTime;
		*(int*) (buf + 8) = *(int*) (entity + 4);
		*(int*) (buf + 0x30) = g_7f4c08;
		*(int*) (buf + 0x2c) = g_7f4c04;
		*(char*) (buf + 4) = 0x76;
		*(int*) (buf + 0xc) = -1;
		*(unsigned short*) (buf + 0x34) = g_7f4c0c;
		*(char*) (buf + 0x36) = 0x0a;
		*(int*) (buf + 0x58) = *(int*) (pkt + 1);
		*(unsigned short*) (buf + 0x6e) = 0x178;
		cm_SendCopyEntityData(buf); fill0_5dc5e0(buf, 0xf8);
	}

	*(int*) (buf + 0x28) = gm_GameTime;
	*(int*) (buf + 8) = *(int*) (entity + 4);
	*(int*) (buf + 0x30) = g_7f4c08;
	*(int*) (buf + 0x2c) = g_7f4c04;
	*(char*) (buf + 4) = 0x77;
	*(int*) (buf + 0xc) = -1;
	*(unsigned short*) (buf + 0x34) = g_7f4c0c;
	*(char*) (buf + 0x36) = 1;
	*(int*) (buf + 0x58) = *(int*) (pkt + 1);
	cm_SendCopyEntityData(buf);

	cm_BeginPacketFieldDelta((char*) *target, *(int*) (*target + 2));
	cm_AppendPacketFieldDelta(4, 1, (char*) *target + 0x25 - g_aed32c, pkt + 1);
	cm_RequestChangeAttribute();
	cm_RequestChangeBits(*(int*) (pkt + 1), 0x5a, 2, 0x20, 0);

	if (*(unsigned short*) (pkt + 0x27) != 0xffff) {
		ent = *(unsigned short*) (pkt + 0x27);
		kind = g_7f4ca2[ent * 0x21c];
		if (kind == 6 || kind == 7) {
			char text[0x800];

			io_FormatTextBuffer(text, 0xff2, pkt);
			ent = *(unsigned short*) (pkt + 0x27);
			he_PostEntityMessage(*(int*) (&g_7f4ca4[ent * 0x87]), -1, text, 0, 0x5fb, 0);
		}
	}
	res = 1;
done:
	return res;
}
