


int __cdecl amt_SendSameOfficeCommand(char*, int, int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);

int __cdecl fcn_005d75d0(char* entity, int a2, int a3)
{
	int handle;

	handle = amt_SendSameOfficeCommand(entity, a2, a3);
	if (handle != -1) {
		if (entity[2] == 6) {
			while (fcn_004c4450(handle) == 0) {
				fcn_00535960();
			}
			return fcn_004c4450(handle) != 2;
		}
		return 1;
	}
	return 0;
}
