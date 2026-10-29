int __cdecl fcn_0064f170(void*, char*, int);
void __cdecl fcn_00442a30(int, int, int, int);

/* ADDRESS: GOLDTL 0x004e6da0 */
char __cdecl fcn_004e6da0(char* obj, int* id)
{
	int kind;
	int who;

	who = *id;
	kind = *(int*) (obj + 0x220);
	if (kind != 2 && kind != 4 && kind != 3) {
		if (fcn_0064f170(obj, (char*) 0x68d6fc, 4) != 0
		    && fcn_0064f170(obj, (char*) 0x68d6f8, 3) != 0
		    && fcn_0064f170(obj, (char*) 0x68d6f0, 4) != 0) {
			fcn_00442a30((int) obj, *(int*) (obj + 0x1cc), who, 1);
		}
	}
	return 1;
}
