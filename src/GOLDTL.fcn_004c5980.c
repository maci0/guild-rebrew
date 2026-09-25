// FUNCTION: GOLDTL 0x4c5980
// SIZE: 46

int __cdecl fcn_004c4330(char*);
void __cdecl fcn_004c4df0(int, void*);

int __cdecl fcn_004c5980(void* data)
{
	char buf[0x9c];

	buf[0] = 0x27;
	fcn_004c4df0(0x114, data);
	return fcn_004c4330(buf);
}
