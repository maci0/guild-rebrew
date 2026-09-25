#include <string.h>

typedef struct Deed {
	unsigned char type;
	char name[0x23];
	void* score;
	void* start;
	void* run;
	char pad30[0x60];
	int flags;
} Deed;
// SIZE 0x94

int __cdecl fcn_00494ed0(Deed* d, char* e);
int __cdecl fcn_004a4410(float* s1, float* s2, int idx, char* e);
int __cdecl fcn_0048d6c0(void);
int __cdecl fcn_0048d910(void);
int __cdecl fcn_0048da10(void);
int __cdecl fcn_0048e050(void);
int __cdecl fcn_0048e5b0(void);
int __cdecl fcn_0048e780(void);
int __cdecl fcn_0048e850(void);
int __cdecl fcn_0048eaa0(void);
int __cdecl fcn_0048eba0(void);
int __cdecl fcn_0048ef30(void);

// FUNCTION: GOLD 0x48fb60
// SIZE: 817
// FUNCTION: GOLDTL 0x0048f110
// SIZE: 817
int __cdecl fcn_0048f110(char* e)
{
	Deed d;

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
	d.start = fcn_0048d6c0;
	d.run = fcn_0048d910;
	d.flags = 0x1c3;
	if (fcn_00494ed0(&d, e) == 0) {
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
	d.start = fcn_0048da10;
	d.run = fcn_0048e050;
	d.flags = 0x1c3;
	if (fcn_00494ed0(&d, e) == 0) {
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
	d.start = fcn_0048e5b0;
	d.run = fcn_0048e780;
	d.flags = 0x1c1;
	if (fcn_00494ed0(&d, e) == 0) {
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
	d.start = fcn_0048e850;
	d.run = fcn_0048eaa0;
	d.flags = 3;
	if (fcn_00494ed0(&d, e) == 0) {
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
	d.start = fcn_0048eba0;
	d.run = fcn_0048ef30;
	d.flags = 0x1c3;
	return fcn_00494ed0(&d, e) != 0;
}
