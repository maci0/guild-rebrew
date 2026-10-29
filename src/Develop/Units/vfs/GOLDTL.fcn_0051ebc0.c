


extern unsigned short* lpObjekteINST;

unsigned int __cdecl vfs_fwrite(void* p, int size, int n, void* file);

int __cdecl fcn_0051ebc0(void* file)
{
	int count;
	int i;
	unsigned char* rec;

	count = 0;
	for (i = 0; i < 0x5008; i++) {
		if (*(short*) (((unsigned char*)lpObjekteINST) + i * 0x43) != 0) {
			count++;
		}
	}
	if (vfs_fwrite(&count, 4, 1, file) <= 0)
		return 0;
	for (i = 0; i < 0x5008; i++) {
		rec = ((unsigned char*)lpObjekteINST) + i * 0x43;
		if (*(short*) rec != 0) {
			if (vfs_fwrite(rec, 2, 1, file) <= 0)
				return 0;
			if (vfs_fwrite(rec + 2, 4, 1, file) <= 0)
				return 0;
			if (vfs_fwrite(rec + 6, 4, 1, file) <= 0)
				return 0;
			if (vfs_fwrite(rec + 0xa, 4, 1, file) <= 0)
				return 0;
			if (vfs_fwrite(rec + 0xe, 4, 1, file) <= 0)
				return 0;
			if (vfs_fwrite(rec + 0x12, 1, 1, file) <= 0)
				return 0;
			if (vfs_fwrite(rec + 0x13, 1, 1, file) <= 0)
				return 0;
			rec += 0x1c;
			if (vfs_fwrite(rec, 0x1f, 1, file) <= 0)
				return 0;
		}
	}
	return 1;
}
