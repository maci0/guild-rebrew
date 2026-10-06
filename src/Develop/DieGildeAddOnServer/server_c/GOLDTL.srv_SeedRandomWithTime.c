/* srv_SeedRandomWithTime — srand(timeGetTime()) thunk (0x1001a140).

 * Seeds the CRT random generator from the Win32 millisecond timer. Called
 * from gm_Open; the target is a bare thunk, so this returns nothing.
 */

// FUNCTION: GOLDTL 0x42e4b0

__declspec(dllimport) unsigned int __stdcall timeGetTime(void);
extern void __cdecl srand(unsigned int);

void __cdecl srv_SeedRandomWithTime(void)
{
	srand(timeGetTime());
}
