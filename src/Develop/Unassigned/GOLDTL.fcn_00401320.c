

// Client twin of GOLD's fcn_00401320 (0x401320, 23 B): the client calls
// fcn_00401260 on four consecutive ints; GOLD calls fcn_00430e30 once.

#ifdef REBREW_GOLD
void __cdecl fcn_00401320(int, int);
#define stream_write fcn_00401320
#else
void __cdecl fcn_00401260(int, int);
#define stream_write fcn_00401260
#endif

void __cdecl fcn_004012e0(int a1, int* a2)
{
	stream_write(a1, a2[0]);
	stream_write(a1, a2[1]);
	stream_write(a1, a2[2]);
	stream_write(a1, a2[3]);
}
