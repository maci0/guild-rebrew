typedef struct
{
	int f0;
	int f4;
	int f8;
} S436a00_Flags;

int __cdecl fcn_004321a0(S436a00_Flags flags, int a3, int v, int lo, int hi);
void __cdecl fcn_00438ac0(int a1, int a2);

/* ADDRESS: GOLDTL 0x00436a00 */
void __cdecl fcn_00436a00(int arg0, char* p, int index)
{
	char* owner;
	int count;

	if (p != 0 && (owner = *(char**) (p + 0x68)) != 0) {
		count = *(int*) (owner + 0x154);
		if (index >= count) {
			index = count - 1;
		}
		if (index < 0) {
			index = count - 1;
		}
		if (index + 1 >= count) {
			*(int*) (p + 8) = *(int*) (*(char**) (owner + 0x15c) + index * 0xc0 + 4) - 1;
		}
		else {
			*(int*) (p + 8) = 0;
		}
		*(int*) p = index;
		*(int*) (p + 4) = fcn_004321a0(*(S436a00_Flags*) (p + 0x6c), index,
		    *(int*) (owner + 0x150), *(int*) (owner + 0x154), *(int*) (owner + 0x148));
		fcn_00438ac0(arg0, 1);
	}
}
