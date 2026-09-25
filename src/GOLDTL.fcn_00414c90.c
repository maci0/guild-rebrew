// FUNCTION: GOLDTL 0x00414c90
// SIZE: 144

// SIZE 0x3
typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
} Rgb;

extern int g_67a370;
void __cdecl fcn_004379a0(int a, char* e, int mask, void (__cdecl* cb)(void), Rgb* c);
void __cdecl fcn_00414c70(void);

void __cdecl fcn_00414c90(char* e, unsigned char r, unsigned char g, unsigned char b)
{
	Rgb c;
	int saved;

	c.r = r;
	c.g = g;
	c.b = b;
	if (e == 0) {
		return;
	}
	if ((*(unsigned char*) (e + 0x214) & 1) == 0) {
		saved = *(int*) (e + 0x1f4);
		*(int*) (e + 0x1f4) = 0;
		fcn_004379a0(g_67a370, e, 0x1ff, fcn_00414c70, &c);
		*(int*) (e + 0x1f4) = saved;
		return;
	}
	fcn_004379a0(g_67a370, e, 0x1ff, fcn_00414c70, &c);
}
