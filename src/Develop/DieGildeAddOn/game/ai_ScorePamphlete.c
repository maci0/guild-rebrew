int __cdecl fcn_004f4830(int, void*);
int __cdecl fcn_004a4680(void*, void*, int, int, void*);
int __cdecl fcn_004a4410(void*, void*, int, int, int, int, int);

/* ADDRESS: GOLDTL 0x0049ca80 */
int __cdecl ai_ScorePamphlete(int* firstScore, int* secondScore, int a3, int a4, int a5, int a6, int a7)
{
	char local[0x24];

	if (a5 != 0) {
		*firstScore = (int) 0xf149f2ca;
		*secondScore = (int) 0xf149f2ca;
		return 0;
	}
	*firstScore = 0;
	*secondScore = 0;
	fcn_004f4830(3, local);
	if (*(int*) (local + 0x18) != 0) {
		return fcn_004a4680(firstScore, secondScore, a3, a4, local);
	}
	return fcn_004a4410(firstScore, secondScore, a3, a4, 0, a6, a7);
}
