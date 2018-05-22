/*
** translation.c for raytracer1 in /home/voravo_d/rendu/raytracer1
** 
** Made by dorian voravong
** Login   <voravo_d@epitech.net>
** 
** Started on  Fri Aug  5 17:43:22 2016 dorian voravong
** Last update Mon Aug  8 19:59:20 2016 dorian voravong
*/

#include "lapin.h"
#include "my.h"

void	object_translation(t_prog *prog)
{
  if (prog->k[BKS_O])
    prog->select = (prog->select + 1) % prog->map->nb_shapes;
  if (prog->k[BKS_H])
    prog->map->shape[prog->select].pos.x -= 50;
  if (prog->k[BKS_K])
    prog->map->shape[prog->select].pos.x += 50;
  if (prog->k[BKS_U])
    prog->map->shape[prog->select].pos.z += 50;
  if (prog->k[BKS_J])
    prog->map->shape[prog->select].pos.z -= 50;
  if (prog->k[BKS_M])
    prog->map->shape[prog->select].pos.y -= 50;
  if (prog->k[BKS_P])
    prog->map->shape[prog->select].pos.y += 50;
}
