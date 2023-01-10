#include "auxilairy.h"

static size_t	counter(int n)
{
	size_t	len;

	len = 0;
	if (n < 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t	i;
	char	number[3];

	i = counter(n);
	if (n < 0)
	{
		n = n * -1;
		number[0] = '-';
	}
	number[i--] = '\0';
	while (n)
	{
		number[i] = (n % 10) + '0';
		n = n / 10;
		i--;
	}
	return (number);
}
