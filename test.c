/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 09:24:50 by lde-san-          #+#    #+#             */
/*   Updated: 2026/03/18 09:35:59 by lde-san-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
# define MINT "\001\033[1;38;2;55;250;133m\002"
# define RSET "\001\033[0m\002"
# define B_WI "\001\033[1;37m\002"

int main (int a, char **v)
{
	int	i;

	printf(B_WI"Argument Count: "MINT"]"RSET"%d"MINT"["RSET"\n", a);
	printf(B_WI"First Argument: "MINT"]"RSET"%s"MINT"["RSET"\n\n", v[1]);

	i = 0;

	printf(B_WI"All arguments: "RSET);
	while (v[i])
	{
		if (!v[i+1])
			printf("%s"MINT"."RSET"\n", v[i]);
		else
			printf("%s"MINT","RSET" ", v[i]);
		i++;
	}
	return (0);
}
