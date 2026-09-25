// FUNCTION: GOLD 0x4fe210
// SIZE: 112
// FUNCTION: GOLDTL 0x00500cb0
// SIZE: 111

#pragma pack(push, 2)
typedef struct
{
	int day;
	unsigned short hour;
	int min;
	int sec;
} Time;
// SIZE 0xe
#pragma pack(pop)

int __cdecl fcn_00500cb0(Time* a, Time* b)
{
	int ta;
	int tb;

	if (a->day < b->day) {
		return -1;
	}
	if (a->day > b->day) {
		return 1;
	}
	ta = (a->hour * 60 + a->min) * 60 + a->sec;
	tb = (b->hour * 60 + b->min) * 60 + b->sec;
	if (ta < tb) {
		return -1;
	}
	return ta > tb;
}
