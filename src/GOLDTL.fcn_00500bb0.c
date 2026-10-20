#pragma pack(push, 1)
typedef struct {
	int x00;
	unsigned short x04;
	int x06;
	int x0a;
} SIM_CLOCK;
#pragma pack(pop)

#pragma optimize("a", on)
/* ADDRESS: GOLDTL 0x00500bb0 */
void __cdecl fcn_00500bb0(SIM_CLOCK* clock, int arg2, int arg3, int arg4)
{
	unsigned short* p4 = &clock->x04;
	int minutes;
	int days;

	clock->x06 = clock->x06 + (arg4 + clock->x0a) / 60;
	clock->x0a = (arg4 + clock->x0a) % 60;
	clock->x04 = (unsigned short) (clock->x04 + (arg3 + clock->x06) / 60);
	clock->x06 = (arg3 + clock->x06) % 60;
	minutes = *p4;
	minutes += *(volatile int*) &arg2;
	if (minutes >= 24) {
		days = (unsigned int) minutes / 24;
		minutes = minutes - days * 24;
		clock->x00 += days;
	}
	if (minutes < 0) {
		days = (unsigned int) (-1 - minutes) / 24 + 1;
		clock->x00 -= days;
		minutes = minutes + days * 24;
	}
	clock->x04 = (unsigned short) minutes;
}
#pragma optimize("", on)
