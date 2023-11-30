#include "get_next_line.h"


int ft_strlen(char *s)
{
  int i = 0;

  if (!s)
    return (0);
  while (s[i] != '\0' && s[i] != '\n')
    i++;
  if (s[i] == '\n')
    i++;
  return (i);
}

char  *ft_strjoin(char *s1, char *s2)
{
  int   len = ft_strlen(s1) + ft_strlen(s2);
  int   i = 0;
  int   j = 0;
  char  *new_str;

  new_str = (char *)malloc(sizeof(char) * len + 1);
  if (!new_str)
    return (free(s1), NULL);
  while (s1 && s1[i])
  {
    new_str[i] = s1[i];
    i++;
  }
  while (s2 && s2[j])
  {
    new_str[i] = s2[j];
    if (new_str[i] == '\n')
      break ;
    i++;
    j++;
  }
  new_str[len] = '\0';
  free(s1);
  return (new_str);
}

int update_buffer(char *buf)
{
  int flag = 0;
  int i = 0;
  int j = 0;

  while (buf[i])
  {
    if (flag)
      buf[j++] = buf[i];
    if (buf[i] == '\n')
      flag = 1;
    buf[i++] = '\0';
  }
  return (flag);
}

char  *get_next_line(int fd)
{
  static char buffer[MAX_FD][BUFFER_SIZE + 1];
  int         bytes;
  char        *line;

  if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
    return (NULL);
  line = NULL;
  bytes = 0;
  while (buffer[fd][0] || (bytes = read(fd, buffer[fd], BUFFER_SIZE)) > 0)
  {
    line = ft_strjoin(line, buffer[fd]);
    if (update_buffer(buffer[fd]))
      break ;
  }
  if (line && bytes < 0)
  {
    free(line);
    line = NULL;
  }
  return (line);
}
