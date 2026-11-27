#pragma optimize("y", off)
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* g_6b7d78;
extern char g_679010[]; /* %lang */
extern char g_679018[]; /* sbs_Compile */

int __cdecl sb_ReleaseSampleBank(char*);
char* __cdecl sbs_CalcCompiledSize(void);
int __cdecl sbs_ExtractBaseName(char*, char*, int);
int __cdecl sbs_GetAudioFormat(char*);
int __cdecl sbs_ReadSampleFile(char*, char*);
int __cdecl sbs_CalcSetDataSize(char*);
int __cdecl sbs_CountRootSamples(void);
int __cdecl sbs_CountSets(void);
int __cdecl sbs_CountSetEntries(char*);
char* __cdecl m_alloc(char*, char*);
int __cdecl sbs_UpdateSampleSizes(char*);

/* ADDRESS: GOLDTL 0x004248a0 */
int __cdecl sbs_Compile(char* name)
{
	char buf[0x100];
	char* p;
	char* node;
	char* child;
	char* text;
	char* m;
	int result;
	int n1;
	int step;
	int offset;
	int count;
	int root;
	int n2;
	int sum;
	int i;

	result = 0;
	count = 0;
	sb_ReleaseSampleBank(0);
	if (sbs_BankManager != 0) {
		n1 = sbs_CountRootSamples();
		n2 = sbs_CountSets();
		if (sbs_UpdateSampleSizes(name) == -1) {
			return -1;
		}
		text = sbs_CalcCompiledSize();
		root = (int) m_alloc(text, g_679018);
		if (root != 0) {
	g_6b7d78 = (char*) root;
	MemUsed += (int) text;
	step = 0x144;
	/* Reviewed original operand-homed fill (inline fill/copy block). */
	__asm {
		mov edi, g_6b7d78
		mov ebx, step
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
	strncpy(g_6b7d78, sbs_BankManager, 0x32);
	offset = root + step;
	*(int*) (g_6b7d78 + 0x134) = n1 + n2;
	*(char**) (g_6b7d78 + 0x138) = (char*) offset;
	offset = ((n1 + n2) << 6) + step;
			if (n1 != 0) {
				node = *(char**) (sbs_BankManager + 0x38);
				if (node != 0) {
					i = 0;
					if (result == 0) {
						do {
							*(char*) (*(char**) (g_6b7d78 + 0x138) + i + 0x36) = 1;
							*(int*) (*(char**) (g_6b7d78 + 0x138) + i) = offset;
							*(int*) (*(char**) (g_6b7d78 + 0x138) + i + 0x38) = 0;
							*(int*) (*(char**) (g_6b7d78 + 0x138) + i + 0x3c) = 0;
							p = (char*) (root + offset);
							result = sbs_ExtractBaseName(node,
							    *(char**) (g_6b7d78 + 0x138) + i + 4, 0x32);
							if (result == 0) {
								*(int*) (p + 4) = *(int*) (node + 0x100);
								*(char*) p = (char) sbs_GetAudioFormat(node);
								if (*(char*) p != 0) {
									*(char**) (p + 8) = (char*) (root + offset + 0xc);
									strcpy(buf, node);
									if ((m = strstr(buf, g_679010)) != 0) {
										*m = 0;
										strcat(buf, name);
										strcat(buf, &node[5 + (m - buf)]);
									}
									result = sbs_ReadSampleFile(buf, p);
									if (result == 0) {
										offset = offset + *(int*) (node + 0x100) + 0xc;
									}
								} else {
									result = -1;
								}
							}
							count++;
							i += 0x40;
							node = *(char**) (node + 0x104);
						} while (node != 0 && result == 0);
					}
				}
			}
			if (n2 != 0) {
				node = *(char**) (sbs_BankManager + 0x3c);
				if (node != 0) {
					n2 = count << 6;
					do {
						if (result != 0) {
							break;
						}
						*(char*) (*(char**) (g_6b7d78 + 0x138) + n2 + 0x36) = 2;
						*(int*) (*(char**) (g_6b7d78 + 0x138) + n2) = offset;
						*(int*) (*(char**) (g_6b7d78 + 0x138) + n2 + 0x38) = 0;
						*(int*) (*(char**) (g_6b7d78 + 0x138) + n2 + 0x3c) = 0;
						p = (char*) (root + offset);
						*(int*) p = sbs_CountSetEntries(node);
						*(int*) (p + 8) = sbs_CalcSetDataSize(node);
						strncpy(*(char**) (g_6b7d78 + 0x138) + n2 + 4, node, 0x32);
						offset += 0xc;
						if (*(int*) p != 0) {
							*(int*) (p + 4) = root + offset;
							sum = 0;
							child = *(char**) (node + 0x38);
							if (child != 0) {
								i = 0;
								if (result == 0) {
									do {
										*(char*) (*(int*) (p + 4) + i) = (char) sbs_GetAudioFormat(child);
										if (*(char*) (*(int*) (p + 4) + i) != 0) {
											*(int*) (*(int*) (p + 4) + i + 4) = *(int*) (child + 0x100);
											*(int*) (*(int*) (p + 4) + i + 8) = root + *(int*) p * 12 + sum + offset;
											sum += *(int*) (child + 0x100);
											strcpy(buf, child);
											if ((m = strstr(buf, g_679010)) != 0) {
												*m = 0;
												strcat(buf, name);
												strcat(buf, &child[5 + (m - buf)]);
											}
											result = sbs_ReadSampleFile(buf,
											    (char*) (*(int*) (p + 4) + i));
										} else {
											result = -1;
										}
										child = *(char**) (child + 0x104);
										i += 0xc;
									} while (child != 0 && result == 0);
								}
							}
							offset += sum + *(int*) p * 12;
						}
						n2 += 0x40;
						node = *(char**) (node + 0x3c);
					} while (node != 0);
				}
			}
			if (result == -1) {
				sb_ReleaseSampleBank(0);
			} else {
				result = 0;
			}
		} else {
			result = 0;
		}
	} else {
		result = -1;
	}
	return result;
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_6b72b4[2756];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_6b72b4[2700];
#endif
