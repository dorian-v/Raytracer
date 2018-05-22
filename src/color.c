/*
** color.c for raytracer1 in /home/voravo_d/rendu/raytracer1
** 
** Made by dorian voravong
** Login   <voravo_d@epitech.net>
** 
** Started on  Fri Aug  5 12:41:08 2016 dorian voravong
** Last update Thu Oct 13 18:25:27 2016 dorian voravong
*/

#include "lapin.h"
#include "my.h"

void	set_color(t_intersection *inter, int *i, double *k)
{
  inter->col.r = 0;
  inter->col.b = 0;
  inter->col.g = 0;
  *k = 2;
  *i = 0;
}

void	color_average(t_intersection *inter, int nb_lights)
{
  if (inter->col.r / nb_lights > 255)
    inter->base_col.argb[0] = 255;
  else
    inter->base_col.argb[0] = inter->col.r / nb_lights;
  if (inter->col.g / nb_lights > 255)
    inter->base_col.argb[1] = 255;
  else
    inter->base_col.argb[1] = inter->col.g / nb_lights;
  if (inter->col.b / nb_lights > 255)
    inter->base_col.argb[2] = 255;
  else
    inter->base_col.argb[2] = inter->col.b / nb_lights;

}

unsigned int	reflexion_average(unsigned int col1, unsigned int col2)
{
  t_color	color1;
  t_color	color2;
  t_color	result;

  color1.full = col1;
  color2.full = col2;
  result.argb[0] = (1 - REFLEXION) * color1.argb[0]
    + REFLEXION * color2.argb[0];
  result.argb[1] = (1 - REFLEXION) * color1.argb[1]
    + REFLEXION * color2.argb[1];
  result.argb[2] = (1 - REFLEXION) * color1.argb[2]
    + REFLEXION * color2.argb[2];
  return (result.full);
}

void	color_tab(unsigned int tab[8])
{
  tab[0] = RED;
  tab[1] = 0x008000;
  tab[2] = BLUE;
  tab[3] = YELLOW;
  tab[4] = PURPLE;
  tab[5] = WHITE;
  tab[6] = TEAL;
  tab[7] = BLACK;
}
