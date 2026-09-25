// FUNCTION: GOLDTL 0x58ff00
// SIZE: 95

int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(void*, int, int);
void __cdecl fcn_0058ee70(int);

void __cdecl fcn_0058ff00(int a)
{
	int v;

	while (fcn_005373e0(fcn_0058ff00, 0x67fff)) {
		v = fcn_005338d0((void*) 0x6a9958, *(int*) 0x14b58c4, 0x16);
		if (*(int*) 0x7746a0 != 0 && *(int*) 0x7746a0 == v) {
			fcn_0058ee70(a);
		}
	}
}
