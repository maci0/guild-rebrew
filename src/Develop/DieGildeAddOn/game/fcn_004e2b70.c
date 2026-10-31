/* TOD cutscene setup handler, 0x4e2b70..0x4e301e (1199 bytes).  Registered
 * with id 8 through fcn_004e7160 at 0x4e7299; frame is a 0x23EC-byte local
 * block (single `add esp,0x23EC; ret` exit at 0x4e3018/0x4e301e). */

typedef struct {
	float f10;          /* 0x00 */
	int alo;            /* 0x04 */
	int ahi;            /* 0x08 */
	int xslot;          /* 0x0c: fcn_004e44b0 result; arg to fcn_004e4610/004e44f0 */
	int yslot;          /* 0x10: fcn_005095d0 out-param */
	int blo;            /* 0x14 */
	int bhi;            /* 0x18 */
	int w[6];           /* 0x1c */
	char buf1[0x400];   /* 0x34 */
	char buf2[0x1fb8];  /* 0x434 */
} Frame4e2b70;

int __cdecl gm_LookupEntityRecordById(int);
void __cdecl fcn_004e4e90(char* s);
int __cdecl fcn_004c3100(char* s, int a);
void __cdecl fcn_004e4730(char* s);
void __cdecl fcn_004e4b60(char* s);
void __cdecl fcn_00445f50(int a, int b, float f, int c);
void __cdecl fcn_004463f0(int a, int b, float f);
int __cdecl fcn_004e44b0(char* s, void* p);
int __cdecl fcn_004e4d00(int a, int b, int c);
void __cdecl fcn_004e4b40(int a, int b, char* s, int c, int d);
void __cdecl fcn_005373e0(int a, int b);
void __cdecl fcn_004234e0(int a, char* s, int b, int c, int d, int e, int f);
int __cdecl fcn_005095d0(void* p, void* buf);
void __cdecl io_FormatTextBuffer(char* buf, ...);
int __cdecl fcn_004e6eb0(void* buf, int n);
void __cdecl fcn_005d0660(int a, int b, int c, int d);
void __cdecl fcn_004c4510(void* a, int b);
void __cdecl fcn_004c4570(int a, int b, int c, void* p);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c5420(int a, int b, int c, int d, int e);
void __cdecl fcn_005356b0(int p);
void __cdecl fcn_00509fc0(void* a, void* b, int c);
void __cdecl fcn_004e48b0(void);
void __cdecl fcn_004e4610(void* h);
void __cdecl fcn_004e44f0(void* h);
void __cdecl fcn_004e4c00(void);
void __cdecl fcn_004e4910(void);
void __cdecl fcn_004c09b0(void);
void __cdecl fcn_004230e0(void* h);
void __cdecl fcn_004e4eb0(void);

