

int __cdecl fcn_0064d470(const char*, const char*);

char __cdecl fcn_0055d5e0(char* name, int* list)
{
	if (fcn_0064d470(name, "dummy_TRANSPORTER")) {
		list[list[0x20]] = (int) name;
		list[0x20]++;
	}
	return list[0x20] < 0x20;
}
