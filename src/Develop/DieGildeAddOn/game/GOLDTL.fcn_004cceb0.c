


char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
void __cdecl fcn_004cfc40(char*, int, int);

int __cdecl fcn_004cceb0(char* request, char* output)
{
	char* target;

	target = gm_LookupEntityRecordIn32SlotTable(*(int*) (request + 0x10));
	if (target != 0) {
		fcn_004cfc40(target, *(int*) (request + 0x14), 0);
		*(int*) (target + 0x24) -= *(int*) (request + 0x14);
		target[8] = request[0x18];
	}
	if (output != 0) {
		output[0] = 1;
		output[1] = 8;
		*(int*) (output + 6) = 0;
	}
	return 0;
}
