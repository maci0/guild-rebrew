


extern int g_7749f8[];

int* __cdecl m_alloc(int size, char* tag);
void __cdecl fcn_00580cf0(int);
int __cdecl sb_LoadLocalizedSampleBank(char*, int);

#pragma optimize("y", off)
/* ADDRESS: GOLD 0x00578760 */
int* __cdecl d2_InitTutorialMainIntro(void)
{
	int* intro;
	char* fdest;
	int flen;

	intro = m_alloc(0x74, "FTInitMainIntro");
	fdest = (char*) intro;
	if (intro == 0) {
		fcn_00580cf0(0);
		return 0;
	}
	flen = 0x74;
	__asm {
		mov edi, fdest
		mov ebx, flen
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
	intro[0] = 0;
	intro[1] = 0x494e5452;
	intro[2] = 4;
	intro[3] = 0x3f24;
	intro[4] = (int) "TUTORIAL_MAIN_INTRO";
	intro[5] = 0;
	intro[6] = 0;
	intro[7] = 0;
	intro[8] = 0;
	intro[0xb] = -1;
	intro[0xc] = 0x8e;
	intro[0xd] = 0;
	intro[0xe] = 0;
	intro[0x10] = 0;
	intro[0x11] = 0;
	intro[0x12] = 0xb;
	intro[0x1a] = 0;
	intro[0x1b] = 0;
	intro[0x1c] = 0;
	(*(int*)g_7749f8) = sb_LoadLocalizedSampleBank("TUTORIAL_INTRO_OUTRO.sbf", 0);
	return intro;
}
#pragma optimize("", on)
