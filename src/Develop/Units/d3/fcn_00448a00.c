typedef struct {
	char pad_000[0x1fc];
	int f1fc;
} ITEM_448a00;

void *__cdecl vfs_Tfopen(void *, int, int);
void __cdecl fcn_00401360(void *, int);
void __cdecl fcn_00446540(void *, ITEM_448a00 *);
void __cdecl CloseVfsStream(void *);
void __cdecl fcn_0041d9e0(char *);
void __cdecl d3_UnlinkObject(ITEM_448a00 *);
void __cdecl fcn_00439c00(int, ITEM_448a00 *);

/* ADDRESS: GOLDTL 0x00448a00 */
void __cdecl fcn_00448a00(void *a1, int count, ITEM_448a00 **list)
{
	void *cont;
	ITEM_448a00 *p;
	int i;
	char found;
	int val;

	if (count <= 0)
		return;
	found = 0;
	for (i = 0; i < count; i++) {
		p = list[i];
		if (found != 0) {
			if (val != p->f1fc) {
				fcn_0041d9e0((char *) 0x67ac48);
				return;
			}
		} else {
			val = p->f1fc;
			found = 1;
		}
	}
	if (val == 0) {
		cont = vfs_Tfopen(a1, 0x6790b0, *(int *) 0x6b7fdc);
		fcn_00401360(cont, 0x3a6c00bb);
		fcn_00401360(cont, count);
		for (i = 0; i < count; i++)
			fcn_00446540(cont, list[i]);
	} else {
		for (i = 0; i < count; i++) {
			d3_UnlinkObject(list[i]);
			fcn_00439c00(val, list[i]);
		}
		cont = vfs_Tfopen(a1, 0x6790b0, *(int *) 0x6b7fdc);
		fcn_00401360(cont, 0x3a6c00bb);
		fcn_00401360(cont, 1);
		fcn_00446540(cont, list[0]);
	}
	CloseVfsStream(cont);
}
