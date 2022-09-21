/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ma3ert <yait-iaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:37:23 by Ma3ert            #+#    #+#             */
/*   Updated: 2022/09/21 18:50:04 by Ma3ert           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

void	init_keystate(t_data *data)
{
	data->keystate.w = 0;
	data->keystate.a = 0;
	data->keystate.s = 0;
	data->keystate.d = 0;
	data->keystate.l = 0;
	data->keystate.r = 0;
	data->keystate.tir = 0;
	data->keystate.q = 0;
}

void	get_gun(t_data *data)
{
	data->gun[0] = "./gun/0.xpm";
	data->gun[1] = "./gun/1.xpm";
	data->gun[2] = "./gun/2.xpm";
	data->gun[3] = "./gun/3.xpm";
	data->gun[4] = "./gun/4.xpm";
}
