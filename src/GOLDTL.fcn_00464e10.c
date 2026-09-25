typedef struct TmUnz {
	unsigned int tm_sec;
	unsigned int tm_min;
	unsigned int tm_hour;
	unsigned int tm_mday;
	unsigned int tm_mon;
	unsigned int tm_year;
} TmUnz;
// SIZE 0x18

// FUNCTION: GOLD 0x467fd0
// SIZE: 79
// FUNCTION: GOLDTL 0x464e10
// SIZE: 79
void __cdecl fcn_00464e10(unsigned long ulDosDate, TmUnz* ptm)
{
	unsigned long uDate;

	uDate = (unsigned long) (ulDosDate >> 16);
	ptm->tm_mday = (unsigned int) (uDate & 0x1f);
	ptm->tm_mon = (unsigned int) ((((uDate) & 0x1E0) / 0x20) - 1);
	ptm->tm_year = (unsigned int) (((uDate & 0x0FE00) / 0x0200) + 1980);
	ptm->tm_hour = (unsigned int) ((ulDosDate & 0xF800) / 0x800);
	ptm->tm_min = (unsigned int) ((ulDosDate & 0x7E0) / 0x20);
	ptm->tm_sec = (unsigned int) (2 * (ulDosDate & 0x1f));
}