/* ADDRESS: GOLDTL 0x004e2b70 */
void __cdecl fcn_004e2b70(void* arg)
{
	Frame4e2b70 f;
	void* obj;
	int handle;
	int i;
	int state;
	int start;
	int r;
	int flags;
	int idxval;
	unsigned int mask;
	__int64 q;

	obj = (void*) gm_LookupEntityRecordById(*(int*) ((char*) arg + 0x34));
	mask = *(unsigned int*) 0x7f4c04;
	i = 0;
	f.w[0] = 8;
	f.w[1] = 0xa;
	f.w[2] = 0xc;
	f.w[3] = 0xf;
	f.w[4] = 0x12;
	f.w[5] = 0x14;
	state = 6;
	*(int*) 0x68bfb8 = 0x702c6;
	*(int*) 0x7725c8 = 1;
	mask &= 0xffff;
	while (i < 6) {
		if ((int) mask < f.w[i]) {
			state = i;
			break;
		}
		i++;
	}
	fcn_004e4e90((char*) 0x68bd14);
	handle = fcn_004c3100((char*) 0x68d2d0, 1);
	fcn_004e4730((char*) 0x68d2c8);
	fcn_004e4b60((char*) 0x68d2b8);
	fcn_00445f50(state, 0, 1.0f, 1);
	fcn_004463f0(0, 0, 0.0f);
	f.xslot = fcn_004e44b0((char*) 0x68d29c, (void*) 0x6b5c60);
	r = fcn_004e4d00(3000, 0, 0);
	if (r == 0) {
		fcn_004e4b40(-8, handle, (char*) 0x68d294, 0, 0);
		fcn_004e4b40(-8, handle, (char*) 0x68d294, 2, 4000);
		fcn_004e4b40(-8, handle, (char*) 0x68d294, 3, 3000);
		fcn_004e4b40(-8, handle, (char*) 0x68d294, 4, 2000);
		fcn_004e4b40(-8, handle, (char*) 0x68d294, 5, 4000);
		fcn_004e4b40(-8, handle, (char*) 0x68d294, 6, 500);
		state = fcn_004e4d00(0x2af8, 0, 0);
		if (state == 0) {
			start = *(volatile int*) 0x6b7fac;
			while (*(volatile unsigned int*) 0x6b7fac < (unsigned int) (start + 0x339) && state == 0) {
				fcn_005373e0(0, *(int*) 0x68bfb8);
				if (*(int*) 0x14ce8e0 != 0) {
					state = 1;
				}
				f.ahi = 0;
				f.alo = *(volatile int*) 0x6b7fac - start;
				q = *(__int64*) &f.alo;
				if ((float) q * *(float*) 0x664f28 < *(float*) 0x6628a0) {
					f.bhi = 0;
					f.blo = *(volatile int*) 0x6b7fac - start;
					f.f10 = (float) *(__int64*) &f.blo * *(float*) 0x664f28;
				} else {
					f.f10 = 1.0f;
				}
				fcn_004463f0(0, 1, f.f10);
			}
			fcn_004463f0(0, 1, 1.0f);
			fcn_004e4d00(0x2cec, 0, 0);
		}
	}
	fcn_004234e0(0, (char*) 0x68d288, 1, 0x3f, 0x7f, 0, 0);
	*(int*) 0x7725c8 = 0;
	r = fcn_005095d0(obj, &f.yslot);
	flags = *(int*) ((char*) obj + 0x1cc);
	if (r != 0) {
		if ((flags & 1) != 0 && (flags & 2) == 0) {
			idxval = *(unsigned short*) obj;
			io_FormatTextBuffer(f.buf1, 0x40fb, 0x40f5, idxval);
			if (fcn_004e6eb0(f.buf1, 0x10) != 0) {
				r = *(int*) ((char*) obj + 4);
				f.alo = 0;
				f.f10 = 100.0f;
				fcn_004c4510(obj, r);
				fcn_004c4570(4, 1, 0x1c, &f.f10);
				fcn_004c4570(4, 1, 0x24, &f.alo);
				*(char*) ((char*) obj + 8) = 100;
				fcn_004c5360();
				fcn_004c5420(*(int*) ((char*) obj + 4), 0x1cc, 4, 2, 0);
			} else {
				fcn_005d0660(*(int*) (0x7f4ca4 + 540 * (unsigned short) *(unsigned short*) 0x774970), 0xa, *(int*) 0x14abde8, *(int*) 0x68bfb8);
			}
		} else {
			fcn_005d0660(*(int*) (0x7f4ca4 + 540 * (unsigned short) *(unsigned short*) 0x774970), 0xa, *(int*) 0x14abde8, *(int*) 0x68bfb8);
		}
	} else {
		if ((flags & 1) != 0 && (flags & 2) == 0) {
			idxval = *(unsigned short*) obj;
			f.f10 = 0.0f;
			*(float*) &f.alo = 100.0f;
			io_FormatTextBuffer(f.buf1, 0x40fc, 0x40f5, idxval);
			fcn_004e6eb0(f.buf1, 0x10);
			fcn_004c4510(obj, *(int*) ((char*) obj + 4));
			fcn_004c4570(4, 1, 0x1c, &f.alo);
			fcn_004c4570(4, 1, 0x24, &f.f10);
			fcn_004c5360();
			fcn_004c5420(*(int*) ((char*) obj + 4), 0x1cc, 4, 2, 0);
			*(char*) ((char*) obj + 8) = 100;
		} else if ((*(unsigned char*) 0x7747b0 & 8) != 0) {
			*(char*) ((char*) obj + 8) = 0;
			*(int*) 0x774954 = 1;
			if (f.yslot != 0) {
				io_FormatTextBuffer(f.buf1, 0x1ab4);
			} else {
				io_FormatTextBuffer(f.buf1, 0x1ab3, *(unsigned short*) obj);
			}
			fcn_004e6eb0(f.buf1, 0);
			fcn_005356b0(0x5438c0);
		} else {
			fcn_00509fc0(obj, f.buf2, 1);
			fcn_004e6eb0(f.buf2 + 0xc, 0x10);
		}
	}
	fcn_004e48b0();
	fcn_004e4610((void*) f.xslot);
	fcn_004e44f0((void*) f.xslot);
	fcn_004e4c00();
	fcn_004e4910();
	fcn_004c09b0();
	fcn_004230e0((void*) handle);
	fcn_004e4eb0();
	*(int*) 0x772f54 = 0;
}
