#pragma optimize("y", off)
extern char* g_6b7d68;
extern int g_6b7d74;
extern char* g_6b7d78;
extern char g_679010[]; /* %lang */
extern char g_679018[]; /* sbs_Compile */

int __cdecl fcn_004230e0(char*);
char* __cdecl fcn_00423960(void);
int __cdecl fcn_00423b20(char*, char*, int);
int __cdecl fcn_00423b80(char*);
int __cdecl fcn_00423bf0(char*, char*);
int __cdecl fcn_00423ce0(char*);
int __cdecl fcn_004246c0(void);
int __cdecl fcn_004246e0(void);
int __cdecl fcn_00424700(char*);
char* __cdecl m_alloc(char*, char*);
int __cdecl fcn_00425980(char*);

/* ADDRESS: GOLDTL 0x004248a0 */
int __cdecl fcn_004248a0(char* name)
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
	fcn_004230e0(0);
	if (g_6b7d68 != 0) {
		n1 = fcn_004246c0();
		n2 = fcn_004246e0();
		if (fcn_00425980(name) == -1) {
			return -1;
		}
		text = fcn_00423960();
		root = (int) m_alloc(text, g_679018);
		if (root != 0) {
	g_6b7d78 = (char*) root;
	g_6b7d74 += (int) text;
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
	strncpy(g_6b7d78, g_6b7d68, 0x32);
	offset = root + step;
	*(int*) (g_6b7d78 + 0x134) = n1 + n2;
	*(char**) (g_6b7d78 + 0x138) = (char*) offset;
	offset = ((n1 + n2) << 6) + step;
			if (n1 != 0) {
				node = *(char**) (g_6b7d68 + 0x38);
				if (node != 0) {
					i = 0;
					if (result == 0) {
						do {
							*(char*) (*(char**) (g_6b7d78 + 0x138) + i + 0x36) = 1;
							*(int*) (*(char**) (g_6b7d78 + 0x138) + i) = offset;
							*(int*) (*(char**) (g_6b7d78 + 0x138) + i + 0x38) = 0;
							*(int*) (*(char**) (g_6b7d78 + 0x138) + i + 0x3c) = 0;
							p = (char*) (root + offset);
							result = fcn_00423b20(node,
							    *(char**) (g_6b7d78 + 0x138) + i + 4, 0x32);
							if (result == 0) {
								*(int*) (p + 4) = *(int*) (node + 0x100);
								*(char*) p = (char) fcn_00423b80(node);
								if (*(char*) p != 0) {
									*(char**) (p + 8) = (char*) (root + offset + 0xc);
									strcpy(buf, node);
									if ((m = strstr(buf, g_679010)) != 0) {
										*m = 0;
										strcat(buf, name);
										strcat(buf, &node[5 + (m - buf)]);
									}
									result = fcn_00423bf0(buf, p);
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
						} while (node != 0);
					}
				}
			}
			if (n2 != 0) {
				node = *(char**) (g_6b7d68 + 0x3c);
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
						*(int*) p = fcn_00424700(node);
						*(int*) (p + 8) = fcn_00423ce0(node);
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
										*(char*) (*(int*) (p + 4) + i) = (char) fcn_00423b80(child);
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
											result = fcn_00423bf0(buf,
											    (char*) (*(int*) (p + 4) + i));
										} else {
											result = -1;
										}
										child = *(char**) (child + 0x104);
										i += 0xc;
									} while (child != 0);
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
				fcn_004230e0(0);
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
