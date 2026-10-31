
int __cdecl fcn_004fd9d0(int, int);
void * __cdecl fcn_004ee060(int);
int __cdecl fcn_004ee0b0(void *);
void * __cdecl fcn_00470820(int, int, void *);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl fcn_00471b60(void *);
void __cdecl d2_SetForm(void *, int);
void __cdecl fcn_005340f0(int);
void __cdecl io_AppendText(int);
int __cdecl d2_CreateRadioGroup(int);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_0046fac0(int, int, char *, int);
void __cdecl fcn_00469470(int, int);
int __cdecl io_FormatTextBuffer(char *, int, ...);
void __cdecl fcn_00472900(int, int);
void __cdecl fcn_00534160(int, int, int, int);
void __cdecl fcn_00533a60(int, int, void *, int, int, int);
void __cdecl fcn_00472640(void *, int);
int __cdecl fcn_005373e0(int, int);
void __cdecl fcn_00469510(int);
void __cdecl fcn_00471e30(void *);
void __cdecl fcn_00532ef0(void);
int __cdecl fcn_00584f00(int, void *, int);
void __cdecl fcn_005263d0(void *, char *, int);

/* ADDRESS: GOLDTL 0x5848b0 */
void __cdecl fcn_005848b0(int a0)
{
	char msg[992];
	char buf[256];
	unsigned int pt[2];
	void *rec[3];
	int val[3];
	int item[3];
	int count;
	int i;
	int off;
	int y;
	int id;
	int idx;
	int keep;
	int last;
	int base;
	void *r;
	void *w;
	unsigned int exp;
	int *fields;
	int *ent;
	char *rp;

	count = 0;
	rec[0] = 0;
	rec[1] = 0;
	rec[2] = 0;
	pt[0] = (unsigned int)fcn_004fd9d0(0, 0x52);
	for (i = 0; i < 3; i++) {
		r = fcn_004ee060(i);
		if (*(int *)r != 0) {
			rec[count] = r;
			val[count] = fcn_004ee0b0(r);
			count++;
		}
	}
	if (count == 0) {
		io_FormatTextBuffer(msg, 0x404a, 0x868060 + (*(volatile unsigned char *)0x773d75) * 0x2f4);
		fcn_005263d0((void *)0x14b5404, msg, 0);
		fcn_00532ef0();
		return;
	}
	w = fcn_00470820(0, 0, (void *)0x6a9380);
	d2_SetOverlayAnimation(0, 0);
	fcn_00471b60(w);
	d2_SetForm(w, 0);
	fcn_005340f0(*(volatile unsigned int *)0x772514);
	d2_SetForm(w, 1);
	d2_SetForm(w, 2);
	keep = *(volatile unsigned int *)0x772514;
	d2_SetForm(w, 3);
	last = *(volatile unsigned int *)0x772514;
	d2_SetForm(w, 1);
	io_AppendText(0x4039);
	d2_SetForm(w, 2);
	idx = d2_CreateRadioGroup(0);
	y = 0x31;
	i = 0;
	off = 0;
	if (count > 0) {
		do {
			item[i] = fcn_0046f740(5, y - 0x19, 0x6c7, keep);
			fields = (int *)((char *)pt[0] + 0x34);
			item[i] = fcn_0046f740(7, y - 0x17, fields[i % 3] + 0x639, last);
			ent = (int *)(*(volatile unsigned int *)0x1015ea0 + item[i] * 0x2f4);
			ent[0x5c / 4] = 1;
			fcn_00469470(idx, item[i]);
			r = rec[off / 4];
			rp = (char *)r;
			io_FormatTextBuffer(buf, 0x68b3f8, *(unsigned int *)(0x14b5908 + *(int *)(rp + 0x10) * 4), *(unsigned int *)(0x14b596c + *(int *)(rp + 0x14) * 4));
			id = fcn_0046fac0(0, y - 0x30, buf, last);
			base = *(int *)(0x1015f4c + keep * 0x3cc);
			ent = (int *)(*(volatile unsigned int *)0x1015ea0 + id * 0x2f4);
			ent[0x18 / 4] = base;
			ent[0x6c / 4] = 1;
			fcn_00472900(id, 0x54);
			io_FormatTextBuffer(buf, 0x679060, *(unsigned int *)0x14b58e8);
			id = fcn_0046fac0(0x50, y - 0x1a, buf, last);
			ent = (int *)(*(volatile unsigned int *)0x1015ea0 + id * 0x2f4);
			ent[0x18 / 4] = *(int *)(0x1015f4c + keep * 0x3cc) - 0x50;
			fcn_00472900(id, 0x54);
			fcn_00534160(0x8c, y - 0x1a, *(unsigned char *)(rp + 4), 0x4df);
			io_FormatTextBuffer(buf, 0x679060, *(unsigned int *)0x14b58ec);
			id = fcn_0046fac0(0x50, y - 0xd, buf, last);
			ent = (int *)(*(volatile unsigned int *)0x1015ea0 + id * 0x2f4);
			ent[0x18 / 4] = *(int *)(0x1015f4c + keep * 0x3cc) - 0x50;
			fcn_00472900(id, 0x54);
			fcn_00534160(0x8c, y - 0xd, *(unsigned char *)(rp + 5), 0x4df);
			io_FormatTextBuffer(buf, 0x679060, *(unsigned int *)0x14b58f0);
			id = fcn_0046fac0(0x50, y, buf, last);
			ent = (int *)(*(volatile unsigned int *)0x1015ea0 + id * 0x2f4);
			ent[0x18 / 4] = *(int *)(0x1015f4c + keep * 0x3cc) - 0x50;
			fcn_00472900(id, 0x54);
			fcn_00534160(0x8c, y, *(unsigned char *)(rp + 6), 0x4df);
			io_FormatTextBuffer(buf, 0x679060, *(unsigned int *)0x14b58f4);
			id = fcn_0046fac0(0x50, y + 0xd, buf, last);
			ent = (int *)(*(volatile unsigned int *)0x1015ea0 + id * 0x2f4);
			ent[0x18 / 4] = *(int *)(0x1015f4c + keep * 0x3cc) - 0x50;
			fcn_00472900(id, 0x54);
			fcn_00534160(0x8c, y + 0xd, *(unsigned char *)(rp + 7), 0x4df);
			io_FormatTextBuffer(buf, 0x403f, *(unsigned char *)(rp + 8));
			id = fcn_0046fac0(0xfa, y - 0x1b, buf, last);
			ent = (int *)(*(volatile unsigned int *)0x1015ea0 + id * 0x2f4);
			ent[0x18 / 4] = *(int *)(0x1015f4c + keep * 0x3cc) - 0xfa;
			io_FormatTextBuffer(buf, 0x4040, fcn_004ee0b0(r));
			id = fcn_0046fac0(0xfa, y - 0xe, buf, last);
			ent = (int *)(*(volatile unsigned int *)0x1015ea0 + id * 0x2f4);
			ent[0x18 / 4] = *(int *)(0x1015f4c + keep * 0x3cc) - 0xfa;
			io_FormatTextBuffer(buf, 0x4041, *(int *)(rp + 0xc) * 2 + 0x9a8);
			id = fcn_0046fac0(0xfa, y - 1, buf, last);
			ent = (int *)(*(volatile unsigned int *)0x1015ea0 + id * 0x2f4);
			ent[0x18 / 4] = *(int *)(0x1015f4c + keep * 0x3cc) - 0xfa;
			off += 4;
			y += 0x64;
			i++;
		} while (i < count);
	}
	d2_SetForm(w, 3);
	fcn_00533a60(last, 0, pt, 2, *(int *)0x14b5428, *(int *)0x14b542c);
	*(volatile unsigned int *)0x100f1dc = 0xffffffff;
	do {
		r = (void *)pt[0];
		exp = *(volatile unsigned int *)(0x102cbc8 + idx * 0x8c);
		fcn_00472640(r, (exp != 0xffffffff) && (i != 0));
		if (*(volatile unsigned int *)0x14ce8e0) {
			*(volatile unsigned int *)0x774654 = 1;
		} else if (*(volatile unsigned int *)0x100f1dc != 0xffffffff) {
			if (*(volatile unsigned int *)0x67d370 == pt[0]) {
				for (id = 0; id < 3; id++) {
					if (exp == (unsigned int)id) {
						if (fcn_00584f00(a0, rec[id], val[id])) {
							*(volatile unsigned int *)0x774654 = 1;
						}
					}
				}
			} else if (*(volatile unsigned int *)0x67d370 == pt[1]) {
				*(volatile unsigned int *)0x774654 = 1;
			}
		}
	} while (fcn_005373e0(0x5848b0, 0x677c7));
	fcn_00469510(idx);
	fcn_00471e30(w);
	fcn_00532ef0();
}
