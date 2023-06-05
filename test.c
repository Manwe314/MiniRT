#include <stdio.h>
#include <math.h>
#include <unistd.h>
# include <stdlib.h>

typedef struct s_child
{
	int a, b;
}	child;


typedef struct s_parent
{
	struct s_child a, b;
}	parent;

child get_child(void)
{
	child ch;
	ch.a = 42;
	ch.b = 69;
	return (ch);
}
child get_child2(void)
{
	child ch;
	ch.a = 70;
	ch.b = 80;
	return (ch);
}

int main()
{
	parent *par;

	par = (parent *)malloc(sizeof(parent));
	par->a = get_child();
	par->b = get_child2();
	printf("ch1: %d && %d\nch2: %d && %d\n",  par->a.a, par->a.b,par->b.a,par->b.b);
    return 0;
}