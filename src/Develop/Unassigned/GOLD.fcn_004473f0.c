extern char* g_5fb5b0;
void __cdecl fcn_0043c7a0(void*);
void __cdecl fcn_00455750(void*);
void __cdecl fcn_0043ff90(void*);
void __cdecl fcn_0045da90(void*);
void __cdecl m_FreeTracked(void*);
void __cdecl fcn_00448910(void);

/* ADDRESS: GOLD 0x004473f0 */
void __cdecl fcn_004473f0(void)
{
	unsigned int* p;
	char* copyDst;
	char* copySrc;
	int copyCount;
	int offset;

	while (*(void**) 0xfc52f0 != (void*) 0xfc2700)
		fcn_0043c7a0(*(void**) 0xfc52f0);
	while (*(void**) 0xfb98f4 != (void*) 0xfb9280)
		fcn_00455750(*(void**) 0xfb98f4);
	if (*(void**) 0x633738 != 0) {
		fcn_0043ff90(*(void**) 0x633738);
		*(void**) 0x633738 = 0;
	}
	if (*(void**) 0x633dd4 != 0) {
		fcn_0045da90(*(void**) 0x633dd4);
		*(void**) 0x633dd4 = 0;
	}
	if (*(void**) (g_5fb5b0 + 0x3c8) != 0) {
		m_FreeTracked(*(void**) (g_5fb5b0 + 0x3c8));
		*(void**) (g_5fb5b0 + 0x3c8) = 0;
	}
	*(void**) 0xfc52f0 = (void*) 0xfc2700;
	*(void**) 0xfc28f4 = (void*) 0xfc5100;
	*(int*) 0x633b1c = 0;
	*(int*) 0x633b20 = 0;
	*(int*) 0x633b24 = 0;
	*(float*) 0x5fcc74 = 200.0f;
	*(float*) 0x5fcc78 = 200.0f;
	*(float*) 0x5fcc7c = 200.0f;
	*(float*) 0x5fcc80 = 200.0f;
	for (p = (unsigned int*) 0xfba968; (int) p < 0xfba9b0; p += 3) {
		p[-2] = 0;
		p[0] = 0;
		p[-1] = 0;
	}
	copyCount = 0x48;
	for (p = (unsigned int*) 0xfba9c4; (int) p < 0xfbac64; p += 0x18) {
		p[-1] = *(unsigned int*) 0x5fcc78;
		p[0] = *(unsigned int*) 0x5fcc7c;
		p[1] = *(unsigned int*) 0x5fcc80;
		p[2] = *(unsigned int*) 0x633b1c;
		p[3] = *(unsigned int*) 0x633b20;
		p[4] = *(unsigned int*) 0x633b24;
		copyDst = (char*) (p + 5);
		copySrc = (char*) 0xfba960;
		__asm {
			mov edi, copyDst
			mov esi, copySrc
			mov ebx, copyCount
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short ResetCopyTail
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		ResetCopyTail:
			add ecx, ebx
			rep movsb
		}
	}
	*(int*) 0x6338c4 = 0;
	*(int*) 0x6338c0 = 0;
	*(int*) 0x6338bc = 0;
	*(int*) 0x6338b8 = 0;
	fcn_00448910();
	*(int*) 0x63349c = 0;
	offset = *(int*) 0x633444 * 0x3e0;
	*(int*) 0x5fb5c0 = 4;
	*(int*) 0x5fb5c4 = 0xf;
	*(int*) (offset + 0xfd7c24) = 0;
	*(int*) (offset + 0xfd7c20) = 0;
	*(char*) (offset + 0xfd7f75) = 0;
	*(char*) (offset + 0xfd7f74) = 0;
	*(char*) (offset + 0xfd7ba0) = 0;
}
