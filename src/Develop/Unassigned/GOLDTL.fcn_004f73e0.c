


int  __cdecl fcn_005d97f0(void*, void*);
extern char g_679060[];
void __cdecl io_FormatTextBuffer(void*, int, int);

int __cdecl fcn_004f73e0(void* entity, void* context)
{
	int result;

	result = 2;
	if (*(int*) context != 3 && *(int*) context != 1) {
		return 1;
	}
	if (*(char*) ((char*) entity + 2) != 6 && *(char*) ((char*) entity + 2) != 5) {
		return 1;
	}
	if (*(int*) context == 3 && *(char*) ((char*) entity + 2) == 6) {
		result = fcn_005d97f0(entity, context) | 2;
	} else if (*(int*) context == 1 && *(char*) ((char*) entity + 2) == 6) {
		io_FormatTextBuffer((char*) context + 0x14, (int) g_679060, 0x1d35);
	}
	return result;
}
