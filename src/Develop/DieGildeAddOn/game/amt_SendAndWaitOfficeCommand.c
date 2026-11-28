


int __cdecl amt_SendSameOfficeCommand(char*, int, int);
int __cdecl cm_GetCommandStatus(int);
void __cdecl cm_StepCommandQueue(void);

/* ADDRESS: GOLDDE 0x005b8e30 */
int __cdecl amt_SendAndWaitOfficeCommand(char* entity, int firstEntity, int secondEntity)
{
	int handle;

	handle = amt_SendSameOfficeCommand(entity, firstEntity, secondEntity);
	if (handle != -1) {
		if (entity[2] == 6) {
			while (cm_GetCommandStatus(handle) == 0) {
				cm_StepCommandQueue();
			}
			return cm_GetCommandStatus(handle) != 2;
		}
		return 1;
	}
	return 0;
}
