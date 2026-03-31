# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/28 20:19:38 by lde-san-          #+#    #+#              #
#    Updated: 2026/03/31 17:05:51 by lde-san-         ###   ########.fr        #
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
FILE += miso_redirection_dad.c
FILE += miso_redirection_kid.c
FILE += miso_redirection_utils.c
FILE += miso_exec_utils_beta.c
FILE += miso_exec_utils_alpha.c
FILE += miso_exec_utils_charlie.c
FILE += miso_export_utils_beta.c
FILE += miso_export_utils_alpha.c
FILE += miso_export_utils_charlie.c
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
FILE += $(EXPANSION_DIR)miso_expand_split.c
FILE += $(HEREDOC_DIR)miso_heredoc.c
FILE += $(HEREDOC_DIR)miso_heredoc_utils_alpha.c
FILE += $(HEREDOC_DIR)miso_heredoc_utils_beta.c
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
	@rm -f miso_tester.sh
	@rm -rf miso_out.txt bash_out.txt
	@rm -rf valgrind_env.sh
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

leaks: $(NAME) $(SUPRS) | valgrind_env 
	@printf "\n$(PINK)valgrind $(ORNG)$(VLGR_FLAGS) $(LIME)--suppressions=$(BABY)$(SUPRS) $(MINT)./$(NAME)"
	@printf "$(RSET)\n\n"
	@sleep 0.3
	@./valgrind_env.sh
	@rm valgrind_env.sh

$(SUPRS): $(OBJ_DIR)
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

valgrind_env: $(NAME) $(SUPRS)
	@> valgrind_env.sh
	@printf "%s\n" '#!/bin/bash'>> valgrind_env.sh
	@printf "%s\n" '# **************************************************************************** #'>> valgrind_env.sh
	@printf "%s\n" '#                                                                              #'>> valgrind_env.sh
	@printf "%s\n" '#                                                         :::      ::::::::    #'>> valgrind_env.sh
	@printf "%s\n" '#    valgrind_env.sh                                    :+:      :+:    :+:    #'>> valgrind_env.sh
	@printf "%s\n" '#                                                     +:+ +:+         +:+      #'>> valgrind_env.sh
	@printf "%s\n" '#    By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+         #'>> valgrind_env.sh
	@printf "%s\n" '#                                                 +#+#+#+#+#+   +#+            #'>> valgrind_env.sh
	@printf "%s\n" '#    Created: 2026/03/23 13:01:53 by lde-san-          #+#    #+#              #'>> valgrind_env.sh
	@printf "%s\n" '#    Updated: 2026/03/23 13:01:53 by lde-san-         ###   ########.fr        #'>> valgrind_env.sh
	@printf "%s\n" '#                                                                              #'>> valgrind_env.sh
	@printf "%s\n" '# **************************************************************************** #'>> valgrind_env.sh
	@printf "%s\n" ''>> valgrind_env.sh
	@printf "%s\n" 'unset MAKEFLAGS MAKELEVEL MAKE_TERMERR MAKE_TERMOUT MFLAGS'>> valgrind_env.sh
	@printf "%s\n" 'export SHLVL=1'>> valgrind_env.sh
	@printf "%s\n" 'valgrind $(VLGR_FLAGS) --suppressions=$(SUPRS) ./$(NAME)'>> valgrind_env.sh
	@chmod 777 valgrind_env.sh

