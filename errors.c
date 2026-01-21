#include "parsing.h"

void	update_exit_status(t_miso *mv, int code, int exit_status)
{
	mv->exit_code = code;
	if (exit_status == 0)
	{
		print_error_message(mv);
		return ;
	}
	if (exit_status == 1)
		exit_program(mv);
}

void	print_error_message(t_miso *mv)
{
	if (mv->exit_code == 2)
		printf("fastshell: error: memory allocation failed");
}
