_This project has been created as part of the 42 curriculum by lde-san- jemustaj_

███╗   ███╗██╗███████╗ ██████╗ ██╗   ██╗███████╗██████╗ ███████╗███████╗
████╗ ████║██║██╔════╝██╔═══██╗██║   ██║██╔════╝██╔══██╗██╔════╝██╔════╝
██╔████╔██║██║███████╗██║   ██║██║   ██║█████╗  ██████╔╝███████╗█████╗  
██║╚██╔╝██║██║╚════██║██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗╚════██║██╔══╝  
██║ ╚═╝ ██║██║███████║╚██████╔╝ ╚████╔╝ ███████╗██║  ██║███████║███████╗
╚═╝     ╚═╝╚═╝╚══════╝ ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝

---

<center>*🍲 A miso-powered minishell 🍲*<br>

---

# 🦝🍲 MisoVerse 🍲🐛️<br>
the tastiest Minishell you'll ever see</center>

---

## Description

**minishell** is a small Unix bash implementation as part of the 42 School curriculum. The objective of this project is to deepen mastery of process management, parsing logic, file descriptors, and terminal interactions by building a shell that can interpret and execute user command lines. The project includes support for built-in commands, I/O redirections, pipelines, environment variables, and basic error handling, all developed from scratch without external parsing libraries.

---

## Instructions

### How to compile<br>

Make sure you have `cc` and GNU Make installed.<br>
<br>
In the project repository:<br>

• first compile the project
```
make
./minishell
```
• after that, if you want, you can compile to use valgrind command with flags:<br>

<br>

```
make leaks
./minishell
```
