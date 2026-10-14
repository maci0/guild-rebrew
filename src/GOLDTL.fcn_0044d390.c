/* ADDRESS: GOLDTL 0x00662d18 */
extern char g_662d18[];
/* ADDRESS: GOLD 0x005ebb58 */
extern char g_662d18[];
/* ADDRESS: GOLDTL 0x0067b608 */
extern char g_67b608[];
/* ADDRESS: GOLD 0x005fc698 */
extern char g_67b608[];

char* __cdecl fcn_0064f026(char* s, const char* delim);
int __cdecl fcn_0064eeec(const char* s);
void* __cdecl m_alloc(int size, char* tag);

/* ADDRESS: GOLD 0x0044eb20 */
/* ADDRESS: GOLDTL 0x0044d390 */
void __cdecl fcn_0044d390(int unused, char* s)
{
	int n;

	n = fcn_0064eeec(fcn_0064f026(0, g_662d18));
	*(int*) (s + 0xc) = n;
	*(int*) (s + 8) = 0;
	if (n > 0) {
		*(void**) (s + 0x10) = m_alloc(n * 0xe0, g_67b608);
	}
}
