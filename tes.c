# include <stdio.h>

int main()
{
	int k, l;
	k = 0;
	l = 0;

    int i[4][3] = {
		{1, 2, 3},
		{4, 5, 6},
		{7,8,9},
		{10,11,12}
	};
    int j[15] = {1,2,3,4,5,6,7,8,9,10,11,12};
	while (k < 4)
	{
		while (l < 3)
		{
			printf("%d %d\n", i[k][l], j[k * 4 + l]);
			l++;
		}
		k++;
		l = 0;
	}

	return (0);
}