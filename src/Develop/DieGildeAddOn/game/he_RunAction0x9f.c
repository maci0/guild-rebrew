


int __cdecl he_FreeAction(int*);

/* ADDRESS: GOLDDE 0x00562700 */
int __cdecl he_RunAction0x9f(int* event)
{
	int state;

	state = *(int*) ((char*) event + 0x70);
	if (state == -1 || state == -2) {
		return he_FreeAction(event);
	}
	return state;
}
