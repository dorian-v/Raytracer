/*
** bmp_load.c for  in /home/fourni_2/wolf3d
**
** Made by Quentin Fournier Montgieux
** Login   <fourni_2@epitech.net>
**
** Started on  Wed Jun 29 16:43:37 2016 Quentin Fournier Montgieux
** Last update Sun Oct 23 14:59:04 2016 dorian voravong
*/

#include <fcntl.h>
#include <unistd.h>
#include "my.h"

int	get_tex(t_shape *shape, int water)
{
  if (shape->type == 4)
    {
      if ((shape->tex = load_bmp("ressources/wall.bmp")) == NULL)
        return (1);
    }
  else if (shape->type == 1)
    {
      if ((shape->tex = load_bmp("ressources/water.bmp")) == NULL)
        return (1);
    }
  else
    shape->tex = NULL;
  shape->water = water;
  return (0);
}

void			modif_color(t_color *color)
{
  unsigned char		stc;

  stc = color->argb[1];
  color->argb[1] = color->argb[2];
  color->argb[2] = stc;
  stc = color->argb[0];
  color->argb[0] = color->argb[3];
  color->argb[3] = stc;
}

t_bunny_pixelarray	*rempl_pixe(int width, int height, int file_d)
{
  t_bunny_position	pos;
  unsigned int		buf1;
  t_bunny_pixelarray	*pix;
  t_color		color;

  if ((pix = bunny_new_pixelarray(width, height)) == NULL)
    return (NULL);
  pos.x = 0;
  pos.y = height - 1;
  while (pos.y >= 0)
    {
      if (read(file_d, &buf1, 4) == -1)
	return (NULL);
      color.full = buf1;
      modif_color(&color);
      tekpixel(pix, &pos, &color);
      pos.x += 1;
      if (pos.x > width - 1)
	{
	  pos.x = 0;
	  pos.y -= 1;
	}
    }
  close(file_d);
  return (pix);
}

t_bunny_pixelarray	*load_bmp(const char *file)
{
  unsigned int		buf[100];
  unsigned int		buf1;
  int			pos_pix;
  int			width;
  int			height;
  int			file_d;

  if ((file_d = open(file, O_RDONLY)) == -1
      || read(file_d, buf, 10) == -1
      || read(file_d, &buf1, 4) == -1)
    return (NULL);
  pos_pix = buf1;
  if (read(file_d, buf, 4) == -1
      || read(file_d, &buf1, 4) == -1)
    return (NULL);
  width = buf1;
  if (read(file_d, &buf1, 4) == -1)
    return (NULL);
  height = buf1;
  if (read(file_d, buf, pos_pix - 26) == -1)
    return (NULL);
  return (rempl_pixe(width, height, file_d));
}
