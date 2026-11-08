#include <string.h>

#include "client_method_registry.h"

int __cdecl fcn_004a4410(float* s1, float* s2, int idx, char* e);
int __cdecl ai_StartBlutrache(void);
int __cdecl ai_RunBlutrache(void);
int __cdecl ai_StartVerfluchen(void);
int __cdecl ai_RunVerfluchen(void);
int __cdecl ai_StartTheater(void);
int __cdecl ai_RunTheater(void);
int __cdecl ai_StartEhrerbietung(void);
int __cdecl ai_RunEhrerbietung(void);

/* ADDRESS: GOLDTL 0x004abff0 */
int __cdecl fcn_004abff0(char* e)
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
	d.type = 0x44;
	strcpy(d.name, "Blutrache");
	d.score = fcn_004a4410;
	d.start = ai_StartBlutrache;
	d.run = ai_RunBlutrache;
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
	d.type = 0x45;
	strcpy(d.name, "Verfluchen");
	d.score = fcn_004a4410;
	d.start = ai_StartVerfluchen;
	d.run = ai_RunVerfluchen;
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
	d.type = 0x46;
	strcpy(d.name, "Theater");
	d.score = fcn_004a4410;
	d.start = ai_StartTheater;
	d.run = ai_RunTheater;
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
			jle short L4
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L4:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x47;
	strcpy(d.name, "Ehrerbietung");
	d.score = fcn_004a4410;
	d.start = ai_StartEhrerbietung;
	d.run = ai_RunEhrerbietung;
	d.flags = 3;
	return am_RegisterMethod(&d, e) != 0;
}
