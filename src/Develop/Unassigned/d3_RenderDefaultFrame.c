

void __cdecl d3_RenderFrame(int, int, int);

void __cdecl d3_RenderDefaultFrame(void)
{
	if (*(char*) 0x6b8018 == 0) {
		return;
	}
	if (*(int*) 0x6b86d4 > 0) {
		return;
	}
	d3_RenderFrame(0x40, 1, 1);
}
