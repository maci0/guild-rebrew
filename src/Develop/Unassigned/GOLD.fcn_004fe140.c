#pragma pack(push, 2)
typedef struct TIME_4FE140 {
	int day;
	unsigned short hour;
	int minute;
	int second;
} TIME_4FE140;
#pragma pack(pop)

/* ADDRESS: GOLD 0x004fe140 */
void __cdecl fcn_004fe140(TIME_4FE140* clock, int hours, int minutes, int seconds)
{
	unsigned short* hour = &clock->hour;
	int value;
	int days;

	clock->minute += (seconds + clock->second) / 60;
	clock->second = (seconds + clock->second) % 60;
	clock->hour += (unsigned short) ((minutes + clock->minute) / 60);
	clock->minute = (minutes + clock->minute) % 60;
	value = *hour;
	value += hours;
	if (value >= 24) {
		days = clock->day; days += (unsigned int) value / 24;
		value -= (unsigned int) value / 24 * 24;
		clock->day = days;
	}
	if (value < 0) {
		days = clock->day; days -= (unsigned int) (-1 - value) / 24 + 1;
		clock->day = days;
		value += ((unsigned int) (-1 - value) / 24 + 1) * 24;
	}
	clock->hour = (unsigned short) value;
}
