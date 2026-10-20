extern void __cdecl fcn_005338a0(void);
extern int __cdecl fcn_005338d0(char* name, int a, int b);
extern int __cdecl fcn_005373e0(int fn, int delay);
extern void __cdecl fcn_005ad000(char* obj);

#define SOUND_FLAG (*(unsigned char*) (0x7f4e51 + *(unsigned short*) 0x774970 * 0x21c))

/* ADDRESS: GOLDTL 0x005ad260 */
void __cdecl fcn_005ad260(char* a0)
{
	int handle;
	int wait;

	handle = 0;
	fcn_005338a0();
	wait = SOUND_FLAG > 0 ? 0x677ff : 0x67fff;
	if (fcn_005373e0(0x5ad260, wait) == 0)
		return;
	do {
		if (SOUND_FLAG > 0)
			handle = fcn_005338d0((char*) 0x6ab1a4, *(int*) 0x14ab9e0, 0x10);
		if (SOUND_FLAG > 0 && *(int*) 0x7746a0 != 0 &&
		    *(unsigned short*) (a0 + 0x27) != 0xffff && *(int*) 0x7746a0 == handle)
			fcn_005ad000(a0);
		wait = SOUND_FLAG > 0 ? 0x677ff : 0x67fff;
	} while (fcn_005373e0(0x5ad260, wait) != 0);
}
