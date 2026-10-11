
void __cdecl m_FreeTracked(void*);

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
		m_FreeTracked(n);
		n = next;
	}
	*head = 0;
}
