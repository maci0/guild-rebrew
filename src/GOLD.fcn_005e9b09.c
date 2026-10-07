// FUNCTION: GOLD 0x005e9b09
// fcn_005e9b09 — if(![0x14eae6c]){ fcn_005e9745(-3); [0x14eae6c]=1; }.

int __cdecl fcn_005e9745(int);

void __cdecl fcn_005e9b09(void)
{
	if (*(int*) 0x14eae6c == 0) {
		fcn_005e9745(-3);
		*(int*) 0x14eae6c = 1;
	}
}
