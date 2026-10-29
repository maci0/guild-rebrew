void* __cdecl m_alloc(unsigned int, char*);
int __cdecl fcn_0041bac0(int, int, int);
void __cdecl fcn_00477560(int*, int*);

/* ADDRESS: GOLDTL 0x00479330 */
int* __cdecl fcn_00479330(int* src)
{
	int* in;
	int* out;
	int j;
	int i;
	int k;
	unsigned short work[0x480];
	int offs[0x360];
	int* res;
	char* p;
	char* s;

	if (*(int*) ((char*) src + 0x26) == -1) {
		res = m_alloc(*(int*) src - *(int*) ((char*) src + 0x2e),
		    (char*) 0x67d9fc);
		for (i = 0; i < 0xc; i++) {
			res[i] = src[i];
		}
		*(unsigned short*) (res + 0xc) = *(unsigned short*) (src + 0xc);
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
				for (i = 0; i < *(unsigned short*) ((char*) src + 6) * 2; i++) {
					out[i] = ((char*) work)[i];
				}
				*(int*) res += *(unsigned short*) ((char*) src + 6) * 2;
				out += *(unsigned short*) ((char*) src + 6) * 2;
				j++;
			} while (j < *(unsigned short*) ((char*) src + 0xa));
		}
		*(int*) ((char*) res + 0x2a) = 0;
		return res;
	}
	res = m_alloc(*(int*) src - *(int*) ((char*) src + 0x2e),
	    (char*) 0x67d9fc);
	for (i = 0; i < 0xc; i++) {
		res[i] = src[i];
	}
	*(unsigned short*) (res + 0xc) = *(unsigned short*) (src + 0xc);
	*(int*) res = 0x32;
	*(unsigned char*) ((char*) res + 0xc) = 1;
	*(int*) ((char*) res + 0x26) = 0;
	*(int*) ((char*) res + 0x2e) = 0;
	in = (char*) src + 0x32;
	out = (char*) res + 0x36;
	p = (char*) src + 0x36;
	s = (char*) res + 0x32;
	j = 0;
	if (*(unsigned short*) ((char*) src + 0xa) == 0) {
		goto done;
	}
	do {
		*(int*) s = *(int*) in;
		offs[j] = (int) (s - (char*) res);
		*(int*) res += 4;
		if (*(int*) in != 0) {
			i = 0;
			do {
				*(int*) out = (int) (((unsigned int) *(int*) p * 2) / 3);
				*(int*) (out + 4) = *(int*) (p + 4);
				if (*(int*) (p + 4) != 0) {
					for (k = 0; k < *(int*) (p + 4); k++) {
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
					for (k = 0; k < *(int*) (p + 4) * 2; k++) {
						out[8 + k] = ((char*) work)[k];
					}
				}
				*(int*) ((char*) res + 0x26) += 1;
				*(int*) ((char*) res + 0x2e) += *(int*) (p + 4);
				*(int*) res += *(int*) (p + 4) * 2 + 8;
				p += *(int*) (p + 4) * 3 + 8;
				out += *(int*) (out + 4) * 2 + 8;
				i++;
			} while (i < *(int*) in);
		}
		in = p;
		s = out;
		p += 4;
		out += 4;
		j++;
	} while (j < *(unsigned short*) ((char*) src + 0xa));
done:
	*(int*) ((char*) res + 0x2a) = *(int*) res;
	*(int*) res += *(unsigned short*) ((char*) res + 0xa) * 4;
	fcn_00477560(offs, res);
	return res;
}
