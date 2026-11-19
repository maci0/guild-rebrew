


#pragma pack(push, 1)
typedef struct {
	int f0;
	unsigned short f4;
	int f6;
} fcn_00500d20_rec;
#pragma pack(pop)
// SIZE 0xa

int __cdecl gm_GetElapsedMinutes(fcn_00500d20_rec* start, fcn_00500d20_rec* end)
{
	return ((end->f0 - start->f0) * 24 - start->f4 + end->f4) * 60 - start->f6 + end->f6;
}
