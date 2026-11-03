typedef void (__cdecl* CALLBACK)(int, int, int, int, int, int, int, int, int, int);

/* ADDRESS: GOLDTL 0x00455d30 */
void __cdecl fcn_00455d30(int count, int arg1, unsigned char flags, int arg3, int arg4)
{
	CALLBACK cb;
	int v6;
	int v3;
	int i;

	i = 0;
	v6 = 0;
	if ((flags & 5) != 0) {
		if ((flags & 1) == 0) {
			v6 = 0xb;
		}
		if (flags & 2) {
			cb = (CALLBACK) 0x455e60;
		}
		else {
			cb = (CALLBACK) 0x455f80;
		}
	}
	else {
		cb = (CALLBACK) 0x455f60;
	}
	if (count <= 0)
		return;
	do {
		v3 = (*(int*) 0x1043290 + 0xffff) >> 16;
		*(int*) 0x10529c0 = ((*(int*) 0x1043298 + 0xffff) >> 16) - v3;
		if (*(int*) 0x10529c0 > 0) {
			cb(((((v3 << 16) - *(int*) 0x1043290) * *(int*) 0x10529cc) >> 16) + *(int*) 0x1042a20,
			   *(int*) 0x10529cc, v6, *(int*) 0x10529c0,
			   *(int*) 0x1042580 + v3, *(int*) 0x1040624, v3,
			   i + arg4, arg1, *(int*) 0x1040620);
		}
		*(int*) 0x1043298 += *(int*) 0x1042a2c;
		*(int*) 0x1043290 += *(int*) 0x1042a1c;
		*(int*) 0x1042a20 += *(int*) 0x1042a0c;
		*(int*) 0x1042580 += arg1;
		i++;
	} while (i < count);
}
