


/* The T&L build of gm_ff_Objekt (SERVER 0x10016460): the invalid flag
 * combination returns NULL without the LogMessageInternal call. */

extern char* g_99ec10;
extern int g_69938c;
extern unsigned int g_699390;
extern unsigned short g_699394;
extern unsigned char g_699396;
extern unsigned char g_773d9a;
extern unsigned char g_773d98;
extern unsigned char g_773d99;
extern unsigned char g_773d90;
extern int g_773d94;
extern int g_868058;
extern unsigned short* g_868054;
extern unsigned short* g_773da4;

void* __cdecl gm_NextEntityQueryMatch(void);

unsigned short* __cdecl fcn_00502cd0(int container_id, int arg_count, ...)
{
	int* arg_ptr;
	int i;
	unsigned char flag1;
	unsigned char flag2;

	if ((*(int*)&g_99ec10) == 0) {
		return (unsigned short*) 0;
	}

	g_69938c = 0x7fff;
	g_699390 = 0xffffffff;
	g_699394 = 0xffff;
	g_699396 = 0xff;
	g_773d9a = 0;

	flag1 = 0;
	g_773d98 = flag1;
	flag2 = 0;
	g_773d99 = flag2;
	g_773d90 = 1;
	g_773d94 = 0;
	g_868058 = 0;

	if (arg_count > 0) {
		arg_ptr = &arg_count;
		i = arg_count;

		do {
			arg_ptr++;
			switch (*(unsigned char*) arg_ptr) {
			case 0:
				arg_ptr++;
				g_69938c = *(unsigned short*) arg_ptr;
				break;
			case 1:
				g_699390 = *(arg_ptr + 1);
				arg_ptr++;
				break;
			case 2:
				break;
			case 3:
				g_699394 = *(short*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 4:
				g_699396 = *(char*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 5:
				g_773d9a = 1;
				break;
			case 6:
				flag2 = 1;
				break;
			case 7:
				flag1 = 1;
				break;
			}
			i--;
		} while (i != 0);

		g_773d98 = flag1;
		g_773d99 = flag2;

		if (flag1 != 0) {
			if (flag2 != 0) {
				return (unsigned short*) 0;
			}
			container_id = (*(int*)&g_868054);
			goto query_tail;
		}
	}

	if (container_id == 0) {
		return (unsigned short*) container_id;
	}

query_tail:
	g_773da4 = (unsigned short*) container_id;
	return gm_NextEntityQueryMatch();
}
