int __cdecl d2_BindTutorialAction(int a1);
struct unit;
void __cdecl he_FreeAction(struct unit*);

/* ADDRESS: GOLDTL 0x0055af10 */
/* ADDRESS: GOLDDE 0x005411c0 */
void __cdecl he_StartTutorialEvent(char* o)
{
	if (d2_BindTutorialAction((int) o) != 0) {
		he_FreeAction((struct unit*) o);
	} else {
		*(int*) (o + 0x70) = 0;
	}
}
