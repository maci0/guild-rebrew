


extern char g_679060[];

int __cdecl fcn_005dae70(unsigned char* a1, int* a2);
void __cdecl io_FormatTextBuffer(void*, int, ...);

int __cdecl fcn_004fa530(unsigned char* entity, int* context)
{
	int result;

	result = 2;
	if ((*context == 3 || *context == 1) && entity[0x166] != 0 && entity[0x166] <= 0x1b) {
		if (*context == 3 && entity[2] == 6) {
			return fcn_005dae70(entity, context);
		}
		if (*context == 1 && entity[2] == 6) {
			io_FormatTextBuffer((char*) context + 0x14, (int) g_679060, 0x1e23);
			return 2;
		}
	} else {
		result = 1;
	}
	return result;
}
