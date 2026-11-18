


int __cdecl fcn_004c6c30(char*);

int __cdecl fcn_004f2ba0(char* a1, char* a2, int a3)
{
	char buf[0x20];
	int value;

	if (a2 == 0) {
		return -1;
	}
	if (a1 == 0) {
		value = -1;
	} else {
		value = *(int*) (a1 + 4);
	}
	*(int*) (buf + 4) = value;
	*(int*) (buf + 8) = *(int*) (a2 + 1);
	*(int*) buf = 4;
	*(int*) (buf + 0xc) = a3;
	buf[0x10] = 0;
	*(short*) (buf + 0x11) = 0;
	*(int*) (buf + 0x13) = 0;
	return fcn_004c6c30(buf);
}
