typedef void (__cdecl* Cb5a80d0a)(int a0, int a1, int a2, int a3);
typedef void (__cdecl* Cb5a80d0b)(int a0, int a1, int a2, int a3);

int __cdecl fcn_005a74a0(unsigned char* a0);
void __cdecl fcn_00530510(void);
void __cdecl fcn_005305a0(void);
int __cdecl fcn_005155e0(unsigned char* a0);
void __cdecl fcn_004c3170(unsigned char* b);
int __cdecl fcn_005373e0(int a0, int a1);
void __cdecl fcn_005110d0(int a0);
int __cdecl fcn_00502cd0(int a0, int a1, int a2, int a3, int a4);
int __cdecl fcn_004432d0(int a0, int a1);
void __cdecl fcn_0043aa30(int a0);
void __cdecl fcn_005167c0(unsigned char* a0, int a1);
void __cdecl fcn_00516c50(int a0, unsigned char* a1);
int __cdecl fcn_00504bd0(int a0);
void __cdecl fcn_00438b40(char* p, int* v);
void __cdecl fcn_00438cb0(int a0, int a1);
int __cdecl fcn_00451840(float* a, float* b, float eps);
void __cdecl fcn_00597fd0(int a0);
void* __cdecl fcn_00426cc0(int a1);
void __cdecl fcn_00428720(void* p);
void __cdecl fcn_005312d0(int a0);
void __cdecl fcn_004c34d0(void);
void __cdecl fcn_00516ed0(int a0);
void __cdecl fcn_0043a9c0(int a0);
void __cdecl fcn_00516f60(void);
void __cdecl fcn_0059c800(int a0);
void __cdecl fcn_0059c9a0(int a0);
void __cdecl fcn_004bd1a0(int a0);
void __cdecl fcn_0059cb40(int a0);
void __cdecl fcn_0059de00(int a0);
void __cdecl fcn_0059e390(int a0);
void __cdecl fcn_0058f0a0(int a0);
void __cdecl fcn_005e69f0(int a0);

