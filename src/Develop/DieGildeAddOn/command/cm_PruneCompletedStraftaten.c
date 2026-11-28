extern char g_9a3825[];
int __cdecl cm_SendRemoveStraftat(int id, int v);
char* __cdecl he_StartHandlungSearch(int a1, int a2, int a3);
int __cdecl cm_GetCommandStatus(int i);
void __cdecl cm_StepCommandQueue(void);

/* ADDRESS: GOLDTL 0x004f5830 */
/* ADDRESS: GOLDDE 0x004e18d0 */
void __cdecl cm_PruneCompletedStraftaten(void)
{
	int cursor;
	int handle;
	int count;

	handle = -1;
	count = 0;
	for (cursor = (int) &g_9a3825; cursor < ((int) &g_9a3825 + 0x5a00); cursor += 0x2d) {
		if (*(unsigned int*) cursor == 1) {
			handle = cm_SendRemoveStraftat(*(int*) (cursor - 0x25), 0);
			count++;
		} else if (*(unsigned int*) cursor > 1) {
			if (he_StartHandlungSearch(1, 1, *(int*) cursor) == 0) {
				handle = cm_SendRemoveStraftat(*(int*) (cursor - 0x25), 1);
				count++;
			}
		}
		if (count >= 0x20) {
			if (handle != -1) {
				while (1) {
					if (cm_GetCommandStatus(handle) != 0) {
						break;
					}
					cm_StepCommandQueue();
				}
			}
			handle = -1;
			count = 0;
		}
	}
}
