int __cdecl fcn_00500240(int a, int b, int c);
void* __cdecl fcn_004ffff0(int a, int b);
int __cdecl fcn_004c4330(void* req);

/* ADDRESS: GOLDTL 0x004c6090 */
int __cdecl fcn_004c6090(int a0, char a1, int a2, int a3)
{
	char buf[0x9c];
	char* q;
	int t;

	buf[0] = 0x3d;
	if (a0 == 0) {
		return -1;
	}
	t = fcn_00500240(a0, a2, a3);
	*(int*) (buf + 0x10) = *(int*) (a0 + 1);
	if (t != 0) {
		*(int*) (buf + 0x19) = *(int*) (t + 4);
		if (*(int*) (t + 0x170) != 0) {
			goto skip;
		}
		q = (char*) fcn_004ffff0(*(unsigned short*) t, a0);
	} else {
		*(int*) (buf + 0x19) = -1;
		q = (char*) fcn_004ffff0(0xffff, a0);
	}
	if (q != 0) {
		*(int*) (buf + 0x14) = *(int*) (q + 1);
	} else {
skip:
		*(int*) (buf + 0x14) = -1;
	}
	buf[0x18] = a1;
	buf[0x1d] = (char) a2;
	buf[0x1e] = (char) a3;
	return fcn_004c4330(buf);
}
