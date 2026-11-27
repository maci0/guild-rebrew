

int __cdecl main_RunFrameLoop(void*, int);
int __cdecl RegisterStatusText(void*, int, int);
void __cdecl d2_RunSeanceAction(int);

void __cdecl d2_RunFriedhofSeanceMenu(int a)
{
	int v;

	while (main_RunFrameLoop(d2_RunFriedhofSeanceMenu, 0x67fff)) {
		v = RegisterStatusText((void*) 0x6a9958, *(int*) 0x14b58c4, 0x16);
		if (*(int*) 0x7746a0 != 0 && *(int*) 0x7746a0 == v) {
			d2_RunSeanceAction(a);
		}
	}
}
