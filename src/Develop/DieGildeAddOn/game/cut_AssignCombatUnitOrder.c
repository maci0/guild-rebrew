extern char* d3_ActiveScene;
extern float g_664330;

char* __cdecl gm_GetEquippedCombatGear(char*);
unsigned short* __cdecl gm_FindEntityActiveItem(char*);
char __cdecl d3sm_3D2SuperMap(char*, float*, int*, int*, float*);
unsigned char* __cdecl cut_FindCombatTarget(char*);
int __cdecl gm_FindBestCombatCell(char*, int, int, int, unsigned int*, unsigned int*);
int __cdecl cut_AssignTargetOrder(char*, char*, char*, int, int);
char* __cdecl d3_FindNearestEnemyWare(char*);
int __cdecl he_QueueTradeWareCommand(char*, char*, char*);
char* __cdecl d3_FindNearestConquerNode(char*);
int __cdecl cut_AssignConquerTarget(char*, char*, char*);
void __cdecl cut_SendExitSlotCommand(char*, char*);
int __cdecl cut_AssignGuardOrder(char*, char*);
char* __cdecl d3_FindNearestEscapeNode(char*);
int __cdecl gm_IssueEscapeOrder(char*, char*, char*);

/* ADDRESS: GOLDTL 0x004d4250 */
/* ADDRESS: GOLDDE 0x004c1470 */
void __cdecl cut_AssignCombatUnitOrder(char* rec, char* e)
{
	char* obj;
	char* map;
	unsigned int gridX;
	float f4;
	unsigned int grid_z;
	if (!e || !*(char**) (e + 0x184) || (*(char*) (e + 8) && *(int*) (*(char**) (*(char**) (e + 0x184) + 0x34) + 0x218) != 1)) {
		switch (*(unsigned char*) (e + 0x1c4)) {
		case 0:
			obj = gm_GetEquippedCombatGear(e);
			if (*(int*) (obj + 0x58) == 1 || *(int*) (obj + 0x58) == 2) {
				if (*(int*) ((char*) gm_FindEntityActiveItem(e) + 0x20) <= 0) {
					break;
				}
			}
			if (*(int*) (obj + 0x58) == 2) {
				map = *(char**) (d3_ActiveScene + 0xb0);
				if (d3sm_3D2SuperMap(map, (float*) (*(char**) (*(char**) (e + 0x184) + 0x34) + 0x4c), (int*) &gridX, (int*) &grid_z, &f4)) {
					obj = (char*) gm_FindBestCombatCell(e, gridX, (int) grid_z, (int) (g_664330 / *(float*) (map + 0x10)), &gridX, &grid_z);
					if (obj != 0) {
						cut_AssignTargetOrder(rec, e, 0, gridX, (int) grid_z);
						return;
					}
				}
			} else {
				obj = (char*) cut_FindCombatTarget(e);
				if (obj != 0) {
					cut_AssignTargetOrder(rec, e, obj, 0, 0);
					return;
				}
			}
			break;
		case 5:
			obj = d3_FindNearestEscapeNode(e);
			if (obj != 0) {
				gm_IssueEscapeOrder(rec, e, obj);
				return;
			}
			break;
		case 1:
			obj = d3_FindNearestEnemyWare(e);
			if (obj != 0) {
				he_QueueTradeWareCommand(rec, e, obj);
				return;
			}
			break;
		case 2:
			obj = d3_FindNearestConquerNode(e);
			if (obj != 0) {
				cut_AssignConquerTarget(rec, e, obj);
				return;
			}
			break;
		case 4:
			cut_AssignGuardOrder(rec, e);
			return;
		case 3:
			cut_SendExitSlotCommand(rec, e);
			break;
		}
	}
}
