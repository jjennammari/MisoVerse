#include "parsing.h"

void	exit_program(t_fshell *fs)
{
	//update signal number if reason is signal usage
	print_error_message(fs);
	free_fastshell(fs);
}
