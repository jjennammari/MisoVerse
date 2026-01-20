#include "parsing.h"

void	update_exit_status(t_fshell *fs, int code, int exit_status)
{
	fs->exit_code = code;
	if (exit_status == 0)
	{
		print_error_message(fs);
		return ;
	}
	if (exit_status == 1)
		exit_program(fs);
}

void	print_error_message(t_fshell *fs)
{
	if (fs->exit_code == 2)
		printf("fastshell: error: memory allocation failed");
}
