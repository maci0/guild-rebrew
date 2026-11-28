

void __cdecl cm_FlushCommandQueue(void);
void __cdecl cm_PollCommandQueue(void);
void __cdecl cm_ExecCommand(void);

/* ADDRESS: GOLDDE 0x0051e1c0 */
void __cdecl cm_StepCommandQueue(void)
{
	cm_FlushCommandQueue();
	cm_PollCommandQueue();
	cm_ExecCommand();
}
