#include "client_types.h"
extern Rec24_99f5a0 g_99f5a0;

void __cdecl cm_SendRandomEventState(void* msg);

extern pos14_7f4c00 gm_GameTime;

/* ADDRESS: GOLDTL 0x004fb650 */
void __cdecl gm_InitDisasterState(int enabled, int scaleA, int scaleB, int duration)
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
	buf[0] = enabled;
	buf[1] = 0;
	buf[2] = (*(int*)&gm_GameTime);
	buf[3] = scaleA;
	buf[4] = scaleB;
	buf[5] = 0;
	buf[6] = duration;
	buf[7] = 0;
	buf[8] = 0;
	cm_SendRandomEventState(buf);
}

/* ADDRESS: GOLDTL 0x004fb6e0 */
void __cdecl gm_EnableDisasterState(void)
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
	cm_SendRandomEventState(buf);
}

/* ADDRESS: GOLDTL 0x004fb740 */
void __cdecl gm_DisableDisasterState(void)
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
	cm_SendRandomEventState(buf);
}

/* ADDRESS: GOLDTL 0x004fbc90 */
int __cdecl gm_DispatchDisasterCommand(unsigned int* msg)
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
