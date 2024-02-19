#include <ft_irc.hpp>

#define BUFFER_SIZE 42

void	over_read(char *string, char *save)
{
	int	i;
	int	j;

	i = 0;
	while (string && string[i] && string[i] != '\n')
		i++;
	if (string)
		i += string[i] == '\n';
	j = 0;
	while (string && string[i])
		save[j++] = string[i++];
	while (save && save[j])
		save[j++] = 0;
}

char	*seek_line(int fd, int pos, char *piece, char *save)
{
	int		i;
	char	buffer[BUFFER_SIZE + 1];
	char	*line;

	i = 0;
	while (i <= BUFFER_SIZE)
		buffer[i++] = 0;
	i = 0;
	while (piece && piece[i] && piece[i] != '\n')
		i++;
	if (piece && piece[i] != '\n' && read(fd, buffer, BUFFER_SIZE) > 0)
		line = seek_line(fd, (pos + i), buffer, save);
	else
	{
		line = malloc(sizeof(char) * (pos + i + (piece[i] == '\n') + 1));
		if (!line)
			return (NULL);
		line[pos + i + (piece[i] == '\n')] = '\0';
		over_read(piece, save);
	}
	i = 0;
	while (line && piece && piece[i] && (i == 0 || piece[i - 1] != '\n'))
		line[pos++] = piece[i++];
	return (line);
}

char	*get_next_line(int fd)
{
	static char		saved[BUFFER_SIZE + 1];
	char			buffer[BUFFER_SIZE + 1];
	char			*line;
	int				i;

	if (read(fd, 0, 0) < 0)
	{
		over_read(NULL, saved);
		return (NULL);
	}
	i = -1;
	line = NULL;
	if (!saved[0])
		i = read(fd, buffer, BUFFER_SIZE);
	else
		while (saved[++i])
			buffer[i] = saved[i];
	buffer[i] = 0;
	if (i)
		line = seek_line(fd, 0, buffer, saved);
	return (line);
}