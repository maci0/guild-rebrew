


char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
void __cdecl d3_ScheduleActionTimer(char*, int, int);

/* ADDRESS: GOLDDE 0x004ba690 */
int __cdecl cm_ExReduceLifespan(char* request, char* output)
{
	char* target;

	target = gm_LookupEntityRecordIn32SlotTable(*(int*) (request + 0x10));
	if (target != 0) {
		d3_ScheduleActionTimer(target, *(int*) (request + 0x14), 0);
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
