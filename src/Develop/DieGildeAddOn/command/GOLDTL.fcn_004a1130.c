#include <string.h>

#include "client_method_registry.h"

int __cdecl fcn_004a4410(float* s1, float* s2, int idx, char* e);
int __cdecl fcn_00495960(void);
int __cdecl fcn_00495980(void);
int __cdecl fcn_00495990(void);
int __cdecl fcn_004959b0(void);
int __cdecl fcn_004959c0(void);
int __cdecl fcn_004959e0(void);
#ifdef REBREW_GOLD
int __cdecl fcn_00496020(int cmd, int dummy, int result);
#else
int __cdecl cm_TestCommandResult(int cmd, int dummy, char* result);
#endif
int __cdecl fcn_00495a10(void);
int __cdecl fcn_00495a20(void);
int __cdecl fcn_00495a40(void);
int __cdecl fcn_00495a50(void);
int __cdecl fcn_00495a70(void);
int __cdecl fcn_00495a80(void);
int __cdecl fcn_00495f80(void);
int __cdecl fcn_00495fe0(void);
int __cdecl fcn_00496480(void);
int __cdecl fcn_004964e0(void);
int __cdecl fcn_00496810(void);
int __cdecl fcn_00496ca0(void);
int __cdecl fcn_00496dc0(void);
int __cdecl fcn_00496e60(void);
int __cdecl fcn_00497000(void);
int __cdecl fcn_00497030(void);
int __cdecl fcn_004973a0(void);
int __cdecl fcn_004974c0(void);
int __cdecl fcn_004974d0(void);
int __cdecl fcn_004974e0(void);
int __cdecl fcn_00497670(void);
int __cdecl fcn_004976e0(void);
int __cdecl fcn_004978d0(void);
int __cdecl fcn_00497990(void);
int __cdecl fcn_00497e60(void);
int __cdecl fcn_00497ec0(void);
int __cdecl fcn_00498470(void);
int __cdecl fcn_00498570(void);
int __cdecl fcn_00498660(void);
int __cdecl fcn_00498670(void);
int __cdecl fcn_00498c90(void);
int __cdecl fcn_00498e00(void);
int __cdecl fcn_00498e10(void);
int __cdecl fcn_00498e20(void);
int __cdecl fcn_00498f40(void);
int __cdecl fcn_00498f50(void);
int __cdecl fcn_00498fb0(void);
int __cdecl fcn_00499000(void);
int __cdecl fcn_00499090(void);
int __cdecl fcn_004994c0(void);
int __cdecl fcn_004995b0(void);
int __cdecl fcn_00499640(void);
int __cdecl fcn_00499950(void);
int __cdecl PrepareBuergerrecht(void*, char*, int, char*);
int __cdecl fcn_00499ad0(void);
int __cdecl fcn_00499cc0(void);
int __cdecl fcn_00499db0(void);
int __cdecl fcn_00499dc0(void);
int __cdecl fcn_00499fe0(void);
int __cdecl fcn_0049a0c0(void);
int __cdecl fcn_0049a4b0(void);
int __cdecl fcn_0049a590(void);
int __cdecl fcn_0049a7b0(void);
int __cdecl fcn_0049a880(void);
int __cdecl fcn_0049aa80(void);
int __cdecl fcn_0049ab50(void);
int __cdecl fcn_0049ace0(void);
int __cdecl fcn_0049adb0(void);
int __cdecl fcn_0049b120(void);
int __cdecl fcn_0049b1f0(void);
int __cdecl fcn_0049b680(void);
int __cdecl fcn_0049b7c0(void);
int __cdecl fcn_0049ba30(void);
int __cdecl fcn_0049bb00(void);
int __cdecl fcn_0049bba0(void);
int __cdecl fcn_0049bbc0(void);
int __cdecl fcn_0049bd50(void);
int __cdecl fcn_0049bdf0(void);
int __cdecl fcn_0049be10(void);
int __cdecl ai_StartSpionage(void);
int __cdecl ai_RunSpionage(void);
int __cdecl ai_StartObjektKaufen(void);
int __cdecl ai_RunObjektKaufen(void);
int __cdecl ai_StartAblassKaufen(void);
int __cdecl ai_RunAblassKaufen(void);
int __cdecl ai_StartUseAmt(void);
int __cdecl ai_RunUseAmt(void);
int __cdecl ai_ScoreDrohen(void);
int __cdecl ai_StartDrohen(void);
int __cdecl ai_RunDrohen(void);
int __cdecl ai_ScorePamphlete(void);
int __cdecl ai_StartPamphlete(void);
int __cdecl ai_RunPamphlete(void);
int __cdecl ai_StartAnschwaerzen(void);
int __cdecl ai_RunAnschwaerzen(void);
int __cdecl ai_ScoreBeleidigen(void);
int __cdecl ai_StartBeleidigen(void);
int __cdecl ai_RunBeleidigen(void);
int __cdecl ai_ScoreErpressen(void);
int __cdecl ai_StartErpressen(void);
int __cdecl ai_RunErpressen(void);
int __cdecl ai_StartUsePrivs(void);
int __cdecl ai_RunUsePrivs(void);
int __cdecl ai_ScoreBuergermeister(void);
int __cdecl ai_StartBuergermeister(void);
#include "client_actions.h"
int __cdecl fcn_0049d7c0(void);
int __cdecl fcn_0049d920(void);
int __cdecl ai_StartBuergermeisterRathaus(void);
int __cdecl ai_RunBuergermeisterRathaus(void);
int __cdecl ai_StartBuergermeisterKerker(void);
int __cdecl ai_RunBuergermeisterKerker(void);
int __cdecl ai_StartBaumeister(void);
int __cdecl ai_RunBaumeister(void);
int __cdecl ai_ScoreDunkleEcke(void);
int __cdecl ai_StartDunkleEcke(void);
int __cdecl ai_RunDunkleEcke(void);
int __cdecl ai_StartKreditNehmen(void);
int __cdecl ai_RunKreditNehmen(void);
int __cdecl ai_ScoreChangeProfession(void);
int __cdecl ai_StartChangeProfession(void);
int __cdecl ai_RunChangeProfession(void);
int __cdecl ai_StartStammtisch(void);
int __cdecl ai_RunStammtisch(void);
int __cdecl ai_StartZunftPreismanipulation(void);
int __cdecl fcn_0049fa80(void);
int __cdecl ai_StartZunftAufruhr(void);
int __cdecl ai_RunZunftAufruhr(void);
int __cdecl ai_StartZunftLevel3(void);
int __cdecl ai_RunZunftLevel3(void);
int __cdecl ai_ScoreUpgradeZunft(void);
int __cdecl ai_StartUpgradeZunft(void);
int __cdecl ai_RunUpgradeZunft(void);
int __cdecl ai_ScoreBerufsausbildung(void);
int __cdecl ai_StartBerufsausbildung(void);
int __cdecl ai_RunBerufsausbildung(void);
int __cdecl ai_StartStudium(void);
int __cdecl ai_RunStudium(void);

