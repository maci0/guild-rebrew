#pragma optimize("y", off)

extern char* g_6b7d68;

void* __cdecl fopen(char*, char*);
int __cdecl fscanf(void*, char*, ...);
int __cdecl fclose(void*);
char* __cdecl strstr(char*, char*);
char* __cdecl strncpy(char*, char*, unsigned int);
int __cdecl strcmp(char*, char*);
char* __cdecl strcpy(char*, char*);
unsigned int __cdecl strlen(char*);
void* __cdecl memset(void*, int, unsigned int);
void* __cdecl m_alloc(unsigned int, char*);
int __cdecl fcn_00423920(char*);

/* ADDRESS: GOLDTL 0x00424de0 */
int __cdecl fcn_00424de0(char* a0, char* a1)
{
	void* fp;
	char buf[0x100];
	int result;
	void* tail;
	void* prev;
	void* node;
	void* hdr;
	char* p;
	char* s;
	char* d;

	tail = 0;
	result = 0;
	if (g_6b7d68 != 0) {
		goto fail;
	}
	fp = fopen(a0, "rt");
	if (fp == 0) {
		goto fail;
	}
	hdr = m_alloc(0x40, "sbs_Load");
	g_6b7d68 = hdr;
	if (hdr == 0) {
		result = -1;
		goto done;
	}
	memset(hdr, 0, 0x40);
	if (fscanf(fp, "%s", hdr) == -1) {
		result = -1;
		goto after_banks;
	}
	for (p = strstr(hdr, "~"); p != 0; p = strstr(p + 1, "~")) {
		*p = 0x20;
	}
	for (;;) {
		if (fscanf(fp, "%s", buf) == -1) {
			result = -1;
			goto after_banks;
		}
		if (strcmp(buf, "{EndOfSamples}") == 0) {
			break;
		}
		node = m_alloc(0x108, "sbs_Load");
		if (tail != 0) {
			*(void**) ((char*) tail + 0x104) = node;
		} else {
			*(void**) ((char*) hdr + 0x38) = node;
		}
		tail = node;
		if (node == 0) {
			result = -1;
			goto done;
		}
		memset(node, 0, 0x108);
		for (p = strstr(buf, "~"); p != 0; p = strstr(p + 1, "~")) {
			*p = 0x20;
		}
		strncpy(node, buf, 0x100);
		p = strstr(buf, "%lang");
		if (p != 0) {
			*p = 0;
			strcpy(buf + strlen(buf), a1);
			strcpy((char*) node + (p - buf) + 5, buf);
		}
		*(int*) ((char*) node + 0x100) = fcn_00423920(buf);
	}
after_banks:
	if (result != 0) {
		goto done;
	}
	prev = 0;
	for (;;) {
		tail = 0;
		if (fscanf(fp, "%s", buf) == -1) {
			result = -1;
			goto done;
		}
		if (strcmp(buf, "{EndOfSampleBank}") == 0) {
			break;
		}
		node = m_alloc(0x40, "sbs_Load");
		if (prev != 0) {
			*(void**) ((char*) prev + 0x3c) = node;
		} else {
			*(void**) ((char*) g_6b7d68 + 0x3c) = node;
		}
		hdr = node;
		if (hdr == 0) {
			result = -1;
			goto done;
		}
		memset(hdr, 0, 0x40);
		for (p = strstr(buf, "~"); p != 0; p = strstr(p + 1, "~")) {
			*p = 0x20;
		}
		strncpy(hdr, buf, 0x32);
		for (;;) {
			if (fscanf(fp, "%s", buf) == -1) {
				result = -1;
				goto done;
			}
			if (strcmp(buf, "{EndOfVariation}") == 0) {
				break;
			}
			node = m_alloc(0x108, "sbs_Load");
			if (tail != 0) {
				*(void**) ((char*) tail + 0x104) = node;
			} else {
				*(void**) ((char*) hdr + 0x38) = node;
			}
			tail = node;
			if (node == 0) {
				result = -1;
				goto done;
			}
			memset(node, 0, 0x108);
			for (p = strstr(buf, "~"); p != 0; p = strstr(p + 1, "~")) {
				*p = 0x20;
			}
			strncpy(node, buf, 0x100);
			p = strstr(buf, "%lang");
			if (p != 0) {
				*p = 0;
				strcpy(buf + strlen(buf), a1);
				strcpy((char*) node + (p - buf) + 5, buf);
			}
			*(int*) ((char*) node + 0x100) = fcn_00423920(buf);
			if (*(int*) ((char*) node + 0x100) != 0) {
				*(int*) ((char*) g_6b7d68 + 0x34) += *(int*) ((char*) node + 0x100);
				*(int*) ((char*) hdr + 0x34) += *(int*) ((char*) node + 0x100);
			}
		}
		prev = hdr;
	}
done:
	fclose(fp);
	return result;
fail:
	return -1;
}
