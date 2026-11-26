


int __cdecl amt_SendSameOfficeCommand(char*, int, int);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_00535960(void);

int __cdecl amt_SendAndWaitOfficeCommand(char* entity, int firstEntity, int secondEntity)
{
	int handle;

	handle = amt_SendSameOfficeCommand(entity, firstEntity, secondEntity);
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