/* ADDRESS: GOLDTL 0x004a1130 */
int __cdecl fcn_004a1130(char* e)
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
	d.type = 0x1;
	strcpy(d.name, "DummyUnversehrtheit");
	d.score = fcn_004a4410;
#ifdef REBREW_GOLD
	d.start = fcn_00496020;
#else
	d.start = cm_TestCommandResult;
#endif
	d.run = fcn_00495a10;
	d.flags = 0x1;
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
	d.type = 0x2;
	strcpy(d.name, "DummyBeruf");
	d.score = fcn_004a4410;
	d.start = fcn_00495a20;
	d.run = fcn_00495a40;
	d.flags = 0x1;
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
	d.type = 0x3;
	strcpy(d.name, "DummyVergnuegen");
	d.score = fcn_004a4410;
	d.start = fcn_00495a50;
	d.run = fcn_00495a70;
	d.flags = 0x1;
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
	d.type = 0x4;
	strcpy(d.name, "Bildung");
	d.score = fcn_004a4410;
	d.start = fcn_00495a80;
	d.run = fcn_00495f80;
	d.flags = 0x1;
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
	d.type = 0x5;
	strcpy(d.name, "Bildung (Beruf)");
	d.score = fcn_004a4410;
	d.start = fcn_00495fe0;
	d.run = fcn_00496480;
	d.flags = 0x1;
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
			jle short L6
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L6:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x6;
	strcpy(d.name, "DummyRechtschaffenheit");
	d.score = fcn_004a4410;
	d.start = fcn_00495960;
	d.run = fcn_00495980;
	d.flags = 0x1;
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
			jle short L7
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L7:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x7;
	strcpy(d.name, "DummySicherheit");
	d.score = fcn_004a4410;
	d.start = fcn_00495990;
	d.run = fcn_004959b0;
	d.flags = 0x1;
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
			jle short L8
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L8:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x8;
	strcpy(d.name, "DummyFortpflanzung");
	d.score = fcn_004a4410;
	d.start = fcn_004959c0;
	d.run = fcn_004959e0;
	d.flags = 0x1;
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
			jle short L9
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L9:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x9;
	strcpy(d.name, "Bestechung");
	d.score = fcn_004964e0;
	d.start = fcn_00496810;
	d.run = fcn_00496ca0;
	d.flags = 0x19;
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
			jle short L10
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L10:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0xa;
	strcpy(d.name, "Amtsbewerbung");
	d.score = fcn_00496dc0;
	d.start = fcn_00496e60;
	d.run = fcn_00497000;
	d.flags = 0x1b;
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
			jle short L11
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L11:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0xb;
	strcpy(d.name, "Objekt kaufen");
	d.score = fcn_004a4410;
	d.start = fcn_00497030;
	d.run = fcn_004973a0;
	d.flags = 0x1;
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
			jle short L12
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L12:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0xd;
	strcpy(d.name, "Objekt kaufen (AP)");
	d.score = fcn_004a4410;
	d.start = fcn_004974c0;
	d.run = fcn_004974d0;
	d.flags = 0x1;
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
			jle short L13
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L13:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0xe;
	strcpy(d.name, "Raum kaufen");
	d.score = fcn_004a4410;
	d.start = fcn_004974e0;
	d.run = fcn_00497670;
	d.flags = 0xff;
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
			jle short L14
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L14:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0xf;
	strcpy(d.name, "Repair Building");
	d.score = fcn_004a4410;
	d.start = fcn_004976e0;
	d.run = fcn_004978d0;
	d.flags = 0xff;
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
			jle short L15
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L15:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x10;
	strcpy(d.name, "Wohnsitz kaufen");
	d.score = fcn_004a4410;
	d.start = fcn_00497990;
	d.run = fcn_00497e60;
	d.flags = 0x3;
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
			jle short L16
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L16:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x11;
	strcpy(d.name, "Wohnsitz bauen");
	d.score = fcn_004a4410;
	d.start = fcn_00497ec0;
	d.run = fcn_00498470;
	d.flags = 0x3;
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
			jle short L17
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L17:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x12;
	strcpy(d.name, "Wohnsitz upgraden (Credits)");
	d.score = fcn_004a4410;
	d.start = fcn_00498570;
	d.run = fcn_00498660;
	d.flags = 0x3;
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
			jle short L18
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L18:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x13;
	strcpy(d.name, "Betrieb bauen");
	d.score = fcn_004a4410;
	d.start = fcn_00498670;
	d.run = fcn_00498c90;
	d.flags = 0x3;
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
			jle short L19
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L19:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x14;
	strcpy(d.name, "Betrieb upgraden (AP)");
	d.score = fcn_004a4410;
	d.start = fcn_00498e00;
	d.run = fcn_00498e10;
	d.flags = 0x3;
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
			jle short L20
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L20:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x15;
	strcpy(d.name, "Betrieb upgraden (Credits)");
	d.score = fcn_004a4410;
	d.start = fcn_00498e20;
	d.run = fcn_00498f40;
	d.flags = 0x3;
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
			jle short L21
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L21:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x16;
	strcpy(d.name, "Medicus ausfsuchen");
	d.score = fcn_004a4410;
	d.start = fcn_00498f50;
	d.run = fcn_00498fb0;
	d.flags = 0x3b;
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
			jle short L22
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L22:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x17;
	strcpy(d.name, "Sabotieren");
	d.score = fcn_00499000;
	d.start = fcn_00499090;
	d.run = fcn_004994c0;
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
			jle short L23
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L23:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x18;
	strcpy(d.name, "Verpruegeln");
	d.score = fcn_004995b0;
	d.start = fcn_00499640;
	d.run = fcn_00499950;
	d.flags = 0x1c9;
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
			jle short L24
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L24:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x19;
	strcpy(d.name, "Buergerrecht");
	d.score = fcn_004a4410;
	d.start = PrepareBuergerrecht;
	d.run = fcn_00499ad0;
	d.flags = 0x1b;
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
			jle short L25
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L25:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x1a;
	strcpy(d.name, "ApsSparen");
	d.score = fcn_004a4410;
	d.start = fcn_00499cc0;
	d.run = fcn_00499db0;
	d.flags = 0x1;
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
			jle short L26
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L26:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x1b;
	strcpy(d.name, "UseObject (Military)");
	d.score = fcn_004a4410;
	d.start = fcn_00499dc0;
	d.run = fcn_00499fe0;
	d.flags = 0x3;
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
			jle short L27
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L27:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x1c;
	strcpy(d.name, "UseObject (Ansehen)");
	d.score = fcn_004a4410;
	d.start = fcn_0049a0c0;
	d.run = fcn_0049a4b0;
	d.flags = 0x19;
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
			jle short L28
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L28:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x1d;
	strcpy(d.name, "UseObject (APS)");
	d.score = fcn_004a4410;
	d.start = fcn_0049a590;
	d.run = fcn_0049a7b0;
	d.flags = 0x39;
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
			jle short L29
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L29:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x1e;
	strcpy(d.name, "UseObject (Bildung)");
	d.score = fcn_004a4410;
	d.start = fcn_0049a880;
	d.run = fcn_0049aa80;
	d.flags = 0x3b;
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
			jle short L30
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L30:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x1f;
	strcpy(d.name, "UseObject (Unversehrtheit)");
	d.score = fcn_004a4410;
	d.start = fcn_0049ab50;
	d.run = fcn_0049ace0;
	d.flags = 0x3f;
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
			jle short L31
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L31:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x20;
	strcpy(d.name, "UseObject (Dynastie)");
	d.score = fcn_004a4410;
	d.start = fcn_0049adb0;
	d.run = fcn_0049b120;
	d.flags = 0x17;
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
			jle short L32
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L32:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x21;
	strcpy(d.name, "UseObject (Gemeinheit)");
	d.score = fcn_004a4410;
	d.start = fcn_0049b1f0;
	d.run = fcn_0049b680;
	d.flags = 0xc9;
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
			jle short L33
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L33:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x22;
	strcpy(d.name, "UseObject (Sicherheit)");
	d.score = fcn_004a4410;
	d.start = fcn_0049b7c0;
	d.run = fcn_0049ba30;
	d.flags = 0x39;
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
			jle short L34
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L34:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x23;
	strcpy(d.name, "Use Parfuem");
	d.score = fcn_0049bb00;
	d.start = fcn_0049bba0;
	d.run = fcn_0049bbc0;
	d.flags = 0xff;
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
			jle short L35
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L35:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x24;
	strcpy(d.name, "Use Trank");
	d.score = fcn_0049bd50;
	d.start = fcn_0049bdf0;
	d.run = fcn_0049be10;
	d.flags = 0xff;
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
			jle short L36
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L36:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x25;
	strcpy(d.name, "Spionage");
	d.score = fcn_004a4410;
	d.start = ai_StartSpionage;
	d.run = ai_RunSpionage;
	d.flags = 0x69;
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
			jle short L37
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L37:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0xc;
	strcpy(d.name, "Objekt Kaufen (Markt)");
	d.score = fcn_004a4410;
	d.start = ai_StartObjektKaufen;
	d.run = ai_RunObjektKaufen;
	d.flags = 0xff;
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
			jle short L38
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L38:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x26;
	strcpy(d.name, "Ablass Kaufen");
	d.score = fcn_004a4410;
	d.start = ai_StartAblassKaufen;
	d.run = ai_RunAblassKaufen;
	d.flags = 0x39;
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
			jle short L39
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L39:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x27;
	strcpy(d.name, "UseAmt");
	d.score = fcn_004a4410;
	d.start = ai_StartUseAmt;
	d.run = ai_RunUseAmt;
	d.flags = 0xff;
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
			jle short L40
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L40:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x28;
	strcpy(d.name, "Drohen");
	d.score = ai_ScoreDrohen;
	d.start = ai_StartDrohen;
	d.run = ai_RunDrohen;
	d.flags = 0x5d;
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
			jle short L41
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L41:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x29;
	strcpy(d.name, "Pamphlete");
	d.score = ai_ScorePamphlete;
	d.start = ai_StartPamphlete;
	d.run = ai_RunPamphlete;
	d.flags = 0x5d;
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
			jle short L42
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L42:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x2a;
	strcpy(d.name, "Anschwaerzen");
	d.score = fcn_004a4410;
	d.start = ai_StartAnschwaerzen;
	d.run = ai_RunAnschwaerzen;
	d.flags = 0x39;
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
			jle short L43
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L43:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x2b;
	strcpy(d.name, "Beleidigen");
	d.score = ai_ScoreBeleidigen;
	d.start = ai_StartBeleidigen;
	d.run = ai_RunBeleidigen;
	d.flags = 0xc9;
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
			jle short L44
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L44:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x2c;
	strcpy(d.name, "Erpressen");
	d.score = ai_ScoreErpressen;
	d.start = ai_StartErpressen;
	d.run = ai_RunErpressen;
	d.flags = 0xc9;
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
			jle short L45
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L45:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x2d;
	strcpy(d.name, "UsePrivs");
	d.score = fcn_004a4410;
	d.start = ai_StartUsePrivs;
	d.run = ai_RunUsePrivs;
	d.flags = 0xff;
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
			jle short L46
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L46:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x2e;
	strcpy(d.name, "Buergermeister");
	d.score = ai_ScoreBuergermeister;
	d.start = ai_StartBuergermeister;
	d.run = RunBuergermeister;
	d.flags = 0x39;
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
			jle short L47
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L47:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x2f;
	strcpy(d.name, "Baumeister");
	d.score = fcn_004a4410;
	d.start = ai_StartBaumeister;
	d.run = ai_RunBaumeister;
	d.flags = 0x3b;
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
			jle short L48
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L48:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x30;
	strcpy(d.name, "Buergermeister upgrade");
	d.score = fcn_004a4410;
	d.start = fcn_0049d7c0;
	d.run = fcn_0049d920;
	d.flags = 0x39;
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
			jle short L49
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L49:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x31;
	strcpy(d.name, "Buergermeister Rathaus");
	d.score = fcn_004a4410;
	d.start = ai_StartBuergermeisterRathaus;
	d.run = ai_RunBuergermeisterRathaus;
	d.flags = 0x39;
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
			jle short L50
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L50:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x3c;
	strcpy(d.name, "Buergermeister Kerker");
	d.score = fcn_004a4410;
	d.start = ai_StartBuergermeisterKerker;
	d.run = ai_RunBuergermeisterKerker;
	d.flags = 0x39;
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
			jle short L51
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L51:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x32;
	strcpy(d.name, "Dunkle Ecke");
	d.score = ai_ScoreDunkleEcke;
	d.start = ai_StartDunkleEcke;
	d.run = ai_RunDunkleEcke;
	d.flags = 0x69;
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
			jle short L52
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L52:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x33;
	strcpy(d.name, "Kredit Nehmen");
	d.score = fcn_004a4410;
	d.start = ai_StartKreditNehmen;
	d.run = ai_RunKreditNehmen;
	d.flags = 0x7;
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
			jle short L53
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L53:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x34;
	strcpy(d.name, "Change Profession");
	d.score = ai_ScoreChangeProfession;
	d.start = ai_StartChangeProfession;
	d.run = ai_RunChangeProfession;
	d.flags = 0x7;
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
			jle short L54
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L54:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x35;
	strcpy(d.name, "Stammtisch");
	d.score = fcn_004a4410;
	d.start = ai_StartStammtisch;
	d.run = ai_RunStammtisch;
	d.flags = 0x19;
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
			jle short L55
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L55:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x36;
	strcpy(d.name, "Zunft Preismanipulation");
	d.score = fcn_004a4410;
	d.start = ai_StartZunftPreismanipulation;
	d.run = fcn_0049fa80;
	d.flags = 0x3;
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
			jle short L56
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L56:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x37;
	strcpy(d.name, "Zunft Aufruhr");
	d.score = fcn_004a4410;
	d.start = ai_StartZunftAufruhr;
	d.run = ai_RunZunftAufruhr;
	d.flags = 0x43;
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
			jle short L57
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L57:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x38;
	strcpy(d.name, "Zunft Level 3");
	d.score = fcn_004a4410;
	d.start = ai_StartZunftLevel3;
	d.run = ai_RunZunftLevel3;
	d.flags = 0x4b;
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
			jle short L58
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L58:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x39;
	strcpy(d.name, "Upgrade Zunft");
	d.score = ai_ScoreUpgradeZunft;
	d.start = ai_StartUpgradeZunft;
	d.run = ai_RunUpgradeZunft;
	d.flags = 0x1b;
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
			jle short L59
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L59:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x3a;
	strcpy(d.name, "Berufsausbildung");
	d.score = ai_ScoreBerufsausbildung;
	d.start = ai_StartBerufsausbildung;
	d.run = ai_RunBerufsausbildung;
	d.flags = 0x1f;
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
			jle short L60
			rep stosb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep stosd
		L60:
			add ecx, ebx
			rep stosb
		}
	}
	d.type = 0x3b;
	strcpy(d.name, "Studium");
	d.score = fcn_004a4410;
	d.start = ai_StartStudium;
	d.run = ai_RunStudium;
	d.flags = 0x13;
	return am_RegisterMethod(&d, e) != 0;
}
