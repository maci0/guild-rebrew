

void __cdecl vfs_WriteInt32(int, int);

/* ADDRESS: GOLD 0x4012b0 */
void __cdecl vfs_WriteVec3(int a1, int* values)
{
	vfs_WriteInt32(a1, values[0]);
	vfs_WriteInt32(a1, values[1]);
	vfs_WriteInt32(a1, values[2]);
}
