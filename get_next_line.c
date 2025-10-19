#include "get_next_line.h"

/*
	NAME
		get_next_line
	SYNOPSIS
		#include "get_next_line.h"
	PROTOTYPE
		char *get_next_line(int fd);
	DESCRIPTION:
		Reads a line from file descriptor fd using a static buffer to maintain state between calls.
		The buffer size is defined by the BUFFER_SIZE macro during compilation.
	RETURN VALUE
		Returns the next line (including \n) or NULL on EOF/error.
	EXTERNAL FUNC(S)
		read, malloc, free
*/

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE];
	char		*line;
	size_t		line_len;
	size_t		capacity;
	size_t		append_len;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	line = NULL;
	line_len = 0;
	capacity = 0;
	while (1)
	{
		append_len = read_buffer(fd, buf);
		if (append_len < 1)
			return (line);
		line = grow_line(line, line_len, append_len, &capacity);
		if (!line)
			return (NULL);
		line = append_line(line, &line_len, buf, append_len);
		if (line[line_len - 1] == '\n')
			return (line);
	}
}

/*
DESCRIPTION
		Reads from fd if buffer empty and returns bytes to append up to newline
		or upto end of buffer or EOF. Returns -1 on error or 0 on EOF.
*/

ssize_t	read_buffer(int fd, char *buf)
{
	ssize_t	bytes_read;
	char	*nl_pos;

	bytes_read = ft_strlen(buf);
	if (bytes_read == 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read < 1)
			return (bytes_read);
		else if (bytes_read < BUFFER_SIZE)
			buf[bytes_read] = 0;
	}
	nl_pos = ft_mstrchr(buf, '\n', bytes_read);
	if (!nl_pos)
		return (bytes_read);
	return (nl_pos - buf + 1);
	
}

/*
DESCRIPTION
	Reallocates the line to the new capacity and returns a pointer to the new line,
	or NULL if the allocation fails or if src is NULL.
*/

char	*grow_line(char *src, size_t src_len, size_t append_len, size_t *capacity)
{
	char	*dst;
	size_t	needed_capacity;

	if (*capacity >= src_len + append_len + 1)
		return (src);
	needed_capacity = src_len + append_len + 1;
	if ((*capacity < SIZE_MAX / 2) && (*capacity * 2 >= needed_capacity))
		*capacity *= 2;
	else
		*capacity = needed_capacity;
	dst = malloc(*capacity);
	if (!dst)
		return (NULL);
	if (src)
		ft_memcpy(dst, src, src_len);
	free(src);
	return (dst);
}

/*
DESCRIPTION
	Appends the bytes from the buffer to the line and returns a pointer to the new line,
	or NULL if the allocation fails or if line is NULL.
*/

char *append_line(char *line, size_t *line_len, char *buf, size_t append_len)
{
	ft_memcpy(line + *line_len, buf, append_len);
	*line_len += append_len;
	line[*line_len] = '\0';
	if (BUFFER_SIZE > append_len)
		ft_memcpy(buf, buf + append_len, BUFFER_SIZE - append_len);
	buf[BUFFER_SIZE - append_len] = 0;
	return (line);
}

/*
DESCRIPTION
	Locates the first occurrence of the character c in the string s, stops after n bytes or at
	the first null terminator. Returns a pointer to the byte located, or NULL if
	no such character exists within n bytes or if s is NULL.
*/

char    *ft_mstrchr(const char *s, int c, size_t n)
{
	if (!s)
		return (NULL);
    while(n-- > 0 && (unsigned char)*s && ((unsigned char)*s != (unsigned char)c))
        s++;
    if ((unsigned char)*s == (unsigned char)c)
        return ((char *)s);
    return (NULL);
}