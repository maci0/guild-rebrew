extern volatile int g_6b7fb0;
extern int g_772600;

void __cdecl d2_ClearAnimationSlot(int index);

/* ADDRESS: GOLDTL 0x0047a090 */
void __cdecl d2_UpdateAnimations(void)
{
	int delta;
	int ebp;
	int index;
	char* p;
	char* obj;
	unsigned char c;
	char cl;
	unsigned short ax;

	ebp = 1;
	if (g_6b7fb0 - g_772600 == 0) {
		return;
	}
	delta = (unsigned int) (g_6b7fb0 - g_772600) < 1U ? 1 : g_6b7fb0 - g_772600;
	g_772600 = g_6b7fb0;
	index = 0;
	for (p = (char*) 0x100e7a4; (int) p < 0x100eb64; p += 0x14, index++) {
		obj = *(char**) (p - 4);
		if (obj == 0 || *(signed char*) p < 0) {
			continue;
		}
		p[1] += (char) delta;
		if ((unsigned char) p[1] <= 1) {
			continue;
		}
		cl = p[8];
		if (cl == 0) {
			p[0]++;
		}
		if (cl == 1) {
			p[0]--;
		}
		c = (unsigned char) p[0];
		p[1] = 0;
		if ((signed char) c == 0x19) {
			p[0] = 0x19;
		}
		if (*(signed char*) p >= *(unsigned short*) (obj + 4) && cl == 0) {
			if (obj[0x14] == 0) {
				p[0] = 0;
				*(short*) (p + 2) = 0;
			}
			if (obj[0x14] == 1) {
				p[0] = (char) 0xff;
				*(short*) (p + 2) = 0;
			}
			if (obj[0x14] == 3) {
				p[0] = 0;
				*(short*) (p + 2) = 0;
				d2_ClearAnimationSlot(index);
			}
			ebp = 0;
		}
		c = (unsigned char) p[0];
		if ((signed char) c < 0 && p[8] == 1) {
			if (obj[0x14] == 0) {
				c = (unsigned char) (obj[4] - 2);
				p[0] = (char) c;
				*(short*) (p + 2) = (short) (signed char) c;
			}
			if (obj[0x14] == 1) {
				p[0] = (char) 0xff;
				*(short*) (p + 2) = 0;
			}
			if (obj[0x14] == 3) {
				p[0] = 0;
				*(short*) (p + 2) = 0;
				d2_ClearAnimationSlot(index);
			}
			ebp = 0;
		} else if (ebp != 0) {
			*(short*) (p + 2) = (short) (signed char) c;
		}
		obj = *(char**) (p - 4);
		ax = *(unsigned short*) (obj + 4);
		if (*(unsigned short*) (p + 2) > ax) {
			*(unsigned short*) (p + 2) = (unsigned short) (ax - 1);
		}
	}
}
