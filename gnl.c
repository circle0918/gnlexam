/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_Next_Line_yy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 17:17:15 by yyuan             #+#    #+#             */
/*   Updated: 2021/11/02 23:53:55 by yyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

char		*ft_strncpy(char *dest, char *src, int n)
{
	char	*s;
	char	*d;
	int		i;

	s = src;
	d = dest;
	i = 0;
	while (s[i] != '\0' && i < n)
	{
		d[i] = s[i];
		i++;
	}
	while (i < n)
	{
		d[i] = '\0';
		i++;
	}
	return (d);
}

char		*ft_strjoin(char *s1, char *s2)
{
	char *new;

	if (!s1 || !s2
	|| !(new = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char))))
		return (NULL);
	ft_strncpy(new, (char *)s1, ft_strlen(s1));
	ft_strcpy(new + ft_strlen(s1), (char *)s2);
	return (new);
}

char		*ft_substr(char *s, size_t start, size_t len)
{
	size_t	l;
	char	*new;

	if (!s || start > ft_strlen(s))
		return (NULL);
	if (start + len <= ft_strlen(s))
		l = start + len + 1;
	else
		l = ft_strlen(s) - start + 1;
	if (start == len)
	{
		new = ft_strdup("");
		return (new);
	}
	if (!(new = malloc(l * sizeof(char))))
		return (NULL);
	new = ft_strncpy(new, &s[start], l - 1);
	new[l - 1] = '\0';
	return (new);
}

char* ft_output(char **str, int lenght_to_cut)
{
	char	*tmp;
	char *ret;

	if (lenght_to_cut != 0)
	{
		ret = ft_substr(*str, 0, lenght_to_cut);
		tmp = ft_strdup(*str + lenght_to_cut); //
		free(*str);
		*str = tmp;
	}
	else // last line
	{
		ret = ft_strdup(*str); // if last only has '\0', to EXCEPTION
		free(*str);
		*str = NULL;
	}
	return ret;
}

char*	get_next_line(int fd)
{
	int			ret;
	static char	*str;
	char		*buf;
	if (str)
	{
		int find_pos = ft_strchr(str, '\n');
		if ( find_pos != -1) // no need to add new buf
			return (ft_output(&str, find_pos+1)); //find_pos+1 is used for substr(, , length)
	}
	if (!(buf = ft_strnew(BUFFER_SIZE)))
		return (NULL);

	int find_pos_n = -1;
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';// but.length = BUFFER_SIZE + 1
		if (!str)
			str = ft_strdup(buf);
		else
		{
			char *tmp = ft_strjoin(str, buf);
			free(str);
			str = tmp;
		}
		find_pos_n = ft_strchr(str, '\n'); 
		if (find_pos_n != -1)
			break ;
	}
	free(buf);
	if (fd < 0 || ret < 0 || BUFFER_SIZE <= 0) //rare
		return (NULL);
	if (ret == 0 && !str) //rare
		return NULL;	

	//EXCEPTION
	if (ret == 0 && str && *str == '\0') //no adding buf, then if str begin with '\0': last line but with only '\0' 
		return NULL;	
	
	if (find_pos_n != -1)
		return (ft_output(&str, find_pos_n+1)); //pos+1 is used for substr(, , length)
	else
		return (ft_output(&str, 0));
}

