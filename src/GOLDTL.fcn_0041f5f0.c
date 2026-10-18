char* __cdecl fcn_0041f9b0(int id);
void __cdecl fcn_0041f7f0(char* v);
struct Node;
void __cdecl fcn_0041f940(struct Node* n);

/* ADDRESS: GOLD 0x00423530 */
/* ADDRESS: GOLDTL 0x0041f5f0 */
int __cdecl fcn_0041f5f0(int id)
{
	char* n;

	n = fcn_0041f9b0(id);
	if (n != 0) {
		fcn_0041f7f0(n);
		fcn_0041f940((struct Node*)n);
		return 1;
	}
	return 0;
}
