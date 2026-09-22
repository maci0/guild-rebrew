// FUNCTION: SERVER 0x1000d330
// FUNCTION: GOLDTL 0x4c75e0
// SIZE: 14

int __cdecl cm_MarkAndReturn(int cmd, char* result)
{
	(void) cmd;
	if (result != (char*) 0x0) {
		*result = '\x01';
	}
	return 0;
}
