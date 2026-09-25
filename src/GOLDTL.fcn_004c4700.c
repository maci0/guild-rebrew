// FUNCTION: GOLDTL 0x4c4700
// SIZE: 210

extern unsigned int g_aed208;
extern unsigned char g_aed224;
extern char g_aed225[];

int __cdecl fcn_004c4700(unsigned char type, unsigned char count, short id, char* data)
{
	unsigned int size;
	unsigned int n;
	unsigned int i;
	char* p;

	if (type != 1 && type != 2 && type != 4)
		return 1;
	size = type * count;
	n = size + g_aed208 + 4;
	if (n >= 0x77)
		return 1;
	p = g_aed225 + g_aed208;
	g_aed224++;
	g_aed208 = n;
	*p++ = type;
	*p++ = count;
	*(short*) p = id;
	p += 2;
	switch (type) {
	case 1:
		for (i = 0; i < count; i++) {
			*p = *data;
			p++;
			data++;
		}
		break;
	case 2:
		for (i = 0; i < count; i++) {
			*(short*) p = *(short*) data;
			p += 2;
			data += 2;
		}
		break;
	case 4:
		for (i = 0; i < count; i++) {
			*(int*) p = *(int*) data;
			p += 4;
			data += 4;
		}
		break;
	}
	return 0;
}