miso_tester: $(NAME) $(SUPRS)
	@printf "$(NEOR) Building miso_tester.sh... $(RESET)"
	@printf "$(MINT)🦝\n\n"
	@printf "$(BABY)'# ************************************************************************ #'\n"
	@printf "$(BABY)'#                                                                          #'\n"
	@printf "$(BABY)'#                                                       :::      ::::::::  #'\n"
	@printf "$(BABY)'#  miso_tester.txt                                    :+:      :+:    :+:  #'\n"
	@printf "$(BABY)'#                                                   +:+ +:+         +:+    #'\n"
	@printf "$(BABY)'#  By: lde-san- <lde-san-@student.42porto.com>    +#+  +:+       +#+       #'\n"
	@printf "$(BABY)'#                                               +#+#+#+#+#+   +#+          #'\n"
	@printf "$(BABY)'#  Created: 2026/03/23 20:04:01 by lde-san-          #+#    #+#            #'\n"
	@printf "$(BABY)'#  Updated: 2026/03/23 20:04:01 by lde-san-         ###   ########.fr      #'\n"
	@printf "$(BABY)'#                                                                          #'\n"
	@printf "$(BABY)'# ************************************************************************ #'\n"
	@> miso_tester.sh
	@printf "%s\n" '#!/bin/bash'>> miso_tester.sh
	@printf "%s\n" '# **************************************************************************** #'>> miso_tester.sh
	@printf "%s\n" '#                                                                              #'>> miso_tester.sh
	@printf "%s\n" '#                                                         :::      ::::::::    #'>> miso_tester.sh
	@printf "%s\n" '#    miso_tester.sh                                     :+:      :+:    :+:    #'>> miso_tester.sh
	@printf "%s\n" '#                                                     +:+ +:+         +:+      #'>> miso_tester.sh
	@printf "%s\n" '#    By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+         #'>> miso_tester.sh
	@printf "%s\n" '#                                                 +#+#+#+#+#+   +#+            #'>> miso_tester.sh
	@printf "%s\n" '#    Created: 2026/03/23 20:04:01 by lde-san-          #+#    #+#              #'>> miso_tester.sh
	@printf "%s\n" '#    Updated: 2026/03/23 20:04:01 by lde-san-         ###   ########.fr        #'>> miso_tester.sh
	@printf "%s\n" '#                                                                              #'>> miso_tester.sh
	@printf "%s\n" '# **************************************************************************** #'>> miso_tester.sh
	@printf "%s\n" ''>> miso_tester.sh
	@printf "%s\n" '#!/bin/bash'>> miso_tester.sh
	@printf "%s\n" ''>> miso_tester.sh
	@printf "%s\n" 'NEOR='\'''\\'001'\\'033[3m'\\'033[38;2;255;153;51m'\\'002'\'''>> miso_tester.sh
	@printf "%s\n" 'MINT='\'''\\'001'\\'033[1;38;2;55;250;133m'\\'002'\'''>> miso_tester.sh
	@printf "%s\n" 'ORNG='\'''\\'001'\\'033[1;38;2;255;153;51m'\\'002'\'''>> miso_tester.sh
	@printf "%s\n" 'PURP='\'''\\'001'\\'033[1;38;2;174;5;252m'\\'002'\'''>> miso_tester.sh
	@printf "%s\n" 'PINK='\'''\\'001'\\'033[1;38;2;255;0;251m'\\'002'\'''>> miso_tester.sh
	@printf "%s\n" 'BABY='\'''\\'001'\\'033[1;38;2;0;255;247m'\\'002'\'''>> miso_tester.sh
	@printf "%s\n" 'BLOD='\'''\\'001'\\'033[1;38;2;255;0;0m'\\'002'\'''>> miso_tester.sh
	@printf "%s\n" 'LIME='\'''\\'001'\\'033[1;38;2;0;255;0m'\\'002'\'''>> miso_tester.sh
	@printf "%s\n" 'RSET='\'''\\'001'\\'033[0m'\\'002'\'''>> miso_tester.sh
	@printf "%s\n" ''>> miso_tester.sh
	@printf "%s\n" ''>> miso_tester.sh
	@printf "%s\n" 'SHELL_TYPE=$$1'>> miso_tester.sh
	@printf "%s\n" 'TEMP_FILE='\"'$${SHELL_TYPE#-}_out.txt'\"''>> miso_tester.sh
	@printf "%s\n" 'START_INDEX=$${2:-0}'>> miso_tester.sh
	@printf "%s\n" ''>> miso_tester.sh
	@printf "%s\n" 'cleanup() {'>> miso_tester.sh
	@printf "%s\n" '    rm -f '\"'$$TEMP_FILE'\"''>> miso_tester.sh
	@printf "%s\n" '    echo -e '\"''\\'n'\\'t$${PINK}>> $${ORNG}Exited $${BABY}Super-Cool-$${MINT}Miso$${BABY}-Powered $${ORNG}Tester$${PINK} <<$${RSET}'\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    exit 0'>> miso_tester.sh
	@printf "%s\n" '}'>> miso_tester.sh
	@printf "%s\n" ''>> miso_tester.sh
	@printf "%s\n" 'trap cleanup SIGINT'>> miso_tester.sh
	@printf "%s\n" ''>> miso_tester.sh
	@printf "%s\n" 'if [[ '\"'$$SHELL_TYPE'\"' != '\"'-miso'\"' && '\"'$$SHELL_TYPE'\"' != '\"'-bash'\"' ]]; then'>> miso_tester.sh
	@printf "%s\n" '    echo -e '\"'$${MINT}Usage: $${BABY}./miso_tester.sh $${ORNG}[$${LIME}-miso $${PURP}| $${LIME}-bash$${ORNG}] [$${LIME}start_index$${ORNG}]$${RSET}'\"''>> miso_tester.sh
	@printf "%s\n" '    exit 1'>> miso_tester.sh
	@printf "%s\n" 'fi'>> miso_tester.sh
	@printf "%s\n" ''>> miso_tester.sh
	@printf "%s\n" '# --- Valgrind Prompt'>> miso_tester.sh
	@printf "%s\n" 'echo -e '\"'$${MINT}Run with Valgrind? $${ORNG}($${LIME}y$${ORNG}/$${BLOD}n$${ORNG})$${RSET}'\"''>> miso_tester.sh
	@printf "%s\n" 'read -p '\"': '\"' val'>> miso_tester.sh
	@printf "%s\n" 'if [[ '\"'$$val'\"' == '\"'y'\"' ]]; then'>> miso_tester.sh
	@printf "%s\n" '    PREFIX='\"'valgrind --leak-check=full --show-leak-kinds=all --suppressions=obj/.valgrind_suppressions.txt'\"''>> miso_tester.sh
	@printf "%s\n" 'else'>> miso_tester.sh
	@printf "%s\n" '    PREFIX='\"''\"''>> miso_tester.sh
	@printf "%s\n" 'fi'>> miso_tester.sh
	@printf "%s\n" ''>> miso_tester.sh
	@printf "%s\n" 'if [[ '\"'$$SHELL_TYPE'\"' == '\"'-miso'\"' ]]; then'>> miso_tester.sh
	@printf "%s\n" '	SHLL='\"'./minishell'\"''>> miso_tester.sh
	@printf "%s\n" 'else'>> miso_tester.sh
	@printf "%s\n" '	SHLL='\"'/usr/bin/bash -i'\"''>> miso_tester.sh
	@printf "%s\n" 'fi'>> miso_tester.sh
	@printf "%s\n" ''>> miso_tester.sh
	@printf "%s\n" '# --->> TESTS HERE! <<---'>> miso_tester.sh
	@printf "%s\n" 'TESTS=('>> miso_tester.sh
	@printf "%s\n" '    '\"'ls -la'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\''\"''\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\\''\\'$$?'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cd ..'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cd'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cd .'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cd.'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cd -'\\''\\'necho '\\'$$OLDPWD'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'unset OLDPWD'\\''\\'ncd -'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cd ~'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'unset HOME'\\''\\'ncd ~'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'unset HOME'\\''\\'ncd'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cd src a'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cd ../../../.. '\\''\\'n pwd'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cd /usr/bin'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cd  ls'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cd nonexistent'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cd '\\''\"''\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ls '\\'$$jhrgsdhgbd'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ls '\\'$$lala/bin | head -n 10'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export a=-l'\\''\\'nls '\\'$$a'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'unset PATH'\\''\\'nls'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'/dev/urandom'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\'$$LACBOLLA'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\''\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'unset PATH'\\''\\'n/usr/bin/whoami'\\''\\'necho '\\'$$PATH'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'/bin/cat'\\''\\'nhehehee'\\''\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'/bin/ls -l'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'/bin/ls lacresta'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\'$$PWD'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cat /bin/ls | head -n 2'\\''\\'n'\\''\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'/bin/ls | wc'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ping -c 2 8.8.8.8'\"''>> miso_tester.sh
	@printf "%s\n" ''\"'    '\"''\"'                           '>> miso_tester.sh
	@printf "%s\n" '      '>> miso_tester.sh
	@printf "%s\n" '      '>> miso_tester.sh
	@printf "%s\n" ''\"''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ls >| out'\\''\\'nrm out'\\''\\'necho '\\''\"'Forced redirection is not a requirement for this subject'\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ls >|'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'./src'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo -n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo -nnnnn'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo -nnnnnnnnnnnnnnnnnnnnn -n -n oi'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo -nnnnnnnnnnnnnnnnnnnnn -nz -n oi'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo -nz oi'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo This is a test'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo -n This is a test'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo -nnnn This is a test'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo This is a test -nnnn'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\'$$?'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\'$$'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo ~'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\'$$USER'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\"''\\'$$'\\''\"'USER'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\'$$/,,'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\"''\'''\\'$$'\'''\'''\\'$$'\'''\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo hi '\\'$$'\'''\'' '\\'$$'\\''\"''\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\'$$USER'\'''\\'$$USER'\'''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\'''\\'$$USER'\'''\\''\"''\\'$$USER'\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\'''\\'$$USER'\'''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\"''\'''\\'$$USER'\'''\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\'''\\''\"''\\'$$USER'\\''\"''\'''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\"''\\'$$U'\\''\"'S'\\''\"'ER'\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\'''\\'$$HOME e '\\'$$CASA e '\\'$$USER'\'''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\'''\'''\\'$$HOME e '\\'$$CASA e '\\'$$USER'\'''\'''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\'''\'''\\'$$HOME e '\'''\\'$$CASA'\'' e '\\'$$USER'\'''\'''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\"''\\'$$HOME | echo '\'''\\'$$USER'\'''\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo hello > '\\''\"'FILENAME WITH SPACE'\\''\"''\\''\\'nls -l | grep '\\''\"'FILENAME WITH SPACE'\\''\"''\\''\\'ncat '\\''\"'FILENAME WITH SPACE'\\''\"''\\''\\'nrm '\\''\"'FILENAME WITH SPACE'\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\"'cat lol.c | cat > lol.c'\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\''\"'ec'\\''\"'h'\\''\"'o'\\''\"'    bla '\\''\"' blaaaaaaaaaaaa'\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ec'\''h'\''o '\''asdas'\'''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\"'Hello World'\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\"''\''Hello World'\'''\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\''\"'echo Hello World'\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo Hello World'\'''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\''\"'e'\\''\"''\''c'\'''\'''\''h'\\''\"'o'\\''\"' Hello'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\"'md'\\''\"' | wc'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\"''\\''\"'carro'\'' | echo '\''cama'\\''\"''\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\"'fred'\'' | echo '\''cama'\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo 42'\'' '\''42'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo a'\''b'\''c'\''d'\''e'\''f'\''g'\''h'\''i'\''j'\''k'\''l'\''m'\''n'\''o'\''p'\''q'\''r'\''s'\''t'\'''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo a'\''b'\''c'\''d'\''e'\''f'\''g'\''h'\''i'\''j'\''k'\''l'\''m'\''n'\''o'\''p'\''q'\''r'\''s'\''t'\'''\\''\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo -n '\\''\"'42'\'' '\''42'\\''\"''\\''\"''\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'env'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'env PATH'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo exit | $${SHLL}'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo exit 300 | $${SHLL}'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo exit -300 | $${SHLL}'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo exit +300 | $${SHLL}'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo exit 2 3 | $${SHLL}'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo exit abc | $${SHLL}'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo exit 99999999999999999999999 | $${SHLL}'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cat nonexistant'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'enter ./minishell'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'>not_executable_file'\\''\\'nls -la|grep not_executable_file'\\''\\'ncat not_executable_file'\\''\\'n./not_executable_file'\\''\\'necho '\\'$$?'\\''\\'nrm not_executable_file'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'| echo 1'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ls not_existing_file'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'/bin/ls'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'/bin/ls teste'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'bla'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'./Makefile'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\''\"' '\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ls > zzz'\\'$$USER.txt'\\''\\'ncat zzz'\\'$$USER.txt'\\''\\'nrm zzz'\\'$$USER.txt'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ls > zzz'\\''\"''\\'$$USER'\\''\"'zzz.txt'\\''\\'ncat zzz'\\''\"''\\'$$USER'\\''\"'zzz.txt'\\''\\'nrm zzz'\\''\"''\\'$$USER'\\''\"'zzz.txt'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ls >> z'\\''\"'zz'\\'$$USER'\\''\"'zzz.txt'\\''\\'ncat z'\\''\"'zz'\\'$$USER'\\''\"'zzz.txt'\\''\\'n rm z'\\''\"'zz'\\'$$USER'\\''\"'zzz.txt'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ls >> z'\''zz'\\'$$USER'\''zzz.txt'\\''\\'ncat z'\''zz'\\'$$USER'\''zzz.txt'\\''\\'nrm z'\''zz'\\'$$USER'\''zzz.txt'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export ='\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export _'\\''\\'nexport'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export _a'\\''\\'nexport |grep _a'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export_'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export n_value'\\''\\'nexport |grep n_value'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export TEST=kaija 12 TEST2=papaija'\\''\\'nexport | grep TEST'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export = a=2 b='\''4'\'' c='\\''\"'10'\\''\"''\\''\\'n echo '\\'$$a '\\'$$b '\\'$$c'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export test='\\''\"'   abc'\\''\"' '\\''\\'nexport | grep test'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export test='\\''\"'ls -l'\\''\"''\\''\\'n'\\'$$test'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export test='\\''\"'o hello'\\''\"''\\''\\'nech'\\'$$test'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export test='\\''\"'| wc '\\''\"''\\''\\'nls '\\'$$test'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export test='\\''\"'a  bc        def'\\''\"''\\''\\'nexport | grep test'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export test'\\''\\'nexport test=hello'\\''\\'nexport | grep test'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export test='\\''\"'a        b         c'\\''\"''\\''\\'n'\\''\\'nexport | grep test'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export ZZ'\\''\"'Y=aaa'\\''\"'bb'\\''\\'nexport | grep ZZY'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export WWW='\\''\"'     -aaa |  '\\''\"''\\''\\'nexport | grep WWW'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export ABC='\\'$$USER'\\''\\'nexport | grep ABC'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export te'\\'$$st=lala'\\''\\'nexport | grep te'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export '\\'$$lalal=hahhaa'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export user=pre'\\'$$'\\''\"'U'\\''\"'S'\\''\"'E'\\''\"'R'\\''\\'necho '\\'$$?'\\''\\'nexport | grep user'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export user=dq'\\''\"''\\'$$USER'\\''\"''\\''\\'necho '\\'$$?'\\''\\'nexport | grep user'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export user=mq'\\'$$'\\''\"'U'\\''\"'S'\\''\"'E'\\''\"'R'\\''\\'necho '\\'$$?'\\''\\'nexport | grep user'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export us'\\'$$er=blabla'\\''\\'necho '\\'$$?'\\''\\'nexport | grep us'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export | grep nonexistentvariable'\\''\\'nunset nonexistentvariable'\\''\\'necho '\\'$$?'\\''\\'nexport | grep nonexistentvariable'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export | grep HOME'\\''\\'nunset HOME'\\''\\'nenv | grep HOME'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'unset'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'unset weird@'\%'chars'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export | grep HOME'\\''\\'nunset -n HOME'\\''\\'necho '\\'$$?'\\''\\'nenv | grep HOME'\\''\\'n'\\''\\'necho '\\''\"'-n flag is not required by the subject'\\''\"''\\''\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export | grep SHLVL'\\''\\'nunset SHL'\\''\"'VL'\\''\"''\\''\\'nexport | grep SHLVL'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'<<'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'>>'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cat << end | wc -l'\\''\\'none'\\''\\'ntwo'\\''\\'nthree'\\''\\'nfour'\\''\\'nend'\\''\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cat << end | grep e'\\''\\'njamon'\\''\\'nempanada'\\''\\'nmalvavisco'\\''\\'nde'\\''\\'npomarosa'\\''\\'narroz'\\''\\'nchocolate'\\''\\'nend'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'<< end '\\''\\'nThis'\\''\\'nis'\\''\\'na'\\''\\'ntest'\\''\\'nend'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'<< end | grep e'\\''\\'nThis'\\''\\'nis'\\''\\'na'\\''\\'ntest'\\''\\'nend'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'<< EOF cat'\\''\\'n'\\'$$USER'\\''\\'n'\\'$$HOME'\\''\\'ncamion'\\''\\'nEOF'\\''\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'<< '\\''\"'EOF'\\''\"' cat'\\''\\'n'\\'$$USER'\\''\\'n'\\'$$HOME'\\''\\'ncamion'\\''\\'nEOF'\\''\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'<< '\''EOF'\'' cat'\\''\\'n'\\'$$USER'\\''\\'n'\\'$$HOME'\\''\\'ncamion'\\''\\'nEOF'\\''\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'<< '\\''\"'eo'\\''\"'f cat'\\''\\'n'\\'$$USER'\\''\\'n'\\'$$HOME'\\''\\'ncamion'\\''\\'neof'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'<< '\\''\"''\\'$$USER'\\''\"' cat'\\''\\'n'\\'$$HOME'\\''\\'ncamion'\\''\\'nEOF'\\''\\'n'\\'$$USER'\\''\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'<< '\'''\\'$$USER'\'' cat'\\''\\'n'\\'$$HOME'\\''\\'ncamion'\\''\\'nEOF'\\''\\'n'\\'$$USER'\\''\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\'$$USER e '\\'$$CASA e '\\''\"''\\'$$ HOME'\\''\"' e '\'''\\'$$ HOME'\'' '\\''\"''\\'$$HOME'\\''\"' '\'''\\'$$HOME'\'' '\\'$$HOME'\\''\\'n'\\''\\'necho '\\'$$USER e '\\'$$CASA e '\\''\"''\\'$$ HOME'\\''\"' e '\'''\\'$$ HOME'\'' '\\''\"''\\'$$HOME'\\''\"' '\'''\\'$$HOME'\'' '\\'$$HOME | wc -m'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\'$$CASA '\\'$$ CAMA'\\''\\'n'\\''\\'necho '\\'$$CASA '\\'$$ CAMA | wc -m'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\''\"'ls'\\''\"' | '\''wc'\'''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'unset USER | env | grep USER'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'unset OLDPWD | ls'\\''\\'n export | grep OLDPWD'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo USER | export USER=bubu'\\''\\'nexport | grep USER'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo Hello World | | grep e'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cat | cat | ls'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cat /dev/urandom | head -c 100'\\''\\'n'\\''\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'| ls'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'|'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ls ||'\\''\\'n'\\''\\'n echo '\\''\"'OR Operand || not required by the subject'\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ls || wc'\\''\\'n'\\''\\'n echo '\\''\"'OR Operand || not required by the subject'\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ls | | wc'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'pwd'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'pwd args'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'PWD args'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\"'<< '\\''\\''\\''\"'EOF'\\''\\''\'' cat'\\''\"' | $${SHLL}'\\''\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\''\"''\\''\"' | ls'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\''\"''\\''\"''\\''\"''\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\''echo '\\''\"' | '\'' | $${SHLL}'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\''\"'/bin/ls'\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export | grep SHLVL'\\''\\'necho '\\''\"'export | grep SHLVL'\\''\"' | $${SHLL}'\\''\\'nexport | grep SHLVL'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\''\"''\\''\"'ls'\\''\"''\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\''\"''\'''\\''\"'ls'\\''\"''\'''\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\''\"''\\''\"'ls -l'\\''\"''\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\''\"'pw'\\''\"''\\''\"''\\''\"'d'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\''\"'ls'\'' | '\''wc'\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\"'ls'\\''\"' '\\''\"'|'\\''\"' '\\''\"''\''wc'\\''\"' | $${SHLL}'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ls | grep '\\''\"''\''md | wc -l'\\''\\'n'\\''\\'n'\\''\"''\\''\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ls | grep '\\''\"''\'''\\''\"'md | wc -l'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ls | grep '\\''\"'md'\\''\"' | wc -l'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\"'cama'\'''\\''\\'n'\\''\\'n'\\''\"''\\''\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\"''\\'$$HOME | echo '\'''\\'$$USER'\'''\\''\\'n'\\''\\'n'\\''\"''\\''\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo hello > outfile'\\''\\'ncat outfile'\\''\\'nls -l | grep outfile'\\''\\'nrm outfile'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ls '\\''\"'>'\\''\"' ola'\\''\\'nls -l | grep ola'\\''\\'nrm ola'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'< inacessible_file | cat -e > output'\\''\\'ncat output'\\''\\'nls -l | grep output'\\''\\'nrm output'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'<'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'>'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'< bla'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'> test'\\''\\'ncat test'\\''\\'nls -l | grep test'\\''\\'nrm test'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo > existingfile'\\''\\'n< existingfile'\\''\\'nls -l | grep existingfile'\\''\\'nrm existingfile'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo hi > testfile'\\''\\'n < testfile > testfile2'\\''\\'ncat testfile2'\\''\\'nls -l | grep testfile '\\''\\'nrm testfile testfile2'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'< nonexisting_file'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ls >out>>out2>out3'\\''\\'ncat out3'\\''\\'nls | grep out'\\''\\'nrm out out2 out3'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ls | grep > out md | wc -l'\\''\\'ncat out'\\''\\'nls -l | grep out'\\''\\'nrm out'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\"''\\''\"'>out'\\''\\'ncat < out >> out'\\''\\'ncat out'\\''\\'nls -l | grep out'\\''\\'nrm out'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo pana mio > in'\\''\\'necho qlq > out'\\''\\'ncat < in >> out'\\''\\'ncat out'\\''\\'nls -l | grep out'\\''\\'nrm in out'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cat < new_file >> new_file'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'<out3 grep i >grep | <grep wc'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\"''\\''\"'>grep'\\''\\'n<out3 grep i >grep | <grep wc'\\''\\'nrm grep'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export fdgsdfhb='\\''\\'nexport | grep fdgsd'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cat<<-eof'\\''\\'nhe'\\''\\'nhe'\\''\\'n-eof'\\''\\'neof'\\''\\'nEOF'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cat <<HERE <<DOC'\\''\\'ntu si'\\''\\'nsabe'\\''\\'nHERE'\\''\\'npapito'\\''\\'nDOC'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'<< echo oi'\\''\\'nhi'\\''\\'namigo'\\''\\'nqueso'\\''\\'necho'\\''\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'<<here oi <<doc'\\''\\'n hehe'\\''\\'nwenas'\\''\\'nhere'\\''\\'nq loco wn'\\''\\'ndoc'\\''\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export GHOST=123 | env | grep GHOST'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cat inc/miso.h | grep '\\''\"');'\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cat <inc/miso.h <<HERE <missing <<DOC | echo oi'\\''\\'nhehe'\\''\\'nlol'\\''\\'nHERE'\\''\\'njsjsjs ok'\\''\\'nbueno'\\''\\'nDOC'\\''\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'pre '\\''\"''\\'$$null'\\''\"'no'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'mkdir test'\\''\\'ncd test'\\''\\'nmkdir test2'\\''\\'ncd test2'\\''\\'nrm -rf ../../test'\\''\\'ncd'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'mkdir test'\\''\\'ncd test'\\''\\'nmkdir test2'\\''\\'ncd test2'\\''\\'nrm -rf ../../test'\\''\\'ncd ..'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'mkdir test'\\''\\'ncd test'\\''\\'nmkdir test2'\\''\\'ncd test2'\\''\\'nrm -rf ../../test'\\''\\'ncd -'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'mkdir test'\\''\\'ncd test'\\''\\'nmkdir test2'\\''\\'ncd test2'\\''\\'nrm -rf ../../test'\\''\\'ncd ../../'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'mkdir test'\\''\\'ncd test'\\''\\'nmkdir test2'\\''\\'ncd test2'\\''\\'nrm -rf ../../test'\\''\\'ncd ../../../..'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'unset PWD'\\''\\'npwd'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'unset PWD'\\''\\'necho '\\'$$PWD'\\''\\'nmkdir test'\\''\\'ncd test'\\''\\'nexport | grep PWD'\\''\\'ncd -'\\''\\'n cd .. '\\''\\'n rm -rf test'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export a=g'\\''\\'necho '\\'$$a'\\''\\'nunset a'\\''\\'necho '\\'$$a'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'>e'\\''\"'of'\\''\"' >ol'\\''\"'a'\\''\"''\\''\\'nls -l | grep -e eof -e ola'\\''\\'nrm eof ola'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'in HD - '\\'$$no ; ola'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'<< '\\'$$USER cat'\\''\\'n'\'''\\'$$USER'\'''\\''\\'nEOF'\\''\\'n'\\'$$USER'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\'$$PATH'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo hi |  '\\''\"'|'\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo hello'\\''\"''\\''\"'world'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo -n '\\''\"'12'\\''\"''\\''\"'34'\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\"''\\'$$PWD'\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo Hello World'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo env | env -i $${SHLL}'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'>'\\'$$USER0'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\'$$EMPTY echo hi'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\'$$EMPTY'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\"'exit_code ->'\\'$$? user ->'\\'$$USER home -> '\\'$$HOME'\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\'$$?HELLO'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo gu>invalid'\\''\\'nchmod 000 invalid'\\''\\'ncat >one <no >invalid'\\''\\'nchmod 777 invalid'\\''\\'nls -l | grep -e invalid -e one'\\''\\'nrm invalid one'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo gu>invalid'\\''\\'nchmod 000 invalid'\\''\\'nls >no >>invalid >>two'\\''\\'nchmod 777 invalid'\\''\\'nls -l | grep -e invalid -e no -e two'\\''\\'n rm invalid no two'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo gu>invalid'\\''\\'nchmod 000 invalid'\\''\\'nls >one >invalid'\\''\\'nchmod 777 invalid'\\''\\'nls -l | grep -e invalid -e one'\\''\\'nrm invalid one'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cat >file <no '\\''\\'nls -l|grep file'\\''\\'nrm file'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export a='\\''\"'ola adeus'\\''\"' '\\''\\'n>'\\'$$a'\\''\\'ncat '\\''\"'ola adeus'\\''\"''\\''\\'nls -l | grep '\\''\"'ola adeus'\\''\"''\\''\\'nrm '\\''\"'ola adeus'\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo gu>invalid'\\''\\'nchmod 000 invalid'\\''\\'ncat <Makefile >invalid'\\''\\'nchmod 777 invalid'\\''\\'nls -la | grep invalid'\\''\\'nrm invalid'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cat '\\''\"''\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'>existing_file'\\''\\'ncat existing_file grep '\\''\"''\\''\"''\\''\\'nrm existing_file'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'>papa echo hello >baby'\\''\\'ncat papa'\\''\\'ncat baby'\\''\\'nls -la | grep -e papa -e baby '\\''\\'nrm papa baby'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'<<'\\''\"''\\''\"''\\''\\'n'\\''\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'<'\\''\"''\\''\"''\\''\\'necho '\\'$$?'\\''\\'n>'\\''\"''\\''\"''\\''\\'necho '\\'$$?'\\''\\'n >>'\\''\"''\\''\"' '\\''\\'n'\\''\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"' cat ./README.md'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'test_files/'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'/test_files'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'unset PATH'\\''\\'necho '\\''\"'ls'\\''\"'| $${SHLL}'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export fdgsdfhb='\\''\\'nexport | grep fdgs'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'<< end'\\''\\'nThis'\\''\\'nis'\\''\\'na heredoc'\\''\\'ncan u believeit?'\\''\\'nstrend'\\''\\'nend'\\''\\'n'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"' | ls'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'>existingfile'\\''\\'n< existingfile'\\''\\'nrm existingfile'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\''\"'ls'\\''\"' | '\\''\"'wc'\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\"'export | grep SHLVL'\\''\"'| $${SHLL}'\\''\\'nexport | grep SHLVL'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export us'\\'$$er=blabla'\\''\\'nexport | grep us'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\"''\'''\\'$$'\\''\"''\\''\"''\\'$$'\'''\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cat < out >> out'\\''\\'nls -l|grep out'\\''\\'n rm out'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'< not_existing_file'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ls'\\''\"''\'''\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'< nonexisting_file | echo hello > nonexisting_file'\\''\\'necho '\\'$$?'\\''\\'ncat nonexisting_file'\\''\\'nrm nonexisting_file'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ls'\'' | '\''wc'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ls'\\''\"''\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo hi>existing_file'\\''\\'necho sth>>existing_file hehe hehe'\\''\\'necho>>existing_file burubururburu'\\''\\'n< existing_file | grep h'\\''\\'n echo '\\'$$?'\\''\\'nrm existing_file  '\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\''\"' '\\''\"'  < '\\''\"' '\\''\"'>'\\''\"''\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\''\"' '\\''\"'  < '\\''\"' '\\''\"'>'\\''\"' '\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cat  < '\\''\"' '\\''\"'>'\\''\"' '\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cat  < README.md>'\\''\"' '\\''\"''\\''\\'n cat '\\''\"' '\\''\"''\\''\\'nrm '\\''\"' '\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo hi > '\\''\"''\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo hi > '\\''\"' '\\''\"''\\''\\'ncat '\\''\"' '\\''\"''\\''\\'nrm '\\''\"' '\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\''\"''\'''\\''\"''\'''\\''\"''\'''\\''\"''\'''\\''\"''\'''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\'''\\''\"''\'''\'''\'''\\''\"''\'''\'''\'''\\''\"''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\'''\'''\'''\'''\'''\'''\'''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\'''\\''\"''\'''\'''\\''\"''\\''\"''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\\'$$USER'\\''\"''\'''\\''\"''\'''\\''\"''\'''\\''\"''\'''\\''\"''\'''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\'''\\''\"''\'''\'''\'''\\''\"''\'''\'''\'''\\''\"''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\'''\'''\'''\'''\'''\'''\'''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\'''\\''\"''\'''\'''\\''\"''\\''\"''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\\''\\'necho '\\''\"''\'''\\''\"''\'''\\''\"''\'''\\''\"''\'''\\''\"''\'''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\'''\\''\"''\'''\'''\'''\\''\"''\'''\'''\'''\\''\"''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\'''\'''\'''\'''\'''\'''\'''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\'''\\''\"''\'''\'''\\''\"''\\''\"''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\\'$$USER'\\''\"''\'''\\''\"''\'''\\''\"''\'''\\''\"''\'''\\''\"''\'''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\'''\\''\"''\'''\'''\'''\\''\"''\'''\'''\'''\\''\"''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\'''\'''\'''\'''\'''\'''\'''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\'''\\''\"''\'''\'''\\''\"''\\''\"''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"'| wc -m'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\'''\\''\"''\'''\\''\"''\'''\\''\"''\'''\\''\"''\'''\\''\"''\'''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\'''\\''\"''\'''\'''\'''\\''\"''\'''\'''\'''\\''\"''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\'''\'''\'''\'''\'''\'''\'''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\'''\\''\"''\'''\'''\\''\"''\\''\"''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\\'$$USER'\'''\'''\\''\"''\'''\\''\"''\'''\\''\"''\'''\\''\"''\'''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\'''\\''\"''\'''\'''\'''\\''\"''\'''\'''\'''\\''\"''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\'''\'''\'''\'''\'''\'''\'''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\'''\\''\"''\'''\'''\\''\"''\\''\"''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\\''\\'necho '\'''\\''\"''\'''\\''\"''\'''\\''\"''\'''\\''\"''\'''\\''\"''\'''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\'''\\''\"''\'''\'''\'''\\''\"''\'''\'''\'''\\''\"''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\'''\'''\'''\'''\'''\'''\'''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\'''\\''\"''\'''\'''\\''\"''\\''\"''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\\'$$USER'\'''\'''\\''\"''\'''\\''\"''\'''\\''\"''\'''\\''\"''\'''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\\''\"''\\''\"''\'''\\''\"''\'''\'''\\''\"''\'''\'''\'''\\''\"''\'''\'''\'''\\''\"''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\'''\'''\'''\'''\'''\'''\'''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'''\'''\\''\"''\'''\'''\\''\"''\\''\"''\'''\'''\'''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\\''\"''\'' | wc -m'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'pw'\\''\"''\\''\"'d'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export user='\\''\"''\\'$$USER'\\''\"'_is_beautiful'\\''\\'necho '\\'$$?'\\''\\'nexport | grep user '\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'ls '\\''\"''\\''\"'-l'\\''\"''\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo >in como estas?'\\''\\'necho >out qlq papito '\\''\"' '\\''\"''\\''\\'ncat < in >> out'\\''\\'necho '\\'$$?'\\''\\'ncat out'\\''\\'nrm in out'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'/bin/ls test'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo hi>existing_file'\\''\\'necho sth>>existing_file hehe hehe'\\''\\'necho>>existing_file burubururburu'\\''\\'n < existing_file grep h'\\''\\'necho '\\'$$?'\\''\\'n cat existing_file'\\''\\'nrm existing_file'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo hi>existing_file'\\''\\'necho sth>>existing_file hehe hehe'\\''\\'necho>>existing_file burubururburu'\\''\\'n >file <existing_file grep sth'\\''\\'necho '\\'$$?'\\''\\'ncat file'\\''\\'nrm file existing_file '\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cd '\\'$$PWD'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo hi amigo> infile'\\''\\'necho >>infile como estas'\\''\\'ngrep hi '\\''\"'<infile'\\''\"''\\''\\'necho '\\'$$?'\\''\\'ncat infile'\\''\\'nrm infile'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo hi amigo> infile'\\''\\'necho >>infile como estas'\\''\\'ngrep hi <infile'\\''\\'necho '\\'$$?'\\''\\'ncat infile'\\''\\'nrm infile'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'doesntexist'\\''\\'n'\\''\\'n'\\''\\'n'\\''\\'n'\\''\\'n'\\''\\'n'\\''\\'n'\\''\\'n'\\''\\'necho '\\'$$?'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export HELLO=123'\\''\\'nexport | grep HELLO'\\''\\'nexport HELLO='\\''\"'beautiful world'\\''\"''\\''\\'nexport | grep HELLO'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cat <./inc/miso.h|ls'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo gu>invalid_permission'\\''\\'nchmod 000 invalid_permission'\\''\\'necho hi | >outfile01 echo bye >invalid_permission'\\''\\'nchmod 777 invalid_permission'\\''\\'nrm invalid_permission outfile01'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo '\\'$$PWD'\\''\\'npwd'\\''\\'nmkdir testesito'\\''\\'ncd testesito'\\''\\'necho '\\'$$PWD'\\''\\'npwd'\\''\\'ncd ..'\\''\\'nrm -rf testesito'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo hi '\\'$$'\\''\"''\'''\'''\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'env | sort | grep -v SHLVL | grep -v ^_'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export VAR='\\''\"'a'\\''\\''\\''\\''\\''\\''\\''\\''\\''\\''\\''\\''\\''\"'b'\\''\\''\\''\\''\\''\\''\\''\\''\\''\\''\\''\\''\\''\\''\\''\\'c'\\''\"''\\''\\'necho '\\'$$VAR'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\''\"''\\'$$null'\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'pre'\\''\"''\\'$$null'\\''\"'no'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\''\"''\\'$$null'\\''\"'no'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'>pre'\\'$$'\\''\"'USER'\\''\"''\\''\\'nls -l | grep USER'\\''\\'nrm preUSER'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export a=echo'\\''\\'n'\\'$$a hello'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'export amiotrofico='\\''\\'n export | grep amiotrofico'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'cmd | echo hi'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo a='\'''\\'$$a'\'''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'commandnotfound1 | echo hello'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"''\\'$$'\\''\"''\\''\"''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'>'\\''\"''\\'$$null'\\''\"''\\''\\'necho '\\'$$?'\\''\\'n>'\\''\"''\\''\"''\\''\\'necho '\\'$$?'\\''\\'n>'\\''\"''\\'$$9'\\''\"''\\''\\'necho '\\'$$?'\\''\\'n>'\\''\"'h h'\\''\"''\\''\\'necho '\\'$$?'\\''\\'nexport a='\\''\"'con espacio'\\''\"''\\''\\'n>'\\'$$a'\\''\\'necho '\\'$$?'\\''\\'n'\\''\\'n>'\\''\"''\\'$$a'\\''\"''\\''\\'necho '\\'$$?'\\''\\'nls -l | grep -e '\''con espacio'\'' -e '\''h h'\'''\\''\\'necho '\\'$$?'\\''\\'nrm '\''con espacio'\'' '\''h h'\'''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'>>'\\''\"''\\'$$null'\\''\"''\\''\\'necho '\\'$$?'\\''\\'n>>'\\''\"''\\''\"''\\''\\'necho '\\'$$?'\\''\\'n>>'\\''\"''\\'$$9'\\''\"''\\''\\'necho '\\'$$?'\\''\\'n>>'\\''\"'h h'\\''\"''\\''\\'necho '\\'$$?'\\''\\'nexport a='\\''\"'con espacio'\\''\"''\\''\\'n>>'\\'$$a'\\''\\'necho '\\'$$?'\\''\\'n'\\''\\'n>>'\\''\"''\\'$$a'\\''\"''\\''\\'necho '\\'$$?'\\''\\'nls -l | grep -e '\''con espacio'\'' -e '\''h h'\'''\\''\\'necho '\\'$$?'\\''\\'nrm '\''con espacio'\'' '\''h h'\'''\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo LLMIN'\\''\\'n echo '\\''\"'exit -9223372036854775808'\\''\"'| $${SHLL}'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo LLMAX'\\''\\'n echo '\\''\"'exit 9223372036854775807'\\''\"'| $${SHLL}'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo LLMIN - 1'\\''\\'n echo '\\''\"'exit -9223372036854775809'\\''\"'| $${SHLL}'\"''>> miso_tester.sh
	@printf "%s\n" '    '\"'echo LLMAX + 1'\\''\\'n echo '\\''\"'exit 9223372036854775808'\\''\"'| $${SHLL}'\"''>> miso_tester.sh
	@printf "%s\n" ')'>> miso_tester.sh
	@printf "%s\n" ''>> miso_tester.sh
	@printf "%s\n" 'if [[ '\"'$$SHLL'\"' == '\"'./minishell'\"' && ! -f '\"'./minishell'\"' ]]; then'>> miso_tester.sh
	@printf "%s\n" '    echo -e '\"'$${BLOD}Error$${PINK}: $${NEOR}./minishell not found. Did you $${ORNG}'\''$${MINT}make$${ORNG}'\''$${NEOR}?$${RSET}'\"''>> miso_tester.sh
	@printf "%s\n" '    exit 1'>> miso_tester.sh
	@printf "%s\n" 'fi'>> miso_tester.sh
	@printf "%s\n" ''>> miso_tester.sh
	@printf "%s\n" 'for (( i=$$START_INDEX; i<$${#TESTS[@]}; i++ )); do'>> miso_tester.sh
	@printf "%s\n" '    clear'>> miso_tester.sh
	@printf "%s\n" '    printf '\"''\\'t'\\'t$${PURP} 🦝 ##>--$${PINK}>$${BABY}> $${MINT}TEST $${LIME}'\%'02d $${BABY}<$${PINK}<$${PURP}--<## 🦝$${RSET}'\\'n'\\'n'\"' '\"'$$i'\"''>> miso_tester.sh
	@printf "%s\n" ''>> miso_tester.sh
	@printf "%s\n" '    if [[ '\"'$$SHELL_TYPE'\"' == '\"'-miso'\"' ]]; then'>> miso_tester.sh
	@printf "%s\n" '        # Running your misoverse'>> miso_tester.sh
	@printf "%s\n" '        echo -e '\"'$${TESTS[$$i]}'\\'necho '\\'$$?'\"' | $$PREFIX $$SHLL > '\"'$$TEMP_FILE'\"' 2>&1'>> miso_tester.sh
	@printf "%s\n" '    else'>> miso_tester.sh
	@printf "%s\n" '        # Running Bash'>> miso_tester.sh
	@printf "%s\n" '        echo -e '\"'$${TESTS[$$i]}'\\'necho '\\'$$?'\"' | $$PREFIX $$SHLL > '\"'$$TEMP_FILE'\"' 2>&1'>> miso_tester.sh
	@printf "%s\n" '    fi'>> miso_tester.sh
	@printf "%s\n" '    cat '\"'$$TEMP_FILE'\"''>> miso_tester.sh
	@printf "%s\n" ''>> miso_tester.sh
	@printf "%s\n" '    echo -e '\"''\\'n'\\'t'\\'t🦝$${MINT}----------------------------$${RSET}🦝'\"''>> miso_tester.sh
	@printf "%s\n" '    echo -e '\"''\\'n'\\'t'\\'t  $${NEOR}Press $${ORNG}[$${BABY}Enter$${ORNG}]$${NEOR} for next test...$${RSET}'\"''>> miso_tester.sh
	@printf "%s\n" '	read -p '\"''\"''>> miso_tester.sh
	@printf "%s\n" '	rm -f '\"'$$TEMP_FILE'\"''>> miso_tester.sh
	@printf "%s\n" 'done'>> miso_tester.sh
	@printf "%s\n" ''>> miso_tester.sh
	@printf "%s\n" 'echo -e '\"''\\'t  $${PINK}>> $${ORNG}Exited $${BABY}Super-Cool-$${MINT}Miso$${BABY}-Powered $${ORNG}Tester$${PINK} <<$${RSET}'\\'n'\"''>> miso_tester.sh
	@printf "%s\n" 'exit 0'>> miso_tester.sh
	@chmod 777 miso_tester.sh
	@printf "$(RESET)🦝"

.PHONY: all clean fclean re bonus open env_clear valgrind_env.sh normloop call_empty_envp_minishell call_empty_envp_bash miso_tester
