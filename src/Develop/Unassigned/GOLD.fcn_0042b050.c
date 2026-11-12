#include <string.h>

void* __cdecl m_alloc(int size, const char* tag);

/* ADDRESS: GOLD 0x0042b050 */
int __cdecl fcn_0042b050(void)
{
	int offset;
	*(void**) 0x6332bc = m_alloc(0x4c00, "evt:command_entry");
	*(void**) 0x6332c0 = m_alloc(0x20, "evt:commandLine");
	*(void**) 0x6332c4 = m_alloc(0x400, "evt:console");
	*(void**) 0x14607b0 = m_alloc(0x1080, "evt:errorline");
	*(void**) 0x6332b4 = m_alloc(0x64c00, "evt:script");
	memset(*(void**) 0x6332b4, 0, 0x64c00);
	for (offset = 0; offset < 0x64c00; offset += 0xc98) {
		*(unsigned int*) ((char*) *(void**) 0x6332b4 + offset + 0x100) = 0xffffffff;
	}
	**(unsigned int**) 0x6332bc = 0;
	strcpy((char*) 0x1460705, "==");
	strcpy((char*) 0x146070a, "=");
	strcpy((char*) 0x146070f, "++");
	strcpy((char*) 0x1460714, "+");
	strcpy((char*) 0x1460719, "--");
	strcpy((char*) 0x146071e, "-");
	strcpy((char*) 0x1460723, "!=");
	strcpy((char*) 0x1460728, "{");
	strcpy((char*) 0x146072d, "}");
	strcpy((char*) 0x1460732, ";");
	strcpy((char*) 0x1460737, ",");
	strcpy((char*) 0x146073c, "(");
	strcpy((char*) 0x1460741, ")");
	strcpy((char*) 0x1460746, "\"");
	strcpy((char*) 0x146074b, "//");
	strcpy((char*) 0x1460750, "<=");
	strcpy((char*) 0x1460755, "<");
	strcpy((char*) 0x146075a, ">=");
	strcpy((char*) 0x146075f, ">");
	strcpy((char*) 0x1460764, "/");
	strcpy((char*) 0x1460769, "*");
	strcpy((char*) 0x146076e, "||");
	strcpy((char*) 0x1460773, "&&");
	strcpy((char*) 0x1460778, "|");
	strcpy((char*) 0x146077d, "&");
	strcpy((char*) 0x1460782, " ");
	strcpy((char*) 0x1460787, "[");
	strcpy((char*) 0x146078c, "]");
	strcpy((char*) 0x1460791, ".");
	strcpy((char*) 0x1460260, "do");
	strcpy((char*) 0x1460270, "while");
	strcpy((char*) 0x1460280, "if");
	strcpy((char*) 0x1460290, "return");
	strcpy((char*) 0x14602a0, "else");
	strcpy((char*) 0x14602b0, "#include");
	strcpy((char*) 0x14602c0, "#singlestep");
	strcpy((char*) 0x14602d0, "#normalstep");
	strcpy((char*) 0x14602e0, "#multistep");
	*(int*) 0x14607a0 = 0;
	*(int*) 0x14607a4 = 0;
	*(int*) 0x14607a8 = 0;
	return 1;
}
