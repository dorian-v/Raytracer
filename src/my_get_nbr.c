/*
** my_get_nbr.c for raytracer1 in /home/voravo_d/rendu/raytracer1
** 
** Made by dorian voravong
** Login   <voravo_d@epitech.net>
** 
** Started on  Sat Jul 30 15:28:47 2016 dorian voravong
** Last update Fri Aug  5 16:44:04 2016 dorian voravong
*/

#include <stdlib.h>
#include "lapin.h"
#include "my.h"

int	my_get_nbr(const char *str)
{
  int	i;
  int	res;
  int	neg;

  if (str == NULL)
    return (-1);
  neg = 0;
  i = 0;
  if (str[i] == '-')
    {
      neg = 1;
      i = i + 1;
    }
  res = 0;
  while (str[i] != '\0')
    {
      if ('0' > str[i] || str[i] > '9')
        return (-1);
      res = res * 10 + str[i] - 48;
      i = i + 1;
    }
  if (neg == 1)
    return (-res);
  return (res);
}
