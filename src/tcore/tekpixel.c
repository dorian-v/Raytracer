/*
** tekpixel.c for raytracer1 in /home/voravo_d/rendu/raytracer1
**
** Made by dorian voravong
** Login   <voravo_d@epitech.net>
**
** Started on  Sun Jul 17 14:40:52 2016 dorian voravong
** Last update Sat Oct  8 18:51:17 2016 Quentin Fournier Montgieux
*/

#include "lapin.h"

void		tekpixel(t_bunny_pixelarray *pix,
			 t_bunny_position *pos,
			 t_color *color)
{
  unsigned int	*pixel;

  pixel = pix->pixels;
  if (pos->x < pix->clipable.clip_width
      && pos->y < pix->clipable.clip_height
      && pos->x >= 0 && pos->y >= 0)
    pixel[pix->clipable.clip_width * pos->y + pos->x] = color->full;
}

void	tekray(const t_bunny_position *screen_info,
	       int *x, int *y, int *z)
{
  *x = screen_info[1].x - screen_info[0].x / 2;
  *y = screen_info[1].y - screen_info[0].y / 2;
  *z = 100;
}

unsigned int	tekgetpixel(t_bunny_pixelarray *pix,
			    t_bunny_position *pos)
{
  unsigned int	*pixel;

  if (pos->x >= pix->clipable.clip_width
      || pos->y >= pix->clipable.clip_height
      || pos->x < 0 || pos->y < 0)
    return (0);
  pixel = pix->pixels;
  return (pixel[pix->clipable.clip_width * pos->y + pos->x]);
}
