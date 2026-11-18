

void __cdecl fcn_00438cb0(char*, void*);

void __cdecl fcn_00438d70(int object, int x, int y, int z)
{
	int buf[3];

	buf[0] = x;
	buf[1] = y;
	buf[2] = z;
	fcn_00438cb0((char*) object, buf);
}
