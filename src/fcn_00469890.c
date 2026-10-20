extern int __cdecl fcn_00465920(void);

/* ADDRESS: GOLDTL 0x00469890 */
int __cdecl fcn_00469890(void)
{
	int id;
	int off;
	int* tbl;
	int* rec;
	int i;

	id = fcn_00465920();
	if (id == -1) {
		return -1;
	}
	off = id * 0x2f4;
	tbl = *(int**) 0x772540;
	rec = (int*) (*(int*) 0x1015ea0 + off);
	for (i = 0x3ff; i >= 0; i--) {
		if (tbl[i] != 0) {
			break;
		}
	}
	i++;
	if (i < 0) {
		i = 0;
	}
	tbl[i] = (int) rec;
	if (id > *(int*) 0x772528) {
		*(int*) 0x772528 = id;
	}
	*(int*) (*(int*) 0x1015ea0 + off + 4) = 1;
	return id;
}
