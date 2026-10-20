#pragma optimize("y", off)

extern char g_7f4ca0[];
extern char g_6a5e88[];
extern char g_773d75;
extern short g_aed32c;
extern float g_665e9c;
extern double g_662a08;

char* __cdecl fcn_00503fe0(int, ...);
char* __cdecl fcn_00502cd0(int, ...);
char* __cdecl fcn_00503e80(void);
void __cdecl fcn_00546190(char*);
int __cdecl fcn_00555490(short*, int*, int*);
double __cdecl fcn_0050bb50(int, int);
int __cdecl fcn_0042e410(int);
int __cdecl fcn_0050d2a0(int);
void __cdecl fcn_004c4eb0(unsigned int);
void __cdecl fcn_004c4ef0(unsigned int);
void __cdecl fcn_004c51f0(int, int, int, int, int, int);
void __cdecl fcn_004c51a0(int, unsigned int, int, int);
void __cdecl fcn_004c4670(int, int, int, int*);
void __cdecl fcn_004c4510(int, int);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_00500bb0(int*, int, int, int);

/* ADDRESS: GOLDTL 0x00555510 */
void __cdecl fcn_00555510(char* a0)
{
	int ent[48];
	int start;
	int end;
	int idx;
	int count;
	int x1;
	int y1;
	int v;
	int w;
	int mx;
	int c;
	int i;
	short* rec;
	char* p;
	char* q;
	char* t;
	unsigned char* t0;

	if (*(int*) (a0 + 0x70) == -2) {
		fcn_00546190(a0);
		return;
	}
	for (i = 0; i < 0x30; i++) {
		ent[i] = 0;
	}
	i = 0;
	ent[0] = (int) fcn_00503fe0(1, 5, 0x16);
	if (ent[0] != 0) {
		p = (char*) ent;
		do {
			if (i >= 0x10) {
				break;
			}
			q = fcn_00502cd0(*(int*) (*(char**) p + 0x5d), 2, 0, 0x2a, 6);
			if (q != 0) {
				*(int*) (p + 4) = (int) fcn_00502cd0(*(int*) (q + 0x14), 1, 0, 0x179);
				*(int*) (p + 8) = (int) fcn_00502cd0(*(int*) (q + 0x14), 1, 0, 0x17a);
			}
			i++;
			p += 0xc;
		} while ((*(int*) p = (int) fcn_00503e80()) != 0);
	}
	if (*(int*) (a0 + 0x70) != 0) {
		return;
	}
	start = *(int*) (a0 + 0xac);
	end = start + 0x180;
	if (start < end) {
		rec = (short*) (g_7f4ca0 + start * 0x21c);
		count = end - start;
		do {
			if (fcn_00555490(rec, ent, &idx) != 0) {
				x1 = (int) (fcn_0050bb50(0x179, g_773d75) * g_662a08);
				y1 = (int) (fcn_0050bb50(0x17a, g_773d75) * g_662a08);
				v = fcn_0042e410(4) + 3;
				w = fcn_0050d2a0((int) rec);
				mx = x1;
				if (x1 <= y1) {
					mx = y1;
				}
				t0 = (unsigned char*) *(int*) (ent + idx * 3);
				if ((double) w > (double) mx * g_665e9c) {
					if (ent[idx * 3 + 1] != 0 && ent[idx * 3 + 2] != 0) {
						if (fcn_0042e410(2) != 0) {
							goto draw179;
						}
						goto draw17a;
					}
				}
				if (w > x1 && ent[idx * 3 + 1] != 0) {
					goto draw179;
				}
				if (w > y1) {
					if (ent[idx * 3 + 2] != 0) {
						goto draw17a;
					}
					if (w > x1) {
						fcn_004c4510((int) t0, *(int*) (t0 + 1));
						c = (int) *(unsigned short*) (ent + idx * 3) - g_aed32c;
						fcn_004c4670(2, 1, c + 0x69, &v);
						goto drawn;
					}
				}
				goto next;
draw179:
				t = (char*) ent[idx * 3 + 1];
				fcn_004c4eb0((unsigned int) g_6a5e88);
				fcn_004c51f0(-1, *(int*) (t + 6), 0x179, 1, g_773d75, 0);
				fcn_004c51a0(-1, *(unsigned int*) (rec + 2), g_773d75, (int) ((double) x1 * g_665e9c));
				fcn_004c51a0(-1, *(unsigned int*) (g_7f4ca0 + 4 + *(unsigned short*) (t0 + 0x27) * 0x21c), g_773d75, x1);
				fcn_004c4510((int) t0, *(int*) (t0 + 1));
				c = (int) *(unsigned short*) (ent + idx * 3) - g_aed32c;
				fcn_004c4670(4, 1, c + 0x65, &x1);
				fcn_004c4670(2, 1, c + 0x6b, &v);
				fcn_004c5360();
				fcn_004c4ef0((unsigned int) g_6a5e88);
				fcn_004c4510((int) t0, *(int*) (t0 + 1));
				fcn_004c4670(2, 1, c + 0x69, &v);
				goto drawn;
draw17a:
				t = (char*) ent[idx * 3 + 2];
				fcn_004c4eb0((unsigned int) g_6a5e88);
				fcn_004c51f0(-1, *(int*) (t + 6), 0x17a, 1, g_773d75, 0);
				fcn_004c51a0(-1, *(unsigned int*) (rec + 2), g_773d75, (int) ((double) y1 * g_665e9c));
				fcn_004c51a0(-1, *(unsigned int*) (g_7f4ca0 + 4 + *(unsigned short*) (t0 + 0x27) * 0x21c), g_773d75, y1);
				fcn_004c4510((int) t0, *(int*) (t0 + 1));
				c = (int) *(unsigned short*) (ent + idx * 3) - g_aed32c;
				fcn_004c4670(4, 1, c + 0x65, &y1);
				fcn_004c4670(2, 1, c + 0x6b, &v);
				fcn_004c5360();
				fcn_004c4ef0((unsigned int) g_6a5e88);
				fcn_004c4510((int) t0, *(int*) (t0 + 1));
				fcn_004c4670(2, 1, c + 0x69, &v);
drawn:
				fcn_004c5360();
			}
next:
			rec = (short*) ((char*) rec + 0x21c);
			count--;
		} while (count != 0);
	}
	*(int*) (a0 + 0xac) = end;
	if (end >= 0x300) {
		*(int*) (a0 + 0xac) = 0;
		*(int*) (a0 + 0xb0) = 0;
		*(int*) (a0 + 0x52) = *(int*) (a0 + 0x52) + 1;
		*(unsigned short*) (a0 + 0x56) = 0x16;
		*(int*) (a0 + 0x58) = 0x1e;
		return;
	}
	fcn_00500bb0((int*) (a0 + 0x52), 0, 0xf, 0);
}
