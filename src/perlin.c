/*
** perlin.c for raytracer in /home/voravo_d/rendu/raytracer2
** 
** Made by dorian voravong
** Login   <voravo_d@epitech.net>
** 
** Started on  Sat Oct  8 22:19:05 2016 dorian voravong
** Last update Sun Oct 23 15:26:10 2016 dorian voravong
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lapin.h"

void		set_gradient(double gradient[8][2])
{
  double	u;

  u = 1.0 / sqrtf(2.0);
  gradient[0][0] = u;
  gradient[0][1] = u;
  gradient[1][0] = -u;
  gradient[1][1] = u;
  gradient[2][0] = u;
  gradient[2][1] = -u;
  gradient[3][0] = -u;
  gradient[3][1] = -u;
  gradient[4][0] = 1;
  gradient[4][1] = 0;
  gradient[5][0] = 0;
  gradient[5][1] = 1;
  gradient[6][0] = -1;
  gradient[6][1] = 0;
  gradient[7][0] = 0;
  gradient[7][1] = -1;
}

int	set_values(int **perm, double gradient[8][2], int opt)
{
  int	i;

  if (opt == 1)
    {
      if (*perm != NULL)
	bunny_free(*perm);
      return (1);
    }
  if ((*perm = bunny_malloc(sizeof(int) * 512)) == NULL)
    return (1);
  i = 0;
  while (i < 512)
    {
      (*perm)[i] = rand() % 255;
      i = i + 1;
    }
  set_gradient(gradient);
  return (0);
}

double		weighted_average(double values[4], double x, double y)
{
  double	smooth1;
  double	smooth2;
  double	ratio;

  ratio = 3 * powf((x - (int)(x)), 2) - 2 * powf((x - (int)(x)), 3);
  smooth1 = values[0] * (1.0 - ratio) + ratio * values[1];
  smooth2 = values[2] * (1.0 - ratio) + ratio * values[3];
  ratio = 3 * powf((y - (int)(y)), 2) - 2 * powf((y - (int)(y)), 3);
  return (smooth1 * (1.0 - ratio) + ratio * smooth2);
}

int	pseudo_rand(int i, int j, int c,
		    int *perm)
{
  if (j < 0)
    j = 0;
  return (perm[i + (c == 1 || c == 3)
	       + perm[j + (c == 2 || c == 3)]] % 8);
}

int		perlin(double x, double y, double resolution, int opt)
{
  static int	*rand_tab = NULL;
  static double	gradient[8][2];
  double	values[4];
  double	vector[4][2];
  int		i;
  int		j;
  int		n;

  if (rand_tab == NULL || opt == 1)
    if (set_values(&rand_tab, gradient, opt) == 1)
      return (0);
  x = fabs(x / resolution);
  y = fabs(y / resolution);
  i = (int)x % 255;
  j = (int)y % 255;
  n = 0;
  while (n < 4)
    {
      vector[n][0] = gradient[pseudo_rand(i, j, n, rand_tab)][0];
      vector[n][1] = gradient[pseudo_rand(i, j, n, rand_tab)][1];
      values[n] = vector[n][0] * (x - ((int)(x) + (n == 1 || n == 3)))
        + vector[n][1] * (y - ((int)(y) + (n == 2 || n == 3)));
      n = n + 1;
    }
  return ((weighted_average(values, x, y) + 1) * 0.5 * 255);
}
