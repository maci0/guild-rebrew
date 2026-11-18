

void* __cdecl fcn_00423ac0(int);
int __cdecl fcn_00424700(int);

int __cdecl fcn_00423ce0(int a1)
{
	int* entry;
	int result;

	result = 0;
	entry = (int*) fcn_00423ac0(a1);
	if (entry != 0) {
		result = entry[0xd] + fcn_00424700(a1) * 12;
	}
	return result;
}
