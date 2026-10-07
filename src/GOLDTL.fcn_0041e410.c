// FUNCTION: GOLDTL 0x41e410

void __cdecl fcn_0041ddd0(void*);

void __cdecl fcn_0041e410(char** head)
{
	char* n;
	char* next;

	if (head == 0) {
		return;
	}
	n = *head;
	while (n != 0) {
		next = *(char**) (n + 0xc);
		fcn_0041ddd0(n);
		n = next;
	}
	*head = 0;
}
