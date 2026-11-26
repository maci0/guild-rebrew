

int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(void*, int, int);
void __cdecl fcn_0058ee70(int);

void __cdecl fcn_0058ff00(int a)
{
	int v;

	while (main_RunFrameLoop(fcn_0058ff00, 0x67fff)) {
		v = RegisterStatusText((void*) 0x6a9958, *(int*) 0x14b58c4, 0x16);
		if (*(int*) 0x7746a0 != 0 && *(int*) 0x7746a0 == v) {
			fcn_0058ee70(a);
		}
	}
}
