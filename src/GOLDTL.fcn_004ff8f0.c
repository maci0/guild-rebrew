extern unsigned char g_slot_table[2];
extern unsigned char g_773d75;
extern int g_aed32c;

int __cdecl gm_RandomMod(int);
int __cdecl fcn_004ff860(unsigned char*);
float __cdecl fcn_004ff210(unsigned short, int);
int __cdecl fcn_00508e40(int);
int __cdecl fcn_004fffb0(int);
void __cdecl fcn_004c4510(void*, int);
int __cdecl fcn_004c4700(unsigned char, unsigned char, short, void*);
void __cdecl fcn_004c53a0(void);
int __cdecl fcn_004c51a0(int, int, unsigned char, int);
int __cdecl fcn_004c4fc0(int, int, int, int, int, int, int, int);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_004c4480(int);
void __cdecl fcn_00535960(void);
int __cdecl fcn_00507400(int, int);
int __cdecl fcn_0047dd60(void*);

/* ADDRESS: GOLDTL 0x004ff8f0 */
void __cdecl fcn_004ff8f0(void)
{
	unsigned char* s;
	unsigned char* e;
	unsigned char* p;
	unsigned char* q;
	int active;
	int count;
	int top;
	int passes;
	int handle;
	int v10;
	int v11;
	int v12;

	active = 0;
	count = 0;
	top = 0;
	for (s = g_slot_table; (int) s < 0x85a0a0; s += 0x21c) {
		if (*(short*) s != -1 && s[8])
			active++;
	}
	for (s = g_slot_table + 2; (int) s < 0x85a0a2; s += 0x21c) {
		e = s - 2;
		if (*(short*) e == -1 || !s[6] || s[0] != 3)
			continue;
		if ((((gm_RandomMod(4) & 0xffff) + 0x2c <= *(unsigned short*) (s + 8)) || 652.8f <= (float) active)
		    && !s[0x164] && !s[0x166] && !s[0x167]) {
			if (fcn_004ff860(e)) {
				v10 = (int) (-(*(float*) (s + 0x1a) + 1.0f));
				fcn_004ff210(*(unsigned short*) e, v10);
				active--;
			}
		}
	}
	for (s = g_slot_table + 2; (int) s < 0x85a0a2; s += 0x21c) {
		e = s - 2;
		if (*(short*) e == -1 || s[6] < 2)
			continue;
		if (!(652.8f <= (float) active)) {
			if (s[0] == 8) {
				p = (unsigned char*) fcn_00508e40(*(int*) (s + 0x60));
				q = (unsigned char*) fcn_00508e40(*(int*) (s + 0x64));
				if ((!p || p[2] == 0x0f) && (!q || q[2] == 0x0f)) {
					if (fcn_004ff860(e)) {
						v10 = (int) (-(*(float*) (s + 0x1a) + 1.0f));
						fcn_004ff210(*(unsigned short*) e, v10);
						active--;
					}
					continue;
				}
			}
		}
		if (s[0] == 8 && !fcn_004fffb0(*(unsigned short*) e)) {
			p = (unsigned char*) fcn_00508e40(*(int*) (s + 0x60));
			q = (unsigned char*) fcn_00508e40(*(int*) (s + 0x64));
			if ((p && p[2] != 0x0f) || (q && q[2] != 0x0f))
				continue;
			v11 = 3;
			v12 = 2;
			fcn_004c4510(e, *(int*) (s + 4));
			fcn_004c4700(1, 1, (short) ((int) s - g_aed32c), &v11);
			if (s[0xb] < 2)
				fcn_004c4700(1, 1, (short) ((int) s - g_aed32c + 0xb), &v12);
			fcn_004c53a0();
			fcn_004c51a0(*(int*) (s + 4), -1, g_773d75,
				((gm_RandomMod(0x800) & 0xffff) + 0x800) * v12 * 0x20);
			count++;
			continue;
		}
		if (fcn_0047dd60(e)) {
			count++;
			if (*(int*) (s + 0x1f0))
				top++;
		}
	}
	if (top <= 5 && !gm_RandomMod(4)) {
		handle = fcn_004c4fc0(0x10, -1, -1, gm_RandomMod(4) + 0x10, -1, 0, 0, 0);
		if (handle != -1) {
			while (!fcn_004c4450(handle)) {
				fcn_00535960();
			}
		}
		if (fcn_004c4450(handle) == 1) {
			count++;
			handle = (int) fcn_004c4480(handle);
			v10 = ((gm_RandomMod(0x2000) & 0xffff) + 10000) * 0x40;
			fcn_004c51a0(*(int*) (handle + 4), -1, g_773d75, v10);
		}
	}
	if (652.8f <= (float) active) {
		if (count < 0x1e)
			v10 = (0x28 - count) / 2;
		else if (count < 0x28)
			v10 = (gm_RandomMod(2) & 0xffff) + 1;
		else
			v10 = 0;
		while (v10 >= 1) {
			passes = gm_RandomMod(0xc);
			handle = fcn_004c4fc0(3, -1, -1, 0x14, -1,
				fcn_00507400((gm_RandomMod(2) & 0xffff) + 1, (passes & 0xffff) + 1), 0, 2);
			if (handle != -1) {
				while (!fcn_004c4450(handle)) {
					fcn_00535960();
				}
			}
			if (fcn_004c4450(handle) == 1) {
				v11 = (gm_RandomMod(0xc) & 0xffff) + 10;
				handle = (int) fcn_004c4480(handle);
				passes = gm_RandomMod(0x400);
				fcn_004c51a0(*(int*) (handle + 4), -1, g_773d75,
					((passes & 0xffff) + 0x400) * 0x40);
				fcn_004c4510(handle, *(int*) (handle + 4));
				fcn_004c4700(1, 1, (short) (handle - g_aed32c + 0x167), &v11);
				fcn_004c53a0();
			}
			v10--;
		}
	}
}
