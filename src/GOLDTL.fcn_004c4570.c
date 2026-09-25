extern unsigned int g_aed208;
struct msgbuf_4c4570 {
	unsigned char n;
	unsigned char data[0x77];
};
// SIZE 0x78

extern struct msgbuf_4c4570 g_aed224;
extern char* g_aed32c;

// FUNCTION: GOLD 0x004c3c00
// SIZE: 244
// FUNCTION: GOLDTL 0x4c4570
// SIZE: 244

int __cdecl fcn_004c4570(unsigned char size, unsigned char count, unsigned short off, char* src)
{
	unsigned char* p;
	char* base;
	unsigned int need;
	unsigned int i;

	if (size != 1 && size != 2 && size != 4)
		return 1;
	need = count * size + g_aed208 + 4;
	if (need >= 0x77)
		return 1;
	p = g_aed224.data + g_aed208;
	g_aed208 = need;
	g_aed224.n++;
	*p++ = size;
	*p++ = count;
	*(unsigned short*) p = off;
	p += 2;
	base = g_aed32c + off;
	switch (size) {
	case 1:
		for (i = 0; i < count; i++)
			*p++ = *src++ - *base++;
		break;
	case 2:
		for (i = 0; i < count; i++) {
			*(short*) p = *(short*) src - *(short*) base;
			base += 2;
			p += 2;
			src += 2;
		}
		break;
	case 4:
		for (i = 0; i < count; i++) {
			*(int*) p = *(int*) src - *(int*) base;
			base += 4;
			p += 4;
			src += 4;
		}
		break;
	}
	return 0;
}
