extern char d3_FoundSceneObject[];


int __cdecl fcn_0065f220(int, int);

/* ADDRESS: GOLDDE 0x004115f0 */
char __cdecl d3_MatchObjectNameCallback(int a1, int a2)
{
	if (fcn_0065f220(a1, a2) == 0) {
		*(int*) &d3_FoundSceneObject = a1;
		return 0;
	}
	return 1;
}
