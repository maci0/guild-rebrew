#include <string.h>
void* __cdecl m_alloc(unsigned int, char*);
int __cdecl fcn_0041bac0(unsigned char, unsigned char, unsigned char);
void __cdecl fcn_00477560(int*, int*);

/* ADDRESS: GOLDTL 0x00479330 */
int* __cdecl fcn_00479330(int* src)
{
	int* in;
	char* out;
	int j;
	int i;
	int k;
	unsigned short work[0x480];
	int offs[0x360];
	int* res;
	char* p;
	char* s;

	if (*(int*) ((char*) src + 0x26) != -1) {
		res = m_alloc(*(int*) src - *(int*) ((char*) src + 0x2e),
		    (char*) 0x67d9fc);
		memcpy(res, src, 0x32);



		*(int*) res = 0x32;
		*(unsigned char*) ((char*) res + 0xc) = 1;
		*(int*) ((char*) res + 0x26) = 0;
		*(int*) ((char*) res + 0x2e) = 0;
		in = (char*) src + 0x32;
		out = (char*) res + 0x36;
		p = (char*) src + 0x36;
		s = (char*) res + 0x32;
		for (j = 0; j < *(unsigned short*) ((char*) src + 0xa); j++) {
			*(int*) s = *(int*) in;
			offs[j] = (int) (s - (char*) res);
			*(int*) res += 4;
			for (i = 0; i < *(unsigned int*) in; i++) {
				*(int*) out = (int) (((unsigned int) *(int*) p * 2) / 3);
				*(int*) (out + 4) = *(int*) (p + 4);
				for (k = 0; k < *(unsigned int*) (p + 4); k++) {
					work[k] = (unsigned short) fcn_0041bac0(
					    *(unsigned char*) (p + 8 + k * 3),
					    *(unsigned char*) (p + 9 + k * 3),
					    *(unsigned char*) (p + 10 + k * 3));
					if (work[k] == 0) {
						work[k] = (unsigned short) fcn_0041bac0(5, 5, 5);
					}
					if (*(unsigned char*) ((char*) src + 0xd) == 1) {
						work[k] = (unsigned short) ((work[k] >> 1) &
						    *(unsigned short*) 0x100eb6c);
					}
				}
				memcpy(out + 8, work, *(unsigned int*) (p + 4) * 2);
				*(int*) ((char*) res + 0x26) += 1;
				*(int*) ((char*) res + 0x2e) += *(int*) (p + 4);
				*(int*) res += *(int*) (p + 4) * 2 + 8;
				p += *(int*) (p + 4) * 3 + 8;
				out += *(int*) (out + 4) * 2 + 8;
			}
			in = p;
			s = out;
			p += 4;
			out += 4;
		}
		*(int*) ((char*) res + 0x2a) = *(int*) res;
		*(int*) res += *(unsigned short*) ((char*) res + 0xa) * 4;
		fcn_00477560(offs, res);
		return res;
	}
	res = m_alloc(*(int*) src - *(int*) ((char*) src + 0x2e),
	    (char*) 0x67d9fc);
	memcpy(res, src, 0x32);



	*(int*) ((char*) res + 0x26) = -1;
	*(int*) res = 0x32;
	*(unsigned char*) ((char*) res + 0xc) = 1;
	*(int*) ((char*) res + 0x2e) = 0;
	out = (char*) res + 0x32;
	j = 0;
	if (*(unsigned short*) ((char*) src + 0xa) != 0) {
		do {
			i = 0;
			while (i < *(unsigned short*) ((char*) src + 6)) {
				s = (char*) src + 0x32 +
				    (*(unsigned short*) ((char*) src + 6) * j + i) * 3;
				work[i] = (unsigned short) fcn_0041bac0(
				    *(unsigned char*) s, *((unsigned char*) s + 1),
				    *((unsigned char*) s + 2));
				if (*(unsigned char*) ((char*) src + 0xd) == 1) {
					work[i] = (unsigned short) ((work[i] >> 1) &
					    *(unsigned short*) 0x100eb6c);
				}
				i++;
			}
			memcpy(out, work, *(unsigned short*) ((char*) src + 6) * 2);


			*(int*) res += *(unsigned short*) ((char*) src + 6) * 2;
			out += *(unsigned short*) ((char*) src + 6) * 2;
			j++;
		} while (j < *(unsigned short*) ((char*) src + 0xa));
	}
	*(int*) ((char*) res + 0x2a) = 0;
	return res;
}
