


#include <string.h>

char* __cdecl ch_NewAction(int);
void __cdecl ch_ExecPlayAnimation(void);

/* ADDRESS: GOLDDE 0x00405550 */
char* __cdecl ch_NewAnimationAction(int a1, char* s, int a3, float a4)
{
	char* e;

	e = ch_NewAction(a1);
	if (e == 0) {
		return e;
	}
	*(int*) (e + 0x30) = a3;
	*(void**) e = (void*) ch_ExecPlayAnimation;
	e[9] = 0x2e;
	*(float*) (e + 0x178) = 1.0f;
	*(int*) (e + 0x28) = 0;
	e[0x10] = 0;
	strcpy(e + 0xf0, s);
	*(float*) (e + 0x178) = a4;
	return e;
}
