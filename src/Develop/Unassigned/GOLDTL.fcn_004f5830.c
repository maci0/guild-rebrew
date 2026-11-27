int __cdecl cm_SendRemoveStraftat(int id, int v);
char* __cdecl he_StartHandlungSearch(int a1, int a2, int a3);
int __cdecl cm_GetCommandStatus(int i);
void __cdecl cm_StepCommandQueue(void);

/* ADDRESS: GOLDTL 0x004f5830 */
void __cdecl fcn_004f5830(void)
{
	int cursor;
	int handle;
	int count;

	handle = -1;
	count = 0;
	for (cursor = 0x9a3825; cursor < 0x9a9225; cursor += 0x2d) {
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
