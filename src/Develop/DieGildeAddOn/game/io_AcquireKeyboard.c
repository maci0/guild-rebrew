

typedef int (__stdcall* INPUT_ACQUIRE_FN)(int*);

/* ADDRESS: GOLDDE 0x00410420 */
int __cdecl io_AcquireKeyboard(int acquire)
{
	int* obj;

#ifdef REBREW_GOLD
	obj = *(int**) 0x1467360;
#else
	obj = *(int**) 0x14ce8a0;
#endif
	if (obj == 0) {
		return 0;
	}
	if (acquire != 0) {
		if (((INPUT_ACQUIRE_FN) ((int*) *obj)[7])(obj) < 0) {
			return 0;
		}
	} else {
		((INPUT_ACQUIRE_FN) ((int*) *obj)[8])(obj);
	}
	return 1;
}
