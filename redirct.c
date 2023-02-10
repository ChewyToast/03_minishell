#include <unistd.h>
int main (void)
{
	write(42, "hola", 4);
	return (0);
}

