/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarek <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 20:36:04 by mmarek            #+#    #+#             */
/*   Updated: 2023/09/23 22:31:45 by mmarek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	**file_read(char *str);

int	ft_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;

	return (i);
}

void	ft_atoi(int b, int a)
{
	int	i;

	i = 0;
	i = ((a - '0') * 10) + b - '0';

	printf("%d\n", i);
}

void	ft_result(char *res, char c)
{
	int	i;

	i = 0;
	while (res[i] != '\0')
		i++;
	res[i] = c;
	res[i + 1] = '\0';
}

int	ft_find_one(char c, char **dict, char *res)
{
	int		i;
	int		j;

	i = 0;
	j = 3;
	while (i < 40)
	{
		if (dict[i][0] == c && c != 48)
		{
			while (dict[i][j] != '\0')
			{
				//write(1, &dict[i][j], 1);
				ft_result(res, dict[i][j]);
				j++;
			}
			ft_result(res, 32);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_find_two(char a, char b, char **dict, char *res)
{
	int	i;
	int	j;

	i = 0;
	j = 4;

	while (i < 40)
	{
		if (dict[i][0] == b && dict[i][1] == a)
		{
			while (dict[i][j] != '\0')
			{
				//write(1, &dict[i][j], 1);
				ft_result(res, dict[i][j]);
				j++;
			}
			ft_result(res, 32);
			return (1);
		}
		i++;
	}

	return (0);
}

int	ft_find_dec(char *c, char **dict, char *res)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 40)
	{
		while (dict[i][j] == c[j])
		{
			j++;
		}
		if (c[j] == '\0' && dict[i][j] == ':')
		{
			j = j + 2;
			while (dict[i][j] != '\0')
			{
				//write(1, &dict[i][j], 1);
				ft_result(res, dict[i][j]);
				j++;
			}
			ft_result(res, 32);
		}
		j = 0;
		i++;
	}
	return (0);
}

char	*ft_add_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	str[i] = '0';
	str[i + 1] = '0';
	str[i + 2] = '0';
	str[i + 3] = '\0';
	return (str);
}

int	is_char(char c)
{
	if(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9')
		return (1);
	return (0);

}

void ft_rev(char *str)
{
	int	len;
	int i;
	int	j;

	len = 0;
	i = 0;
	j = 0;
	len = ft_len(str);

	while(len >= 0)
	{
		while(!is_char(str[len]))
			len--;
		while(is_char(str[len]))
			len--;
		i = len + 1;
		while(is_char(str[i]))
		{
			write(1, &str[i], 1);
			i++;
		}
		write(1, " ", 1);
	}
}


void	ft_write(char *arr)
{
	char *strh = "100";
	char *str = "100";
	char *result;
	int	size;
	int	ret;
	int	j;
	int	i;
	int duo;
	char	**dict;
	char	*path = "";
	int	len;

	len = 0;

	dict = file_read(path);

	str = (char *)malloc(10 * sizeof(char));
	result = (char *)malloc(1024 * sizeof(char));
	str[0] = '1';

	if (!dict)
		printf("%s\n", "Error dict create");

	size = 0;
	j = 0;
	duo = 0;
	size = ft_len(arr);
	i = size - 1;
	while (j < size)
	{
		if (i > 0 && duo != 1)
		{
			ret = ft_find_two(arr[i], arr[i - 1], dict, result);
			if (!ret)
			{
				ft_find_one(arr[i], dict, result);
				arr[i] = '0';
				ft_find_two(arr[i], arr[i - 1], dict, result);
			}
			j = j + 2;
			i = i - 2;
			duo = 1;
		}
		else
		{
			if (arr[i] != 48 && j > 0 && (j + 1) % 3 == 0)
				ft_find_dec(strh, dict, result);
			ft_find_one(arr[i], dict, result);
			duo = 0;
			j++;
			i--;
		}
		if (j != 0 && j % 3 == 0 && j < size)
		{
			str = ft_add_str(str);
			if(arr[i] == 0 || arr[i - 1] == 0 || arr[i - 2] == 0)
			{
				ft_find_dec(str, dict, result);
			}
		}
	}

	//write reverse result;
	len = ft_len(result);
	i = 0;
	//while(i <= len)
	//{
	//	write(1, &result[i], 1);
	//	i++;
	//}
	ft_rev(result);
	free (dict);
	free (str);
	free (result);
}


int	main(int argc, char **argv)
{
	char	*arr;
	int		i;

	i = 0;
	arr = (char *) malloc (1000 * sizeof(char));
	if (argc < 2)
	{
		printf("%s\n", "Arg error");
		return (0);
	}
	while (argv[1][i] != '\0')
	{
		arr[i] = argv[1][i];
		i++;
	}
	arr[i] = '\0';
	ft_write(arr);
	write(1, "\n", 1);
	free (arr);
	return (0);
}
