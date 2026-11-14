extern unsigned char* g_7e3f30;
extern float g_662910;
extern char* g_item_def_table;
unsigned short* __cdecl fcn_00502cd0(int container_id, int arg_count, ...);
float __cdecl fcn_00508820(int, int);

/* ADDRESS: GOLD 0x00509b40 */
int __cdecl fcn_00509b40(unsigned char* a0, int scale)
{
	unsigned char* row;
	unsigned short* words;
	unsigned short* ent;
	unsigned short* rec;
	unsigned char* kind;
	int acc;
	int i;
	int id;
	char seen;

	row = g_7e3f30 + *a0 * 0x24d;
	acc = *(int*) (row + 0x249) * 0xf00;
	ent = 0;
	seen = 0;
	i = 0;
	words = (unsigned short*) (row + 0x25);
	for (; i < 0x40; i++, words++) {
		if (words[-1] == 0) {
			break;
		}
		id = words[-1] & 0x7fff;
		kind = (unsigned char*) g_item_def_table + (id << 6) + id;
		if (!seen) {
			if (*kind != 2 && *kind != 6) {
				continue;
			}
			ent = fcn_00502cd0(*(int*) (a0 + 0x5d), 1, 0, id);
			if (ent == 0) {
				continue;
			}
			acc = (int) (fcn_00508820(ent[0], *((unsigned char*) ent + 0x12)) + acc);
			if (i >= 0x3f) {
				continue;
			}
			id = words[0] & 0x7fff;
			kind = (unsigned char*) g_item_def_table + (id << 6) + id;
			if (*kind != 2 && *kind != 6) {
				seen = 1;
			}
		} else if (ent != 0) {
			rec = fcn_00502cd0(*(int*) ((unsigned char*) ent + 0x14), 1, 0, id);
			if (rec != 0) {
				acc = (int) (fcn_00508820(rec[0], *((unsigned char*) rec + 0x12)) + acc);
			}
			if (i >= 0x3f) {
				continue;
			}
			id = words[0] & 0x7fff;
			kind = (unsigned char*) g_item_def_table + (id << 6) + id;
			if (*kind == 2 || *kind == 6) {
				seen = 0;
			}
		}
	}
	return (int) (acc * (scale * g_662910));
}
