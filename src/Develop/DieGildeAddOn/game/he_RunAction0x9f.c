


int __cdecl he_FreeAction(int*);

int __cdecl he_RunAction0x9f(int* event)
{
	int state;

	state = *(int*) ((char*) event + 0x70);
	if (state == -1 || state == -2) {
		return he_FreeAction(event);
	}
	return state;
}
