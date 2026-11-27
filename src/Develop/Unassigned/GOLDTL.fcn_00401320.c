

// Client twin of GOLD's fcn_00401320 (0x401320, 23 B): the client calls
// fcn_00401260 on four consecutive ints; GOLD calls fcn_00430e30 once.

#ifdef REBREW_GOLD
void __cdecl vfs_WriteDword(int, int);
#define stream_write vfs_WriteDword
#else
void __cdecl vfs_WriteInt32(int, int);
#define stream_write vfs_WriteInt32
#endif

void __cdecl vfs_WriteVec4(int stream, int* values)
{
	stream_write(stream, values[0]);
	stream_write(stream, values[1]);
	stream_write(stream, values[2]);
	stream_write(stream, values[3]);
}
