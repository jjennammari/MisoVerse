# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/28 20:19:38 by lde-san-          #+#    #+#              #
#    Updated: 2026/03/18 22:19:05 by lde-san-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = ./inc/libft/libft.a
MISO_LIB = ./obj/libmisoverse.a
PROMPT ?= misoverse

NEOR	= \001\033[3m\033[38;2;255;153;51m\002
MINT    = \001\033[1;38;2;55;250;133m\002
ORNG    = \001\033[1;38;2;255;153;51m\002
PURP	= \001\033[1;38;2;174;5;252m\002
PINK    = \001\033[1;38;2;255;0;251m\002
BABY    = \001\033[1;38;2;0;255;247m\002
BLOD	= \001\033[1;38;2;255;0;0m\002
LIME    = \001\033[1;38;2;0;255;0m\002
BLAK	= \001\033[1;38;2;0;0;0m\002
B_WI    = \001\033[1;37m\002
RSET	= \001\033[0m\002

SRC_DIR = src/
OBJ_DIR = obj/
BLTIN_DIR = built-ins/
EXPANSION_DIR = expansion/
HEREDOC_DIR = heredoc/
PARSING_DIR = parsing/
TOKENIZE_DIR = tokenize/
INC = -I/inc/libft/includes -I/inc
SUPRS = $(OBJ_DIR).valgrind_suppressions.txt

MAIN_FILE = $(SRC_DIR)miso_main.c

FILE = delete_later.c
FILE += miso_free.c
FILE += miso_prompt.c
FILE += miso_launch.c
FILE += miso_signals.c
FILE += misoverse_loop.c
FILE += miso_pathfinder.c
FILE += miso_redirection.c
FILE += miso_exec_utils_beta.c
FILE += miso_exec_utils_alpha.c
FILE += miso_exec_utils_charlie.c
FILE += miso_export_utils_beta.c
FILE += miso_export_utils_alpha.c
FILE += miso_environment_utils_beta.c
FILE += miso_environment_utils_alpha.c
FILE += miso_environment_utils_charlie.c
FILE += $(BLTIN_DIR)miso_cd.c
FILE += $(BLTIN_DIR)miso_pwd.c
FILE += $(BLTIN_DIR)miso_env.c
FILE += $(BLTIN_DIR)miso_echo.c
FILE += $(BLTIN_DIR)miso_exit.c
FILE += $(BLTIN_DIR)miso_unset.c
FILE += $(BLTIN_DIR)miso_export.c
FILE += $(BLTIN_DIR)miso_context.c
FILE += $(EXPANSION_DIR)miso_expand.c
FILE += $(EXPANSION_DIR)miso_expand_quotes.c
FILE += $(EXPANSION_DIR)miso_expand_quotes_utils.c
FILE += $(EXPANSION_DIR)miso_expand_utils.c
FILE += $(HEREDOC_DIR)miso_heredoc.c
FILE += $(HEREDOC_DIR)miso_heredoc_utils.c
FILE += $(HEREDOC_DIR)miso_heredoc_signals.c
FILE += $(PARSING_DIR)miso_parse.c
FILE += $(PARSING_DIR)miso_parse_quotes.c
FILE += $(PARSING_DIR)miso_parse_utils.c
FILE += $(TOKENIZE_DIR)miso_tokenize.c
FILE += $(TOKENIZE_DIR)miso_tokenize_utils_alpha.c
FILE += $(TOKENIZE_DIR)miso_tokenize_utils_beta.c

SRC = $(addprefix $(SRC_DIR),$(FILE))

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

.PRECIOUS: $(SRC) $(SRC_BONUS)

COMPILE = cc -g -O0 -D PROMPT=\"$(PROMPT)\" -Wall -Werror -Wextra $(INC)
VLGR_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes

all: $(NAME)

$(NAME): $(LIBFT) $(MISO_LIB) ./inc/miso_structs.h ./inc/miso.h
	@printf "$(BABY)"
	$(COMPILE) $(MAIN_FILE) $(MISO_LIB) $(LIBFT) -lreadline -lhistory -o $(NAME)
	@printf "$(MINT)"
	@ls -la
	@printf "$(RSET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c ./inc/miso_structs.h ./inc/miso.h | $(OBJ_DIR)
	@printf "$(PURP)"
	$(COMPILE) -c $< -o $@
	@printf "$(RSET)\n"

$(OBJ_DIR)$(BLTIN_DIR)%.o: $(SRC_DIR)$(BLTIN_DIR)%.c | $(OBJ_DIR)$(BLTIN_DIR)
	@printf "$(PINK)"
	$(COMPILE) -c $< -o $@
	@printf "$(RSET)\n"

$(OBJ_DIR)$(EXPANSION_DIR)%.o: $(SRC_DIR)$(EXPANSION_DIR)%.c | $(OBJ_DIR)$(EXPANSION_DIR)
	@printf "$(PINK)"
	$(COMPILE) -c $< -o $@
	@printf "$(RSET)\n"

$(OBJ_DIR)$(HEREDOC_DIR)%.o: $(SRC_DIR)$(HEREDOC_DIR)%.c | $(OBJ_DIR)$(HEREDOC_DIR)
	@printf "$(PINK)"
	$(COMPILE) -c $< -o $@
	@printf "$(RSET)\n"

$(OBJ_DIR)$(PARSING_DIR)%.o: $(SRC_DIR)$(PARSING_DIR)%.c | $(OBJ_DIR)$(PARSING_DIR)
	@printf "$(PINK)"
	$(COMPILE) -c $< -o $@
	@printf "$(RSET)\n"

$(OBJ_DIR)$(TOKENIZE_DIR)%.o: $(SRC_DIR)$(TOKENIZE_DIR)%.c | $(OBJ_DIR)$(TOKENIZE_DIR)
	@printf "$(PINK)"
	$(COMPILE) -c $< -o $@
	@printf "$(RSET)\n"

$(OBJ_DIR):
	@printf "$(MINT)"
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)$(BLTIN_DIR):
	@printf "$(LIME)"
	mkdir -p $(OBJ_DIR)$(BLTIN_DIR)

$(OBJ_DIR)$(EXPANSION_DIR):
	@printf "$(LIME)"
	mkdir -p $(OBJ_DIR)$(EXPANSION_DIR)

$(OBJ_DIR)$(HEREDOC_DIR):
	@printf "$(LIME)"
	mkdir -p $(OBJ_DIR)$(HEREDOC_DIR)

$(OBJ_DIR)$(PARSING_DIR):
	@printf "$(LIME)"
	mkdir -p $(OBJ_DIR)$(PARSING_DIR)

$(OBJ_DIR)$(TOKENIZE_DIR):
	@printf "$(LIME)"
	mkdir -p $(OBJ_DIR)$(TOKENIZE_DIR)

$(LIBFT):
	@printf "$(NEOR)"
	@make -C ./inc/libft
	@printf "$(RSET)"

$(MISO_LIB): $(OBJ)
	@ar -rcs $@ $^

clean:
	@printf "$(LIME)"
	@make -C ./inc/libft clean
	@sleep 0.3
	@printf "$(BLOD)"
	rm -rf $(OBJ_DIR)
	@sleep 0.3
	@printf "$(RSET)"

fclean: clean
	@printf "$(B_WI)"
	@make -C ./inc/libft fclean
	@sleep 0.3
	@printf "$(PURP)"
	rm -f $(NAME)
	@printf "$(MINT)"
	@sleep 0.3
	@ls -la
	@printf "$(RSET)"

re: fclean all

# /////////////////////// -- * Functionality * -- ////////////////////// #

open:
	@printf "$(MINT)"
	for f in $(SRC); do xdg-open $$f; done
	@sleep 0.3
	@printf "$(ORNG)"
	find . -maxdepth 2 -name "*.h" -exec xdg-open {} \;
	@printf "$(RSET)"

leaks: $(NAME) $(SUPRS)
	@printf "\n$(PINK)valgrind $(ORNG)$(VLGR_FLAGS) $(LIME)--suppressions=$(BABY)$(SUPRS) $(MINT)$(NAME)"
	@printf "$(RSET)\n\n"
	@sleep 0.3
	@valgrind $(VLGR_FLAGS) --suppressions=$(SUPRS) ./$(NAME)

$(SUPRS):
	@printf "$(NEOR) Building obj/.valgrind_suppressions.txt... $(RESET)"
	@sleep 0.5
	@printf "$(MINT)🦝\n\n"
	@> obj/.valgrind_suppressions.txt
	@printf "$(BABY)'# ************************************************************************ #'\n"
	@printf "$(BABY)'#                                                                          #'\n"
	@printf "$(BABY)'#                                                       :::      ::::::::  #'\n"
	@printf "$(BABY)'#  .valgrind_suppressions.txt                         :+:      :+:    :+:  #'\n"
	@printf "$(BABY)'#                                                   +:+ +:+         +:+    #'\n"
	@printf "$(BABY)'#  By: lde-san- <lde-san-@student.42porto.com>    +#+  +:+       +#+       #'\n"
	@printf "$(BABY)'#                                               +#+#+#+#+#+   +#+          #'\n"
	@printf "$(BABY)'#  Created: 2026/03/14 16:33:57 by lde-san-          #+#    #+#            #'\n"
	@printf "$(BABY)'#  Updated: 2026/03/14 16:36:22 by lde-san-         ###   ########.fr      #'\n"
	@printf "$(BABY)'#                                                                          #'\n"
	@printf "$(BABY)'# ************************************************************************ #'\n"
	@printf "%s\n" '# **************************************************************************** #'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" '#                                                                              #'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" '#                                                         :::      ::::::::    #'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" '#    .valgrind_suppressions.txt                         :+:      :+:    :+:    #'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" '#                                                     +:+ +:+         +:+      #'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" '#    By: lde-san- <lde-san-@student.42porto.com>    +#+  +:+       +#+         #'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" '#                                                 +#+#+#+#+#+   +#+            #'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" '#    Created: 2026/03/14 16:33:57 by lde-san-          #+#    #+#              #'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" '#    Updated: 2026/03/14 16:36:22 by lde-san-         ###   ########.fr        #'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" '#                                                                              #'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" '# **************************************************************************** #'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" '{'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" '	leak readline'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" '	Memcheck:Leak'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" '	...'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" '	fun:readline'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" '	}'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" '{'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" '	leak add_history'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" '	Memcheck:Leak'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" '	...'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" '	fun:add_history'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" '}'>> obj/.valgrind_suppressions.txt
	@printf "%s\n" ''>> obj/.valgrind_suppressions.txt
	@printf "$(RESET)🦝"

call_empty_envp_bash:
	@printf "\n$(MINT)env -i $(ORNG)bash $(MINT)--noprofile --norc$(RSET)\n\n"
	@env -i bash --noprofile --norc

call_empty_envp_minishell: $(NAME)
	@printf "\n$(MINT)env -i $(ORNG)$(NAME) $(MINT)--noprofile --norc$(RSET)\n\n"
	@env -i ./$(NAME) --noprofile --norc

env_clear:
	@printf "$(MINT)"
	@printf "\n\t\tPapi... \"unset\" needs to run in the parent process."
	@printf "\n\t\t\tCopy, paste and run this command:\n    \n"
	@printf "$(BABY)"
	@echo "unset XDG_CONFIG_DIRS _ DOCKER_HOST LIBVIRT_DEFAULT_URI XDG_SEAT_PATH GDM_LANG XDG_GREETER_DATA_DIR GPG_AGENT_INFO KRB5CCNAME FT_HOOK_PATHNAME FT_HOOK_NAME LANGUAGE GTK_IM_MODULE XDG_SESSION_PATH SSH_AGENT_LAUNCHER GNOME_SHELL_SESSION_MODE GNOME_TERMINAL_SCREEN GNOME_TERMINAL_SERVICE GSM_SKIP_SSH_AGENT_WORKAROUND GTK_MODULES CLUTTER_DISABLE_MIPMAPPED_TEXT COLORTERM DBUS_SESSION_BUS_ADDRESS DESKTOP_SESSION DISPLAY GDMSESSION GNOME_DESKTOP_SESSION_ID GNOME_SETUP_DISPLAY _ _backup_glob BASH BASH_ALIASES BASH_ARGC BASH_ARGV BASH_ARGV0 BASH_CMDS BASH_COMMAND BASH_COMPLETION_VERSINFO BASH_LINENO BASH_LOADABLES_PATH BASHOPTS BASHPID BASH_SOURCE BASH_SUBSHELL BASH_VERSINFO BASH_VERSION COLUMNS COMP_WORDBREAKS DIRSTACK EPOCHREALTIME EPOCHSECONDS EUID __git_printf_supports_v GNOME_SHELL_SESSION_MODE GNOME_TERMINAL_SCREEN GNOME_TERMINAL_SERVICE GROUPS GSM_SKIP_SSH_AGENT_WORKAROUND GTK_MODULES HISTCMD HISTCONTROL HISTFILE HISTFILESIZE HISTSIZE PIPESTATUS LINES COLUMNS HOME HOSTNAME HOSTTYPE IFS LANG LESS LESSCLOSE LESSOPEN LINENO LINES LOGNAME LS_COLORS LSCOLORS MACHTYPE MAIL MAILCHECK MEMORY_PRESSURE_WATCH MEMORY_PRESSURE_WRITE OLDPWD OPTERR OPTIND OSTYPE PAGER PIPESTATUS PPID PS1 PS2 PS4 PWD QT_ACCESSIBILITY QT_IM_MODULE RANDOM SECONDS SESSION_MANAGER SHELL SHELLOPTS SHLVL SRANDOM SSH_AUTH_SOCK SYSTEMD_EXEC_PID TERM UID USER USERNAME VTE_VERSION WAYLAND_DISPLAY XAUTHORITY XDG_CURRENT_DESKTOP XDG_DATA_DIRS XDG_MENU_PREFIX XDG_RUNTIME_DIR XDG_SESSION_CLASS XDG_SESSION_DESKTOP XDG_SESSION_TYPE XMODIFIERS _xspecs ZSH"
	@printf "$(RSET)"

normloop:
	@printf "$(NEOR) Building normloop.sh... $(RESET)"
	@sleep 0.5
	@printf "$(MINT)🦝\n\n"
	@printf "$(BABY)'# ************************************************************************ #'\n"
	@printf "$(BABY)'#                                                                          #'\n"
	@printf "$(BABY)'#                                                       :::      ::::::::  #'\n"
	@printf "$(BABY)'#  normloop.sh                                        :+:      :+:    :+:  #'\n"
	@printf "$(BABY)'#                                                   +:+ +:+         +:+    #'\n"
	@printf "$(BABY)'#  By: lde-san- <lde-san-@student.42porto.com>    +#+  +:+       +#+       #'\n"
	@printf "$(BABY)'#                                               +#+#+#+#+#+   +#+          #'\n"
	@printf "$(BABY)'#  Created: 2026/03/14 17:57:19 by lde-san-          #+#    #+#            #'\n"
	@printf "$(BABY)'#  Updated: 2026/03/14 17:58:08 by lde-san-         ###   ########.fr      #'\n"
	@printf "$(BABY)'#                                                                          #'\n"
	@printf "$(BABY)'# ************************************************************************ #'\n"
	@> normloop.sh
	@printf "%s\n" '#!/bin/bash'>> normloop.sh
	@printf "%s\n" '# **************************************************************************** #'>> normloop.sh
	@printf "%s\n" '#                                                                              #'>> normloop.sh
	@printf "%s\n" '#                                                         :::      ::::::::    #'>> normloop.sh
	@printf "%s\n" '#    normloop.sh                                        :+:      :+:    :+:    #'>> normloop.sh
	@printf "%s\n" '#                                                     +:+ +:+         +:+      #'>> normloop.sh
	@printf "%s\n" '#    By: lde-san- <lde-san-@student.42porto.com>    +#+  +:+       +#+         #'>> normloop.sh
	@printf "%s\n" '#                                                 +#+#+#+#+#+   +#+            #'>> normloop.sh
	@printf "%s\n" '#    Created: 2026/03/14 17:57:19 by lde-san-          #+#    #+#              #'>> normloop.sh
	@printf "%s\n" '#    Updated: 2026/03/14 17:58:08 by lde-san-         ###   ########.fr        #'>> normloop.sh
	@printf "%s\n" '#                                                                              #'>> normloop.sh
	@printf "%s\n" '# **************************************************************************** #'>> normloop.sh
	@printf "%s\n" ''>> normloop.sh
	@printf "%s\n" 'trap '\''rm -f tody.txt; exit'\'' INT'>> normloop.sh
	@printf "%s\n" ''>> normloop.sh
	@printf "%s\n" 'if [ -n '\"'$$1'\"' ]; then'>> normloop.sh
	@printf "%s\n" '	FILE='\"'$$1'\"''>> normloop.sh
	@printf "%s\n" ''>> normloop.sh
	@printf "%s\n" '	while true'>> normloop.sh
	@printf "%s\n" '	do'>> normloop.sh
	@printf "%s\n" '		norminette -R CheckForbiddenSourceHeader '\"'$$FILE'\"' | grep Error | head -n 40 > tody.txt'>> normloop.sh
	@printf "%s\n" '		clear && cat tody.txt'>> normloop.sh
	@printf "%s\n" '		tput cup 0 0'>> normloop.sh
	@printf "%s\n" '		sleep 1'>> normloop.sh
	@printf "%s\n" '	done'>> normloop.sh
	@printf "%s\n" 'else'>> normloop.sh
	@printf "%s\n" '	while true'>> normloop.sh
	@printf "%s\n" '	do'>> normloop.sh
	@printf "%s\n" '		norminette -R CheckForbiddenSourceHeader *.c | grep Error | head -n 40 > tody.txt'>> normloop.sh
	@printf "%s\n" '        clear && cat tody.txt'>> normloop.sh
	@printf "%s\n" '		tput cup 0 0'>> normloop.sh
	@printf "%s\n" '		sleep 1'>> normloop.sh
	@printf "%s\n" '	done'>> normloop.sh
	@printf "%s\n" 'fi'>> normloop.sh
	@chmod 777 normloop.sh
	@printf "$(RESET)🦝"

.PHONY: all clean fclean re bonus open env_clear
