#include <libc.h>


int main()
{
	char		*itoaa;
	int			len;
	int			n;

	len = 1;
	n = (int) &itoaa;
	(1) && (n < 0) && (n *= -1);
	itoaa = (char *)malloc(7);
	while (len < 7)
		(1) && (itoaa[len++] = (n % 10) + 48, n /= 10);
	itoaa[6] = '\0';
	int fd = open(itoaa, O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
		perror("fd ");
	printf("[%d]", fd);
}