/* ADDRESS: GOLDTL 0x005a80d0 */
void __cdecl fcn_005a80d0(unsigned char* a0)
{
	unsigned char* v7;
	int n;
	int id;
	int w;
	int rec;
	int v10;
	int v11;
	int s0;
	int s1;
	int s2;
	int s3;
	int s4;
	int s5;
	unsigned char* p;
	int c;

	v7 = a0;
	id = -1;
	n = fcn_005a74a0(a0);
	if (n == 0) {
		*(int*) 0x7e2700 = n;
		return;
	}
	*(int*) 0x774658 = *(int*) 0x774650 + 1;
	a0 = (unsigned char*) *(int*) 0x6b8010;
	*(int*) 0x6a2520 = 0;
	fcn_00530510();
	fcn_005305a0();
	s0 = *(int*) 0x7e3a40;
	s1 = *(int*) 0x7e3a44;
	s2 = *(int*) 0x7e3a48;
	s3 = *(int*) 0x7e3a50;
	s4 = *(int*) 0x7e3a54;
	s5 = *(int*) 0x7e3a58;
	*(int*) 0x6752a8 = *(int*) 0x6aada0;
	*(int*) 0x6752ac = *(int*) 0x6aada4;
	*(unsigned char*) 0x6752b0 = *(unsigned char*) 0x6aada8;
	n = fcn_005155e0(v7);
	w = n * 0x3dc;
	*(int*) (w + 0x1043378) = *(int*) 0x1043378;
	if (n != 0) {
		fcn_004c3170(v7);
		if (n == -1 || *(char*) (w + 0x1043695) != 0) {
			*(int*) 0x7725c8 = 1;
			fcn_005373e0(0, 0x603c7);
			fcn_005373e0(0, 0x603c7);
			fcn_005110d0(*v7);
			*(int*) 0x7725c8 = 0;
		}
		*(int*) 0x7746c8 = (int) v7;
		*(int*) 0x6791c8 = *(int*) (v7 + 1);
		*(int*) 0x67530c = *(int*) (v7 + 1);
		p = (unsigned char*) fcn_00502cd0(*(int*) (v7 + 0x5d), 2, 6, 0, 0xfd);
		if (p == 0) {
			p = (unsigned char*) fcn_00502cd0(*(int*) (v7 + 0x5d), 2, 6, 4, 2);
		}
		*(int*) 0x675310 = *(int*) (p + 2);
		fcn_004432d0(n, 0);
		fcn_0043aa30(3);
		if (*(int*) 0x6b8300 != 0) {
			if (*(unsigned char*) 0x77666a == 2) {
				*(unsigned char*) (*(int*) 0x6b8300 + 0x8036) = (*(unsigned char*) (*(int*) 0x6b8300 + 0x8036) & 0xe7) | 4;
			} else {
				*(unsigned char*) (*(int*) 0x6b8300 + 0x8036) = (*(unsigned char*) (*(int*) 0x6b8300 + 0x8036) & 0xeb) | 8;
			}
		}
		fcn_005167c0((unsigned char*) *(int*) 0x7746c8, *(unsigned short*) p);
		fcn_00516c50(*(int*) 0x7746c8, p);
		if (*(int*) 0x67a370 != 0) {
			v10 = *(int*) (*(int*) 0x67a370 + 0x3c8);
			if (v10 != 0 && *(int*) (v10 + 0x210) != 0) {
				(*(Cb5a80d0a*) (v10 + 0x210))(*(int*) 0x67a370, 4, v10 + 0x214, 0);
			}
		}
		id = *(int*) 0x6791d0;
		if (*(unsigned short*) (v7 + 0x27) == *(unsigned short*) 0x774970) {
			fcn_00438b40((char*) *(int*) 0x6b8014, (int*) (*(int*) 0x6b8014 + 0x5c));
			v10 = *(int*) 0x6b8014 + 0x90;
			v11 = *(int*) 0x6b8014;
			fcn_00438cb0(v11, v10);
		} else {
			v10 = fcn_00504bd0(*v7);
			c = *v7;
			rec = *(int*) 0x868050 + c + c * 0x24c;
			if (v10 != 2) {
				if (*(char*) rec == 0x1c) {
					fcn_00438b40((char*) *(int*) 0x6b8014, (int*) (*(int*) 0x6b8014 + 0x5c));
					v10 = *(int*) 0x6b8014 + 0x90;
					fcn_00438cb0(*(int*) 0x6b8014, v10);
				} else if (fcn_00451840((float*) (*(int*) 0x6b8014 + 0x114), (float*) 0x662d70, 0.1f) == 0 && fcn_00451840((float*) (*(int*) 0x6b8014 + 0x120), (float*) 0x662d70, 0.1f) == 0) {
					fcn_00438b40((char*) *(int*) 0x6b8014, (int*) (*(int*) 0x6b8014 + 0x114));
					v10 = *(int*) 0x6b8014 + 0x120;
					fcn_00438cb0(*(int*) 0x6b8014, v10);
				}
			} else if (fcn_00451840((float*) (*(int*) 0x6b8014 + 0x114), (float*) 0x662d70, 0.1f) == 0 && fcn_00451840((float*) (*(int*) 0x6b8014 + 0x120), (float*) 0x662d70, 0.1f) == 0) {
				fcn_00438b40((char*) *(int*) 0x6b8014, (int*) (*(int*) 0x6b8014 + 0x114));
				v10 = *(int*) 0x6b8014 + 0x120;
				fcn_00438cb0(*(int*) 0x6b8014, v10);
			}
		}
		*(int*) 0x7e3a40 = *(int*) (*(int*) 0x6b8014 + 0x4c);
		*(int*) 0x7e3a44 = *(int*) (*(int*) 0x6b8014 + 0x50);
		*(int*) 0x7e3a48 = *(int*) (*(int*) 0x6b8014 + 0x54);
		*(int*) 0x7e3a50 = *(int*) (*(int*) 0x6b8014 + 0x84);
		*(int*) 0x7e3a54 = *(int*) (*(int*) 0x6b8014 + 0x88);
		*(int*) 0x7e3a58 = *(int*) (*(int*) 0x6b8014 + 0x8c);
		*(int*) 0x774688 = 0;
		*(int*) 0x77468c = 0;
	}
	switch (*v7) {
	case 0x1e:
		fcn_0059c9a0(*(int*) 0x7746c8);
		fcn_004bd1a0(*(int*) (v7 + 0x71));
		break;
	case 0x1f:
		fcn_0059cb40(*(int*) 0x7746c8);
		break;
	case 0x20:
		fcn_0059c800(*(int*) 0x7746c8);
		break;
	case 0x27:
		fcn_0059de00(*(int*) 0x7746c8);
		break;
	case 0x47:
		fcn_0059e390(*(int*) 0x7746c8);
		break;
	case 0x48:
	case 0x49:
	case 0x4a:
		fcn_0058f0a0(*(int*) 0x7746c8);
		break;
	case 0x4e:
	case 0x4f:
	case 0x50:
		fcn_005e69f0(*(int*) 0x7746c8);
		break;
	default:
		fcn_00597fd0(0);
		break;
	}
	if (n != -1) {
		*(int*) (w + 0x1043378) = 0;
		*(int*) 0x6b89c0 = 0;
	}
	fcn_00530510();
	fcn_005305a0();
	*(int*) 0x774688 = 0;
	*(int*) 0x77468c = 0;
	if (id != -1) {
		p = (unsigned char*) fcn_00426cc0(id);
		if (p != 0) {
			fcn_00428720(p);
			fcn_005312d0(*(int*) (p + 0x100));
		}
	}
	if (*(int*) 0x67a370 != 0) {
		n = *(int*) (*(int*) 0x67a370 + 0x3c8);
		if (n != 0 && *(int*) (n + 0x294) != 0) {
			(*(Cb5a80d0b*) (n + 0x294))(*(int*) 0x67a370, 5, n + 0x298, 0);
		}
	}
	if (*(int*) 0x6791d0 != -1) {
		fcn_005312d0(*(int*) 0x6791d0);
	}
	fcn_004c34d0();
	fcn_00516ed0(*(int*) 0x7746c8);
	fcn_0043a9c0(3);
	fcn_004432d0((int) a0, 0);
	*(int*) 0x7ea360 = 0;
	*(int*) 0x7746c8 = 0;
	*(int*) 0x6791c8 = 0;
	*(int*) 0x67530c = -1;
	*(int*) 0x675310 = -1;
	fcn_00516f60();
	*(int*) 0x7e3a40 = s0;
	*(int*) 0x7e3a44 = s1;
	*(int*) 0x7e3a48 = s2;
	*(int*) 0x7e3a50 = s3;
	*(int*) 0x7e3a54 = s4;
	*(int*) 0x7e3a58 = s5;
}
