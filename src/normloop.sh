#!/bin/bash
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    normloop.sh                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-san- <lde-san-@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/03/14 17:57:19 by lde-san-          #+#    #+#              #
#    Updated: 2026/03/14 17:58:08 by lde-san-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

trap 'rm -f tody.txt; exit' INT

if [ -n "$1" ]; then
	FILE="$1"

	while true
	do
		norminette -R CheckForbiddenSourceHeader "$FILE" | grep Error | head -n 40 > tody.txt
		clear && cat tody.txt
		tput cup 0 0
		sleep 1
	done
else
	while true
	do
		norminette -R CheckForbiddenSourceHeader *.c | grep Error | head -n 40 > tody.txt
        clear && cat tody.txt
		tput cup 0 0
		sleep 1
	done
fi
