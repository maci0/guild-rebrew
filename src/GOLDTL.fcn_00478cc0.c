
// if (rows > 0) while (rows != 0) {...}, not a do-while: that form puts dst
// and rows in the dead surf/spr parameter slots like the reference.

typedef struct Surf0478cc0 {
	char pad0[0x10];
	int pitch;
	char pad14[8];
	unsigned short* bits;
} Surf0478cc0;
// SIZE 0x20

void __cdecl fcn_00478cc0(int x, int y, Surf0478cc0* surf, unsigned char* spr)
{
	unsigned short* dst;
	unsigned short* d;
	unsigned short* src;
	unsigned int* run;
	unsigned int* cnt;
	unsigned int i;
	unsigned int k;
	int rows;

	run = (unsigned int*)(spr + 0x36);
	cnt = (unsigned int*)(spr + 0x32);
	dst = surf->bits + (y * surf->pitch + x);
	rows = *(unsigned short*)(spr + 0xa);
	if (rows > 0) {
		while (rows != 0) {
			d = dst;
			for (k = 0; k < *cnt; k++) {
				d += run[0] / 2;
				src = (unsigned short*)(run + 2);
				for (i = 0; i < run[1]; i++) {
					*d++ = *src++;
				}
				run = (unsigned int*)(run[1] * 2 + (char*)run + 8);
			}
			cnt = run;
			run = run + 1;
			rows--;
		}
	}
}
