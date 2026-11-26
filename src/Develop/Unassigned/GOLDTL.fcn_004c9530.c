

void __cdecl main_ExitToFrameHandler(int);

int __cdecl fcn_004c9530(int a1, char* p)
{
	main_ExitToFrameHandler(0x5438c0);
	if (p != 0) {
		*p = 1;
	}
	return 0;
}
