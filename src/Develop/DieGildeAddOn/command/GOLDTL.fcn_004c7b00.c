extern int nt_ClientSocket;
extern int gm_NextEntityId;
extern char gm_TownTable[];

int __cdecl cm_ResolveSpecialEntityId(char*, int);
int __cdecl gm_RemoveObjectQuantity(int, int, int);
int __cdecl gm_AddObjekt(int, int, int);


/* ADDRESS: GOLDTL 0x004c7b00 */
int __cdecl fcn_004c7b00(unsigned char* command, char* result)
{
	int v;

	if (nt_ClientSocket != -1)
		gm_NextEntityId = *(int*) (command + 0x18);
	if (*(int*) (command + 0x14) != -1) {
		v = cm_ResolveSpecialEntityId((char*) command, *(int*) (command + 0x14));
		*(int*) (command + 0x14) = v;
		if (gm_RemoveObjectQuantity(v, *(unsigned short*) (gm_TownTable + command[0x1c] * 756 + 0x54), *(int*) (command + 0x1d)) == 0)
			return 1;
	}
	if (*(int*) (command + 0x10) != -1) {
		v = cm_ResolveSpecialEntityId((char*) command, *(int*) (command + 0x10));
		*(int*) (command + 0x10) = v;
		if (gm_AddObjekt(v, *(unsigned short*) (gm_TownTable + command[0x1c] * 756 + 0x54), *(int*) (command + 0x1d)) == 0)
			return 1;
	}
	if (result != 0)
		result[0] = 1;
	return 0;
}
