


extern char g_85ab90[];

float __cdecl eval_ObjektPreis2Credits(int, int);

float __cdecl fcn_0050bb50(int id, unsigned char a)
{
	int i;

	for (i = 0; i < 0x55; i++) {
		if (*(unsigned short*) (g_85ab90 + a * 0x2a90 + i * 0x80) == id) {
			return *(float*) (g_85ab90 + 0x38 + a * 0x2a90 + i * 0x80);
		}
	}
	return eval_ObjektPreis2Credits(id, 100);
}
