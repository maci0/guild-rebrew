


int __cdecl fcn_0064d470(const char*, const char*);

int __cdecl fcn_00513d00(char* name, int* list)
{
	if (fcn_0064d470(name, (char*) list + 0x804)) {
		list[list[0] + 1] = (int) name;
		list[0]++;
	}
	return list[0] < 0x200;
}
