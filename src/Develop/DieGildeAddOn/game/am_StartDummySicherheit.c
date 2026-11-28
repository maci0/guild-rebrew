
/* ADDRESS: GOLDTL 0x00495990 */
/* ADDRESS: GOLDDE 0x00484440 */
int __cdecl am_StartDummySicherheit(int actorKind, int unused, int busy)
{
	if (actorKind != 0) {
		return 0;
	}
	return (busy != 0) ? 0 : 7;
}
