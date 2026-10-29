int __cdecl fcn_005809a0(int a1);
struct unit;
void __cdecl fcn_00546190(struct unit*);

/* ADDRESS: GOLDTL 0x0055af10 */
void __cdecl fcn_0055af10(char* o)
{
	if (fcn_005809a0((int) o) != 0) {
		fcn_00546190((struct unit*) o);
	} else {
		*(int*) (o + 0x70) = 0;
	}
}
