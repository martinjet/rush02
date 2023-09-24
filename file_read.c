






#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


char	**file_read(char *str)
{
	char	**arr;
	int		num;
	char	buff[1024];
	int		fp;
	int		i;
	int		j;
	int		k;

	arr = (char **) malloc (5000 * sizeof(char));
	i = 0;
	while (i < 41)
	{
		arr[i] = (char *) malloc (200 * sizeof(char));
		i++;
	}
	fp = open("./numbers.dict", O_RDONLY);
	if (fp < 0)
	{
		printf("Error!");
		return (arr);
	}
	read(fp, buff, 1024);
	close(fp);
	k = 0;
	i = 0;
	j = 0;
	while (buff[i] != '\0')
	{
		while (buff[i] != '\n')
		{
			arr[j][k] = buff[i];
			i++;
			k++;
		}
		arr[j][k] = '\0';
		i++;
		j++;
		k = 0;
	}
	return (arr);
}


/*
int	main(void)
{

	char	*str;
	char	**arr;

	arr = file_read(str);
	printf("%s\n", arr[15]);

	free (arr);

}
*/
