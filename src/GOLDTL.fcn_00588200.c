/* Refreshes the portrait graphics of one animation object: three slot frames,
   bars, the two counter labels and the position/displacement fields. */

int __cdecl fcn_00471f80(int);
float __cdecl fcn_004f0eb0(int, int, int);
void __cdecl fcn_004f10d0(char*, int*, int*);
void __cdecl fcn_00472380(int, int, int, int);
void __cdecl fcn_00472640(int, int);
int __cdecl fcn_004f0ff0(char*, int, int, int, int*, int*);
float __cdecl fcn_005e8860(int);
int __cdecl _ftol(void);
void __cdecl fcn_005886f0(char*, int);
void __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_0046fac0(int, int, char*, int);
void __cdecl fcn_00472900(int, int);
void __cdecl fcn_0051af00(char*, char*, ...);
int __cdecl fcn_0050d320(char*, unsigned char);

/* ADDRESS: GOLDTL 0x00588200 */
void __cdecl fcn_00588200(char* a0, char* a1, char* a2)
{
	int level;
	int percent;
	int max;
	int rec;
	int show;
	unsigned int v1;
	unsigned int v2;
	float f;
	char text[64];

	level = fcn_00471f80(*(int*) (a1 + 0xb0));
	percent = fcn_00471f80(*(int*) (a1 + 0xb4));
	f = fcn_004f0eb0(level, percent, 1);
	fcn_004f10d0(a0, (int*) (a1 + 0xdc), (int*) (a1 + 0xe0));
	max = *(int*) (a1 + 0xe0);
	if (max < level) {
		level = max;
	}
	fcn_00472380(*(int*) (a1 + 0xb0), 0, max, level);
	fcn_00472640(*(int*) (a1 + 0xcc), 1 <= *(int*) (a1 + 0xdc));
	fcn_00472640(*(int*) (a1 + 0xd0), 2 <= *(int*) (a1 + 0xdc));
	*(int*) (*(int*) 0x1015ea0 + 0x3c + *(int*) (a1 + 0xc8) * 0x2f4) =
	    *(int*) (a1 + 0xa0) == 0;
	*(int*) (*(int*) 0x1015ea0 + 0x3c + *(int*) (a1 + 0xcc) * 0x2f4) =
	    *(int*) (a1 + 0xa0) == 1;
	*(int*) (*(int*) 0x1015ea0 + 0x3c + *(int*) (a1 + 0xd0) * 0x2f4) =
	    *(int*) (a1 + 0xa0) == 2;
	*(int*) (*(int*) 0x1015ea0 + 0x38 + *(int*) (a1 + 0xc8) * 0x2f4) =
	    *(int*) (a1 + 0xa0) == 0;
	*(int*) (*(int*) 0x1015ea0 + 0x38 + *(int*) (a1 + 0xcc) * 0x2f4) =
	    *(int*) (a1 + 0xa0) == 1;
	*(int*) (*(int*) 0x1015ea0 + 0x38 + *(int*) (a1 + 0xd0) * 0x2f4) =
	    *(int*) (a1 + 0xa0) == 2;
	rec = fcn_004f0ff0((char*) (*(unsigned short*) 0x774970 * 0x21c + 0x7f4ca0), level,
	                   percent, *(int*) (a1 + 0xa0) + 1, (int*) &v1, (int*) &v2);
	show = *(float*) (a1 + 0x20) <= *(float*) 0x662910 && rec != 0 &&
	       *(float*) (a2 + 8 + *(int*) (a1 + 0xa0) * 4) >= f &&
	       (*(unsigned char*) (a2 + 4) & 2) == 0;
	fcn_00472640(*(int*) (a1 + 0xb8), show);
	fcn_00472640(*(int*) (a1 + 0xbc),
	             (~*(unsigned int*) (a2 + 4) >> 1) & 1);
	fcn_005e8860(1);
	fcn_00472380(*(int*) (a1 + 0xa8), 0, 100, _ftol());
	fcn_005886f0(a1, 1);
	fcn_00472380(*(int*) (a1 + 0xac), 0, 100, _ftol());
	fcn_00472380(*(int*) (a1 + 0xc4), 0, 100, _ftol());
	fcn_004727a0(*(int*) (a1 + 0xc0), 2);
	fcn_00519190(0x6811b0);
	rec = fcn_0046fac0(0, 0xf, (char*) 0x14b54c0, *(int*) 0x772514);
	*(int*) (rec * 0x2f4 + 0x6c + *(int*) 0x1015ea0) = 1;
	*(int*) (rec * 0x2f4 + 0x18 + *(int*) 0x1015ea0) =
	    *(int*) (*(int*) 0x772514 * 0x3cc + 0x1015f4c) / 2;
	fcn_00472900(rec, 0x54);
	fcn_0051af00(text, (char*) 0x6a9480, v2, v1);
	rec = fcn_0046fac0(0, 0x23, text, *(int*) 0x772514);
	*(int*) (rec * 0x2f4 + 0x6c + *(int*) 0x1015ea0) = 1;
	*(int*) (rec * 0x2f4 + 0x18 + *(int*) 0x1015ea0) =
	    *(int*) (*(int*) 0x772514 * 0x3cc + 0x1015f4c) / 2;
	fcn_00472900(rec, 0x54);
	rec = fcn_0046fac0(*(int*) (*(int*) 0x772514 * 0x3cc + 0x1015f4c) / 2,
	                   0xf, (char*) 0x14b54c4, *(int*) 0x772514);
	*(int*) (rec * 0x2f4 + 0x6c + *(int*) 0x1015ea0) = 1;
	*(int*) (rec * 0x2f4 + 0x18 + *(int*) 0x1015ea0) =
	    *(int*) (*(int*) 0x772514 * 0x3cc + 0x1015f4c) / 2;
	fcn_00472900(rec, 0x54);
	fcn_0051af00(text, (char*) 0x6a9480,
	             fcn_0050d320((char*) (*(unsigned short*) 0x774970 * 0x21c + 0x7f4ca0),
	                          *(unsigned char*) 0x773d75));
	rec = fcn_0046fac0(*(int*) (*(int*) 0x772514 * 0x3cc + 0x1015f4c) / 2,
	                   0x23, text, *(int*) 0x772514);
	*(int*) (rec * 0x2f4 + 0x6c + *(int*) 0x1015ea0) = 1;
	*(int*) (rec * 0x2f4 + 0x18 + *(int*) 0x1015ea0) =
	    *(int*) (*(int*) 0x772514 * 0x3cc + 0x1015f4c) / 2;
	fcn_00472900(rec, 0x54);
	*(int*) 0x9a9214 = level;
	*(int*) 0x9a9218 = percent;
	*(int*) 0x9a921c = *(int*) (a1 + 0xa0);
	*(int*) 0x9a9208 = *(int*) (a1 + 0x10);
	*(int*) 0x9a920c = *(int*) (a1 + 0x14);
	*(int*) 0x9a9210 = *(int*) (a1 + 0x18);
}
