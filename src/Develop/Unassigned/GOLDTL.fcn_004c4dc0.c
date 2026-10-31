extern char cm_LastEntityId[];
extern char cm_LastBuildingId[];
extern char cm_LastObjectId[];

/* ADDRESS: GOLD 0x004c4450 */
/* ADDRESS: GOLDTL 0x004c4dc0 */
int __cdecl fcn_004c4dc0(int a1, int a2)
{
	if (a2 == -2) {
		return *(int*) cm_LastEntityId;
	}
	if (a2 == -3) {
		return *(int*) cm_LastBuildingId;
	}
	if (a2 == -4) {
		return *(int*) cm_LastObjectId;
	}
	return a2;
}
