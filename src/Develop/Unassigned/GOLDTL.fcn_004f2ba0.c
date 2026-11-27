


int __cdecl fcn_004c6c30(char*);

int __cdecl gv_RequestActivateSection(char* owner, char* entity, int fieldType)
{
	char buf[0x20];
	int value;

	if (entity == 0) {
		return -1;
	}
	if (owner == 0) {
		value = -1;
	} else {
		value = *(int*) (owner + 4);
	}
	*(int*) (buf + 4) = value;
	*(int*) (buf + 8) = *(int*) (entity + 1);
	*(int*) buf = 4;
	*(int*) (buf + 0xc) = fieldType;
	buf[0x10] = 0;
	*(short*) (buf + 0x11) = 0;
	*(int*) (buf + 0x13) = 0;
	return fcn_004c6c30(buf);
}
