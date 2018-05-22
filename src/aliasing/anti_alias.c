/*
** anti_alias.c for  in /home/fourni_2/rendu/raytracer1
**
** Made by fourni_2
** Login   <fourni_2@epitech.net>
**
** Started on  Sun Aug  7 16:57:42 2016 fourni_2
** Last update Sun Oct 23 14:54:59 2016 dorian voravong
*/

#include "my.h"

void	free_sample(t_bunny_pixelarray **pix_tab)
{
  int	i;

  i = 0;
  while (i < 4)
    {
      bunny_delete_clipable(&pix_tab[i]->clipable);
      i += 1;
    }
}

int			anti_alias(t_bunny_pixelarray *pix)
{
  t_alias		alias;
  t_bunny_pixelarray	*pix_tab[4];
  t_bunny_position	dir[4];

  if (init_pix(pix_tab, pix) == 1)
    return (1);
  init_arr(&alias);
  init_dir(dir);
  fill_sample(&alias, pix_tab, dir);
  fill_pix_with_tab(pix_tab, pix, &alias);
  free_sample(pix_tab);
  return (0);
}
