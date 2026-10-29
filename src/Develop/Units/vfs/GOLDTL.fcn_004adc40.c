


extern int g_7728c0;
extern int g_7728c4;
extern int g_7728c8;
extern int g_7728cc;
extern int g_7728d0;

unsigned int __cdecl vfs_fwrite(void*, int, int, void*);

int __cdecl fcn_004adc40(void* stream)
{
	if (!(vfs_fwrite(&g_7728c0, 4, 1, stream) > 0))
		return 0;
	if (!(vfs_fwrite(&g_7728c4, 4, 1, stream) > 0))
		return 0;
	if (!(vfs_fwrite(&g_7728c8, 4, 1, stream) > 0))
		return 0;
	if (!(vfs_fwrite(&g_7728cc, 4, 1, stream) > 0))
		return 0;
	return vfs_fwrite(&g_7728d0, 4, 1, stream) > 0;
}
