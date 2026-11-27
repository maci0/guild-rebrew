

void __cdecl d3_SetObjectRotation(char*, void*);

void __cdecl d3_SetObjectEulerRotation(int object, int x, int y, int z)
{
	int buf[3];

	buf[0] = x;
	buf[1] = y;
	buf[2] = z;
	d3_SetObjectRotation((char*) object, buf);
}
