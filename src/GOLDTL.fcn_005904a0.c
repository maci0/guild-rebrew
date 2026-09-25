// FUNCTION: GOLDTL 0x5904a0
// SIZE: 91

char* __cdecl fcn_0050dc90(int);
int __cdecl fcn_00426cc0(int);
void __cdecl fcn_00428720(int);

void __cdecl fcn_005904a0(char* obj, unsigned int flag)
{
	int id;
	int h;

	if (*(int*) (obj + 0x16c) != 0 && obj == fcn_0050dc90(*(int*) (obj + 0x16c))) {
		return;
	}
	id = *(int*) (*(char**) (obj + 0x184) + 0x28);
	if (id != -1) {
		h = fcn_00426cc0(id);
		if (h != 0) {
			fcn_00428720(h);
		}
	}
	*(unsigned int*) (obj + 0x1b4) ^= (*(unsigned int*) (obj + 0x1b4) ^ flag) & 1;
}
