#pragma pack(push, 2)
typedef struct {
	int day;
	unsigned short hour;
	int min;
	int sec;
} Time;
// SIZE 0xe
#pragma pack(pop)

#pragma optimize("a", on)
/* ADDRESS: GOLDTL 0x00500bb0 */
void __cdecl fcn_00500bb0(Time* clock, int arg2, int arg3, int arg4)
{
	unsigned short* p4 = &clock->hour;
	int minutes;
	int days;

	clock->min += (arg4 + clock->sec) / 60;
	clock->sec = (arg4 + clock->sec) % 60;
	clock->hour += (unsigned short) ((arg3 + clock->min) / 60);
	clock->min = (arg3 + clock->min) % 60;
	minutes = *p4;
	minutes += arg2;
	days = clock->day;
	if (minutes >= 24) {
		days += (unsigned int) minutes / 24;
		minutes -= (unsigned int) minutes / 24 * 24;
	}
	if (minutes < 0) {
		days -= (unsigned int) (-1 - minutes) / 24 + 1;
		minutes += ((unsigned int) (-1 - minutes) / 24 + 1) * 24;
	}
	clock->day = days;
	clock->hour = (unsigned short) minutes;
}
#pragma optimize("", on)
