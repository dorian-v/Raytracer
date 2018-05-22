/*
** camera.c for raytracer1 in /home/voravo_d/rendu/raytracer1
**
** Made by dorian voravong
** Login   <voravo_d@epitech.net>
**
** Started on  Wed Aug  3 11:49:49 2016 dorian voravong
** Last update Fri Oct 14 17:48:13 2016 Quentin Fournier Montgieux
*/

#include <math.h>
#include "lapin.h"
#include "my.h"

void	camera_rotation(t_prog *prog)
{
  if (prog->k[BKS_LEFT])
    prog->y_angle -= M_PI / 100;
  else if (prog->k[BKS_RIGHT])
    prog->y_angle += M_PI / 100;
  if (prog->k[BKS_UP])
    prog->x_angle -= M_PI / 100;
  else if (prog->k[BKS_DOWN])
    prog->x_angle += M_PI / 100;
  if (prog->k[BKS_A])
    prog->z_angle += M_PI / 100;
  else if (prog->k[BKS_E])
    prog->z_angle -= M_PI / 100;
}

void	camera_move(t_prog *prog)
{
  if (prog->k[BKS_Z])
    {
      prog->eye_pos.x += sin(prog->y_angle) * 50;
      prog->eye_pos.y += -sin(prog->z_angle) * 50;
      prog->eye_pos.z += cos(prog->x_angle) * 50;
    }
  else if (prog->k[BKS_S])
    prog->eye_pos.z -= 50;
  if (prog->k[BKS_D])
    prog->eye_pos.x += 50;
  else if (prog->k[BKS_Q])
    prog->eye_pos.x -= 50;
  if (prog->k[BKS_SPACE])
    prog->eye_pos.y += 50;
  else if (prog->k[BKS_B])
    prog->eye_pos.y -= 50;
}
