# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-san- <lde-san-@student.42porto.co      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/28 20:19:38 by lde-san-          #+#    #+#              #
#    Updated: 2026/03/09 19:07:48 by lde-san-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = ./inc/libft/libft.a
MISO_LIB = ./obj/libmisoverse.a

NEOR	= \033[3m\033[38;2;255;153;51m
MINT    = \033[1;38;2;55;250;133m
ORNG    = \033[1;38;2;255;153;51m
PURP	= \033[1;38;2;174;5;252m
PINK    = \033[1;38;2;255;0;251m
BABY    = \033[1;38;2;0;255;247m
BLOD	= \033[1;38;2;255;0;0m
LIME    = \033[1;38;2;0;255;0m
BLAK	= \033[1;38;2;0;0;0m
B_WI    = \033[1;37m
RSET	= \033[0m

SRC_DIR = src/
OBJ_DIR = obj/
BLTIN_DIR = built-ins/
INC = -I/inc/libft/includes -I/inc

MAIN_FILE = $(SRC_DIR)miso_main.c

FILE = delete_later.c
FILE += miso_free.c
FILE += miso_parse.c
FILE += miso_parse_utils.c
FILE += miso_expand.c
FILE += miso_launch.c
FILE += miso_heredoc.c
FILE += miso_signals.c
FILE += miso_tokenize.c
FILE += misoverse_loop.c
FILE += miso_tokenize_utils.c
FILE += miso_tokenize_quotes.c
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

SRC = $(addprefix $(SRC_DIR),$(FILE))

OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

.PRECIOUS: $(SRC) $(SRC_BONUS)

COMPILE = cc -g -O0 -Wall -Werror -Wextra $(INC)

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

$(OBJ_DIR)$(BLTIN_DIR)%.o: $(SRC_DIR)$(BLTIN_DIR)%.c | $(BLTIN_DIR)
	@printf "$(PINK)"
	$(COMPILE) -c $< -o $@
	@printf "$(RSET)\n"

$(OBJ_DIR):
	@printf "$(MINT)"
	mkdir -p $(OBJ_DIR)

$(BLTIN_DIR):
	@printf "$(LIME)"
	mkdir -p $(OBJ_DIR)$(BLTIN_DIR)

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

call_empty_envp_bash:
	@printf "\n$(MINT)env -i $(ORNG)bash $(MINT)--noprofile --norc$(RSET)\n\n"
	@env -i bash --noprofile --norc

call_empty_envp_minishell: $(NAME)
	@printf "\n$(MINT)env -i $(ORNG)$(NAME) $(MINT)--noprofile --norc$(RSET)\n\n"
	@env -i $(NAME) --noprofile --norc

env_clear:
	@printf "$(MINT)"
	@printf "\n\t\tPapi... \"unset\" needs to run in the parent process."
	@printf "\n\t\t\tCopy, paste and run this command:\n    \n"
	@printf "$(BABY)"
	@echo "unset XDG_CONFIG_DIRS _ DOCKER_HOST LIBVIRT_DEFAULT_URI XDG_SEAT_PATH GDM_LANG XDG_GREETER_DATA_DIR GPG_AGENT_INFO KRB5CCNAME FT_HOOK_PATHNAME FT_HOOK_NAME LANGUAGE GTK_IM_MODULE XDG_SESSION_PATH SSH_AGENT_LAUNCHER GNOME_SHELL_SESSION_MODE GNOME_TERMINAL_SCREEN GNOME_TERMINAL_SERVICE GSM_SKIP_SSH_AGENT_WORKAROUND GTK_MODULES CLUTTER_DISABLE_MIPMAPPED_TEXT COLORTERM DBUS_SESSION_BUS_ADDRESS DESKTOP_SESSION DISPLAY GDMSESSION GNOME_DESKTOP_SESSION_ID GNOME_SETUP_DISPLAY _ _backup_glob BASH BASH_ALIASES BASH_ARGC BASH_ARGV BASH_ARGV0 BASH_CMDS BASH_COMMAND BASH_COMPLETION_VERSINFO BASH_LINENO BASH_LOADABLES_PATH BASHOPTS BASHPID BASH_SOURCE BASH_SUBSHELL BASH_VERSINFO BASH_VERSION COLUMNS COMP_WORDBREAKS DIRSTACK EPOCHREALTIME EPOCHSECONDS EUID __git_printf_supports_v GNOME_SHELL_SESSION_MODE GNOME_TERMINAL_SCREEN GNOME_TERMINAL_SERVICE GROUPS GSM_SKIP_SSH_AGENT_WORKAROUND GTK_MODULES HISTCMD HISTCONTROL HISTFILE HISTFILESIZE HISTSIZE PIPESTATUS LINES COLUMNS HOME HOSTNAME HOSTTYPE IFS LANG LESS LESSCLOSE LESSOPEN LINENO LINES LOGNAME LS_COLORS LSCOLORS MACHTYPE MAIL MAILCHECK MEMORY_PRESSURE_WATCH MEMORY_PRESSURE_WRITE OLDPWD OPTERR OPTIND OSTYPE PAGER PIPESTATUS PPID PS1 PS2 PS4 PWD QT_ACCESSIBILITY QT_IM_MODULE RANDOM SECONDS SESSION_MANAGER SHELL SHELLOPTS SHLVL SRANDOM SSH_AUTH_SOCK SYSTEMD_EXEC_PID TERM UID USER USERNAME VTE_VERSION WAYLAND_DISPLAY XAUTHORITY XDG_CURRENT_DESKTOP XDG_DATA_DIRS XDG_MENU_PREFIX XDG_RUNTIME_DIR XDG_SESSION_CLASS XDG_SESSION_DESKTOP XDG_SESSION_TYPE XMODIFIERS _xspecs ZSH"
	@printf "$(RSET)"

.PHONY: all clean fclean re bonus open env_clear
