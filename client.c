/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovotny <rnovotny@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 17:45:42 by rnovotny          #+#    #+#             */
/*   Updated: 2023/08/08 18:19:34 by rnovotny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int main(int argc, char **argv)
{
    if (argc != 3 || argv[1])
    {
        ft_printf("Incorrect arguments.\n");
        ft_printf("Should be: ./client <PID> <message>\n");
    }
}