#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdint.h> // SIZE_MAX
# include <stdlib.h> // malloc, free
# include <unistd.h> // read, ssize_t

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 256
#endif

// get_next_line
char	*get_next_line(int fd);
ssize_t	read_buffer(int fd, char *buf);
char	*grow_line(char *line, size_t line_len, size_t append_len, size_t *capacity);
char	*append_line(char *line, size_t *line_len, char *buf, size_t append_len);

// get_next_line_utils
size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char    *ft_mstrchr(const char *s, int c, size_t n);

#endif