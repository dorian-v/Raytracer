/*
** my_putstr_err.c for raytracer1 in /home/voravo_d/rendu/raytracer1
** 
** Made by dorian voravong
** Login   <voravo_d@epitech.net>
** 
** Started on  Sun Jul 17 15:37:49 2016 dorian voravong
** Last update Sun Oct 23 15:19:01 2016 dorian voravong
*/

#include <unistd.h>

void	my_putstr_err(char *str)
{
  int	i;

  i = 0;
  while (str[i] != '\0')
    {
      write(2, &str[i], 1);
      i = i + 1;
    }
}
