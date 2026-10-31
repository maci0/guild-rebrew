int __cdecl fcn_0046f2c0();
int __cdecl fcn_0046f740();
int __cdecl fcn_00471af0();
int __cdecl fcn_00471b60();
int __cdecl fcn_00471e30();
int __cdecl fcn_00472250();
int __cdecl d2_SetForm();
int __cdecl d2_SetOverlayAnimation();
int __cdecl fcn_004927c0();
int __cdecl fcn_00492950();
int __cdecl fcn_00492d60();
int __cdecl fcn_00492e50();
int __cdecl fcn_00493000();
int __cdecl fcn_004c51a0();
int __cdecl gm_LookupEntityRecordById();
int __cdecl fcn_0050b710();
int __cdecl io_AppendText();
int __cdecl io_FormatTextBuffer();
int __cdecl fcn_00532ef0();
int __cdecl fcn_005340f0();
int __cdecl fcn_005373e0();
int __cdecl fcn_005a0960();
int __cdecl fcn_005a0cd0();
int __cdecl fcn_005a1130();
int __cdecl fcn_005ca560();
int __cdecl fcn_005ca740();
int __cdecl gm_LookupEntityRecordById();
int __cdecl fcn_00591990();

/* ADDRESS: GOLDTL 0x005a1130 */
unsigned int __cdecl fcn_005a1130(char* a0, int a1)
{
	char* self;
	char* entity;
	char* other;
	char* p;
	char* q;
	char* dst;
	char* src;
	char work[0x18];
	int i;
	int count;
	int room;
	unsigned int mode;
	unsigned int value;

	self = a0;
	d2_SetForm(self, 2);
	fcn_0046f2c0(*(int*) 0x772514, 1);
	d2_SetForm(self, 3);
	fcn_0046f2c0(*(int*) 0x772514, 1);

	if (*(char*) (*(int*) (self + 0xc) + 2) != 6) {
		d2_SetForm(self, 3);
		io_AppendText((char*) (*(int*) (self + 0xc) + 0x30), (char*) 0x6a9694);
		count = *(unsigned char*) (self + 0x10);
		for (i = 0; i < count; i++) {
			fcn_0046f740(0x1c + (i & 7) * 0x3a, 0x1d + ((i < 8) ? 0x29 : 0x00),
				*(unsigned char*) (self + 0x18 + i) + 0x75a, *(int*) 0x772514);
		}
	}
	else {
		d2_SetForm(self, 2);
		io_AppendText((char*) (*(int*) (self + 0xc) + 0x30), (char*) 0x6a9694);
		count = *(unsigned char*) (self + 0x10);
		for (i = 0; i < count; i++) {
			fcn_0046f740(0x1c + (i & 7) * 0x3a, 0x1d + ((i < 8) ? 0x29 : 0x00),
				*(unsigned char*) (self + 0x18 + i) + 0x75a, *(int*) 0x772514);
		}
	}

	if (*(char*) (*(int*) (self + 0x30) + 2) != 6) {
		d2_SetForm(self, 2);
		io_AppendText((char*) (*(int*) (self + 0x30) + 0x30), (char*) 0x6a9694);
		count = *(unsigned char*) (self + 0x34);
		for (i = 0; i < count; i++) {
			fcn_0046f740(0x1c + (i & 7) * 0x3a, 0x1d + ((i < 8) ? 0x29 : 0x00),
				*(unsigned char*) (self + 0x18 + i) + 0x75a, *(int*) 0x772514);
		}
	}
	else {
		d2_SetForm(self, 2);
		io_AppendText((char*) (*(int*) (self + 0x30) + 0x30), (char*) 0x6a9694);
		count = *(unsigned char*) (self + 0x34);
		for (i = 0; i < count; i++) {
			fcn_0046f740(0x1c + (i & 7) * 0x3a, 0x1d + ((i < 8) ? 0x29 : 0x00),
				*(unsigned char*) (self + 0x18 + i) + 0x75a, *(int*) 0x772514);
		}
	}

	d2_SetForm(self, 2);
	fcn_0046f2c0(*(int*) 0x772514, 1);

	if (((*(int*) (self + 8) != 5) || (*(char*) (*(int*) (self + 0xc) + 2) != 6))
		&& ((*(int*) (self + 8) != 6) || (*(char*) (*(int*) (self + 0x30) + 2) != 6))) {
		a1 = *(int*) (self + 0x54) / 2;
		room = 0x1888;
	}
	else {
		a1 = *(int*) (self + 0x54);
		room = 0x1887;
	}
	fcn_005ca740();

	if (*(int*) 0x1052de0 == 0) {
		return 0xffffffff;
	}
	entity = (char*) (*(int*) 0x772514 * 0x3cc);
	if (*(int*) (entity + 0x10161d0) == 0) {
		return 0xffffffff;
	}

	for (i = 0; i < 0x17d; i++) {
		work[i] = 0;
	}

	if (0x4800 <= room) {
		p = (char*) room;
		dst = work;
		do {
			*dst++ = *p;
		} while (*p++ != 0);
	}
	else {
		p = *(char**) (room * 4 + 0x14a5320);
		if (p == 0) {
			return 0xffffffff;
		}
		i = 0;
		while (p[i] != 0) {
			i++;
		}
		if (0x17c1 <= i) {
			return 0xffffffff;
		}
		fcn_005ca560(work, p, i + 1);
	}

	mode = *(int*) 0x772554;
	value = 0;
	dst = work;
	while (*dst != 0) {
		dst++;
	}
	if (dst != work) {
		for (i = 0; i <= 0x17d0; i++) {
			if (work[i] == '%' || work[i] == '$' || work[i] == '{') {
				int next = i + 1;
				if (work[i + 1] >= '0' && work[i + 1] <= '9') {
					next = i + 2;
				}
				src = (char*) work[next];
				i = next;
				if ((unsigned int) ((int) src - 0x25) <= 0x52) {
					return fcn_00591990();
				}
			}
			i++;
			if (work[i] == 0) {
				break;
			}
		}
	}

	i = 0;
	while (*(char*) (*(int*) (*(int*) 0x772514 * 0x3cc + 0x1015f7c) + i) != 0) {
		i++;
	}
	if (0x17d0 <= i - 2) {
		return 0xffffffff;
	}

	fcn_005ca560((char*) (*(int*) 0x772514 * 0x3cc + 0x1015f7c),
		work, i + 1);
	*(int*) (*(int*) 0x772514 * 0x3cc + 0x10161b8) = 2;
	value = *(unsigned int*) (*(int*) 0x772514 * 0x3cc + 0x1015f6c);
	if (a1 == 0) {
		return value;
	}
	*(int*) 0x772554 = 1;
	other = (char*) *(int*) (0x1015ea0 + 0x50 + *(int*) (*(int*) 0x772514 * 0x3cc + 0x10161bc) * 0x2f4);
	if (other == 0) {
		*(int*) 0x772554 = mode;
		return value;
	}
	if (*(int*) (other + 0x198) == 0) {
		*(int*) 0x772554 = mode;
		return value;
	}
	fcn_00471af0(other);
	*(int*) 0x772554 = mode;
	return value;
}
