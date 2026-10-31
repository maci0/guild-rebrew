void __cdecl ReportClientMessage(char*);
void* __cdecl m_alloc(unsigned int, char*);
int __cdecl fcn_0041bac0(int, int, int);
void __cdecl fcn_00477560(int*, int*);

/* ADDRESS: GOLDTL 0x00479110 */
int* __cdecl shp_Convert8To16(int* src, int unused, char* dest)
{
	unsigned short pal[256];
	unsigned short work[256];
	int offs[0x360];
	int* res;
	int* s;
	int* d2;
	char* q;
	char* p;
	int i;
	int counter;
	int count;
	int j;
	int idx;
	char flag;

	if (*(int*) ((char*) src + 0x26) == -1) {
		ReportClientMessage((char*) 0x67da10);
		return 0;
	}
	res = m_alloc(*(unsigned int*) ((char*) src + 0x2e) + *(int*) src, (char*) 0x67d9fc);
	for (i = 0; i < 0xc; i++) {
		res[i] = src[i];
	}
	*(unsigned short*) (res + 0xc) = *(unsigned short*) (src + 0xc);
	*(int*) ((char*) res + 0x26) = 0;
	*(int*) ((char*) res + 0x2e) = 0;
	s = (int*) ((char*) src + 0x36);
	d2 = (int*) ((char*) res + 0x36);
	q = dest + 0x32;
	*(int*) res = 0x32;
	*(unsigned char*) ((char*) res + 0xc) = 1;
	for (i = 0; i < 0x100; i++) {
		pal[i] = (unsigned short) fcn_0041bac0(0x100eb80 + i * 4, 0x100eb80 + i * 4 + 1,
		    0x100eb80 + i * 4 + 2);
	}
	counter = 0;
	i = 0;
	*(int*) ((char*) res + 0x2a) = 0;
	if (*(unsigned short*) ((char*) src + 0xa) == 0) {
		goto done;
	}
	do {
		p = q;
		count = 0;
		*(int*) ((char*) res + 0x32) = *(int*) p;
		offs[i] = 0x32;
		*(int*) res += 4;
		if (*(int*) p != 0) {
			do {
				*(int*) d2 = *(int*) s * 2;
				*(int*) ((char*) d2 + 4) = *(int*) ((char*) s + 4);
				count = *(int*) ((char*) s + 4);
				if (count != 0) {
					flag = *(char*) ((char*) src + 0xd);
					for (j = 0; j < count; j++) {
						idx = *(unsigned char*) ((char*) s + 8 + j);
						work[j] = pal[idx];
						if (flag == 1) {
							work[j] = (unsigned short) ((work[j] >> 1) & *(unsigned short*) 0x100eb6c);
						}
					}
				}
				for (j = 0; j < count * 2; j++) {
					((char*) d2)[8 + j] = ((char*) work)[j];
				}
				*(int*) ((char*) res + 0x26) += 1;
				*(int*) ((char*) res + 0x2e) += count;
				*(int*) res += count * 2 + 8;
				s = (int*) ((char*) s + count + 8);
				d2 = (int*) ((char*) d2 + count * 2 + 8);
				counter += 1;
			} while (counter < *(int*) p);
		}
		q = (char*) s;
		d2 = (int*) ((char*) d2 + 4);
		s = (int*) ((char*) s + 4);
		i += 1;
	} while (i < *(unsigned short*) ((char*) src + 0xa));
done:
	*(int*) ((char*) res + 0x2a) = *(int*) res;
	*(int*) res += *(unsigned short*) ((char*) res + 0xa) * 4;
	fcn_00477560(offs, res);
	return res;
}
