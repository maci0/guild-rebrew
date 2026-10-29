

// SIZE 0x8
typedef struct Count {
	int n;
	int flags;
} Count;

extern int g_67a370;
extern int g_6b8300;

void __cdecl fcn_00459be0(unsigned int);
void __cdecl fcn_004379a0(int, int, int, void*, void*);
void __cdecl fcn_0045a200(void);
int __cdecl fcn_00459d90(int, int);
int __cdecl fcn_00459d50(int);

int __cdecl fcn_0045a230(int mask, int flags, char keep)
{
	Count c;
	int r;

	if (keep == 0) {
		fcn_00459be0(0);
	}
	c.flags = flags | 0x114;
	c.n = 0;
	fcn_004379a0(g_67a370, 0, mask, fcn_0045a200, &c);
	if ((flags & 0x200) != 0 && g_6b8300 != 0) {
		c.n += fcn_00459d90(g_6b8300, 1);
		r = c.n;
	} else {
		r = c.n;
	}
	if ((flags & 0x400) != 0 && *(int*) (g_67a370 + 0xb0) != 0) {
		r += fcn_00459d50(*(int*) (g_67a370 + 0xb0));
	}
	return r;
}
