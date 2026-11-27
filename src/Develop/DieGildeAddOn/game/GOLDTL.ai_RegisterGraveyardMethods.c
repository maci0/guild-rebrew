#include <string.h>

#include "client_method_registry.h"

int __cdecl fcn_004a4410(float* s1, float* s2, int idx, char* e);
int __cdecl ai_StartGraveyardOwner(void);
int __cdecl ai_RunGraveyardOwner(void);
int __cdecl ai_StartHandleGrave(void);
int __cdecl ai_RunHandleGrave(void);
int __cdecl ai_StartUseSeance(void);
int __cdecl ai_RunUseSeance(void);

/* ADDRESS: GOLDTL 0x004901d0 */
int __cdecl ai_RegisterGraveyardMethods(char* e)
{
	AM_METHOD d;

	{
		char* p;
		int len;

		len = sizeof(d);
		p = (char*) &d;
		/* block-fill prelude, see docs/codegen-walls.md section 6b */
		__asm {
			mov edi, p
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
	d.type = 0x3d;
	strcpy(d.name, "Graveyard Owner");
	d.score = fcn_004a4410;
	d.start = ai_StartGraveyardOwner;
	d.run = ai_RunGraveyardOwner;
	d.flags = 0x1c3;
	if (am_RegisterMethod(&d, e) == 0) {
		return 0;
	}
	{
		char* p;
		int len;

		len = sizeof(d);
		p = (char*) &d;
		/* block-fill prelude, see docs/codegen-walls.md section 6b */
		__asm {
			mov edi, p
			mov ebx, len
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L2
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L2:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x3e;
	strcpy(d.name, "Handle Grave");
	d.score = fcn_004a4410;
	d.start = ai_StartHandleGrave;
	d.run = ai_RunHandleGrave;
	d.flags = 1;
	if (am_RegisterMethod(&d, e) == 0) {
		return 0;
	}
	{
		char* p;
		int len;

		len = sizeof(d);
		p = (char*) &d;
		/* block-fill prelude, see docs/codegen-walls.md section 6b */
		__asm {
			mov edi, p
			mov ebx, len
			xor eax, eax
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L3
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L3:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x3f;
	strcpy(d.name, "Use Seance");
	d.score = fcn_004a4410;
	d.start = ai_StartUseSeance;
	d.run = ai_RunUseSeance;
	d.flags = 1;
	return am_RegisterMethod(&d, e) != 0;
}
