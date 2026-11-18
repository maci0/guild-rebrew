


int __cdecl fcn_00546190(int*);

int __cdecl fcn_0057c8d0(int* event)
{
	int state;

	state = *(int*) ((char*) event + 0x70);
	if (state == -1 || state == -2) {
		return fcn_00546190(event);
	}
	return state;
}
