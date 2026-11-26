

void __cdecl fcn_00414be0(char*, char, char, char);

char __cdecl d3_SetObjectColorBytes(char* object, char* rgb)
{
	fcn_00414be0(object, rgb[0], rgb[1], rgb[2]);
	return 1;
}
