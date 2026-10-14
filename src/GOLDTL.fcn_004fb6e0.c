#include "client_types.h"
extern Rec24_99f5a0 g_99f5a0;

void __cdecl fcn_004c6a00(void* msg);

extern pos14_7f4c00 g_7f4c00;

/* ADDRESS: GOLD 0x004f9190 */
/* ADDRESS: GOLDTL 0x004fb650 */
void __cdecl fcn_004fb650(int a1, int a2, int a3, int a4)
{
	int buf[10];

	{
		int len;
		char* p;

		len = 0x24;
		p = (char*) buf;
		/* block-copy prelude, see docs/codegen-walls.md section 6b */
		__asm {
			mov edi, p
			mov esi, offset g_99f5a0
			mov ebx, len
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L1
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		L1:
			add ecx, ebx
			rep movsb
		}
	}
	buf[9] = 0x696e6974;
	buf[0] = a1;
	buf[1] = 0;
	buf[2] = (*(int*)&g_7f4c00);
	buf[3] = a2;
	buf[4] = a3;
	buf[5] = 0;
	buf[6] = a4;
	buf[7] = 0;
	buf[8] = 0;
	fcn_004c6a00(buf);
}

/* ADDRESS: GOLDTL 0x004fb6e0 */
void __cdecl fcn_004fb6e0(void)
{
	int buf[10];

	{
		int len;
		char* p;

		len = 0x24;
		p = (char*) buf;
		/* block-copy prelude, see docs/codegen-walls.md section 6b */
		__asm {
			mov edi, p
			mov esi, offset g_99f5a0
			mov ebx, len
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L1
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		L1:
			add ecx, ebx
			rep movsb
		}
	}
	buf[0] = 1;
	buf[9] = 0x656e626c;
	fcn_004c6a00(buf);
}

/* ADDRESS: GOLDTL 0x004fb740 */
void __cdecl fcn_004fb740(void)
{
	int buf[10];

	{
		int len;
		char* p;

		len = 0x24;
		p = (char*) buf;
		/* block-copy prelude, see docs/codegen-walls.md section 6b */
		__asm {
			mov edi, p
			mov esi, offset g_99f5a0
			mov ebx, len
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L1
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		L1:
			add ecx, ebx
			rep movsb
		}
	}
	buf[0] = 0;
	buf[9] = 0x6473626c;
	fcn_004c6a00(buf);
}

/* ADDRESS: GOLD 0x004f9710 */
/* ADDRESS: GOLDTL 0x004fbc90 */
int __cdecl fcn_004fbc90(unsigned int* msg)
{
	int len;

	switch (msg[9]) {
	case 0x656e626c:
		g_99f5a0.head = 1;
		break;
	case 0x6473626c:
		g_99f5a0.head = 0;
		break;
	case 0x696e6974:
	case 0x73657420:
		len = 0x24;
		/* block-copy prelude, see docs/codegen-walls.md section 6b */
		__asm {
			mov edi, offset g_99f5a0
			mov esi, msg
			mov ebx, len
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L1
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		L1:
			add ecx, ebx
			rep movsb
		}
		break;
	default:
		return 0;
	}
	return 1;
}
