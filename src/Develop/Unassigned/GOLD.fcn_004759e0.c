extern int g_f8f080;

int __cdecl fcn_004690a0(int);

/* ADDRESS: GOLD 0x004759e0 */
int __cdecl fcn_004759e0(int id, int* out)
{
	int slot;
	char* rec;
	char* font;
	int kind;
	unsigned short w;

	if (id == -1) {
		return 0;
	}
	slot = id;
	slot = (slot << 5) - id;
	slot = slot + slot * 2;
	slot = id + slot * 2;
	rec = (char*) (g_f8f080 + slot * 4);
	kind = *(int*) (rec + 0x18);
	if (kind != 1 && kind != 8 && kind != 5) {
		return 0;
	}
	font = (char*) fcn_004690a0(*(int*) (rec + 8));
	if (font == 0) {
		return 0;
	}
	kind = *(int*) (rec + 0x18);
	if (kind == 8 || kind == 5) {
		font = font + *(int*) (font + *(int*) (rec + 0x78) * 4 + 0x45);
		if (font != 0) {
			w = *(unsigned short*) (font + 6);
			*out = w;
			w = *(unsigned short*) (font + 0xa);
			*out = w;
		}
		return 1;
	}
	w = *(unsigned short*) (font + 0x2c);
	*out = w;
	w = *(unsigned short*) (font + 0x2e);
	*out = w;
	return 1;
}
