#include <string.h>

#include "client_method_registry.h"

int __cdecl fcn_004a4410(float* s1, float* s2, int idx, char* e);
int __cdecl ai_StartDomizil(void);
int __cdecl ai_RunDomizil(void);
int __cdecl ai_StartSecretRoom(void);
int __cdecl ai_RunSecretRoom(void);
int __cdecl ai_StartCannonTower(void);
int __cdecl ai_RunCannonTower(void);
int __cdecl ai_StartSculpture(void);
int __cdecl ai_RunSculpture(void);
int __cdecl ai_StartAlchemistryItems(void);
int __cdecl ai_RunAlchemistryItems(void);

/* ADDRESS: GOLDTL 0x0048f110 */
int __cdecl ai_RegisterDomizilMethods(char* e)
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
	d.type = 0x40;
	strcpy(d.name, "Build Domizil");
	d.score = fcn_004a4410;
	d.start = ai_StartDomizil;
	d.run = ai_RunDomizil;
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
	d.type = 0x41;
	strcpy(d.name, "UseSecretRoom");
	d.score = fcn_004a4410;
	d.start = ai_StartSecretRoom;
	d.run = ai_RunSecretRoom;
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
	d.type = 0x42;
	strcpy(d.name, "UseCannonTower");
	d.score = fcn_004a4410;
	d.start = ai_StartCannonTower;
	d.run = ai_RunCannonTower;
	d.flags = 0x1c1;
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
	d.type = 0x43;
	strcpy(d.name, "BuildSculpture");
	d.score = fcn_004a4410;
	d.start = ai_StartSculpture;
	d.run = ai_RunSculpture;
	d.flags = 3;
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
			jle short L5
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L5:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x48;
	strcpy(d.name, "UseAlchemistryItems");
	d.score = fcn_004a4410;
	d.start = ai_StartAlchemistryItems;
	d.run = ai_RunAlchemistryItems;
	d.flags = 0x1c3;
	return am_RegisterMethod(&d, e) != 0;
}
