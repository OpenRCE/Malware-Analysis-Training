#include <stdio.h>

main()
{
	char	buff[256];
	int	l;
	int	state;
	char	*p;

	while(gets(buff)) {
	    l = strlen(buff);
	    if(l && buff[l - 1] == '\r')
		buff[--l] = 0;
	    if(!strncmp(buff, "WINAPI", 6)) {
		puts(buff);
		state = 1;
		continue;
	    }
	    if(state && (p = strstr(buff, ");"))) {
		for(l = 0; &buff[l] < p; ++l)
		    putchar(buff[l]);
		printf(") { }");
		puts(p + 2);
		state = 0;
	    } else
		puts(buff);
	}
}

