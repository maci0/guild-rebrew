#include <string.h>

void __cdecl ReportClientMessage(char*);
void* __cdecl m_alloc(unsigned int, char*);
unsigned short __cdecl fcn_0041bac0(unsigned char, unsigned char, unsigned char);
void __cdecl fcn_00477560(int*, int*);
extern char g_100eb80[];

/* ADDRESS: GOLDTL 0x00479110 */
int* __cdecl shp_Convert8To16(int* src, int unused, char* dest)
{
	unsigned short pal[256];
	unsigned short work[0x480];
	int offs[0x360];
	int* res;
	unsigned char* s;
	unsigned char* d2;
	unsigned int* q;
	unsigned int* hdr;
	int i;
	unsigned int counter;
	unsigned int count;
	unsigned int j;
	char flag;

	if (*(int*) ((char*) src + 0x26) == -1) {
		ReportClientMessage((char*) 0x67da10);
		return 0;
	}
	res = m_alloc(*(unsigned int*) ((char*) src + 0x2e) + *(int*) src, (char*) 0x67d9fc);
	memcpy(res, src, 0x32);
	*(int*) ((char*) res + 0x26) = 0;
	*(int*) ((char*) res + 0x2e) = 0;
	s = (unsigned char*) src + 0x36;
	d2 = (unsigned char*) res + 0x36;
	q = (unsigned int*) ((char*) src + 0x32);
	*(int*) res = 0x32;
	*(unsigned char*) ((char*) res + 0xc) = 1;
	hdr = (unsigned int*) ((char*) res + 0x32);
	for (i = 0; i < 0x100; i++) {
		pal[i] = fcn_0041bac0(g_100eb80[i * 4], g_100eb80[i * 4 + 1], g_100eb80[i * 4 + 2]);
	}
	for (i = 0; i < *(unsigned short*) ((char*) src + 0xa); i++) {
		*hdr = *q;
		offs[i] = (char*) hdr - (char*) res;
		*(int*) res += 4;
		for (counter = 0; counter < *q; counter++) {
			*(unsigned int*) d2 = *(unsigned int*) s * 2;
			*(unsigned int*) (d2 + 4) = *(unsigned int*) (s + 4);
			count = *(unsigned int*) (s + 4);
			for (j = 0; j < count; j++) {
				flag = *((char*) src + 0xd);
				work[j] = pal[s[8 + j]];
				if (flag == 1) {
					work[j] = (unsigned short) ((work[j] >> 1) & *(unsigned short*) 0x100eb6c);
				}
			}
			memcpy(d2 + 8, work, count * 2);
			*(int*) ((char*) res + 0x26) += 1;
			*(unsigned int*) ((char*) res + 0x2e) += *(unsigned int*) (s + 4);
			*(int*) res += *(unsigned int*) (s + 4) * 2 + 8;
			s += *(unsigned int*) (s + 4) + 8;
			d2 += *(unsigned int*) (d2 + 4) * 2 + 8;
		}
		hdr = (unsigned int*) d2;
		d2 += 4;
		q = (unsigned int*) s;
		s += 4;
	}
	*(int*) ((char*) res + 0x2a) = *(int*) res;
	*(int*) res += *(unsigned short*) ((char*) res + 0xa) * 4;
	fcn_00477560(offs, res);
	return res;
}
