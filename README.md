# Minishell


## Introduction

As beautiful as a shell! This [@42SP](https://github.com/42sp) project is a simple implementation of a Unix shell, created for educational purposes, using all the knowledge adquired in 42 so far. It allows users to execute basic commands, just like in a real terminal. In this project we learn about system calls, communicating multiples processes, input and output redirections, use of git to control and develop new features, etc. Furthermore, teamwork, division of tasks using flowcharts, good communication, code versioning, exchange with the community and peer programming were essential for us to complete this project.

## Features

- Prompt waiting user's commands
- Expansions of environ, single and double quotes
- Execution of simple commands (e.g., `ls`, `echo`)
- Input and output redirection (`>`, `<`)
- Support for pipes (`|`) and multiple commands
- Environment variable manipulation
- Execution of built-in commands like `cd`, `exit`, and `env`
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- Handle $? (brings the last status executed);

## Prerequisites

To compile and run Minishell, you will need the Readline library. Follow the steps below to install it on your system:

### Ubuntu/Debian

```bash
sudo apt-get update
sudo apt-get install libreadline-dev
```

### Fedora
```bash
sudo dnf install readline-devel
```

### macOS (using Homebrew)
```bash
brew install readline
```

## Installation 

To install Minishell, you need to have GCC (or another compatible compiler) and Make installed on your system. Follow the steps below:

1. Clone the repository:

    ```bash
    git clone https://github.com/LuisTakeo/42-Minishell.git
    cd 42-Minishell
    ```

2. Compile the project using Make:

    ```bash
    make
    ```

## Usage

After installation, you can run Minishell with the command:

```bash
./minishell
```

## Supported Commands

Minishell supports various basic commands, including:

- env: Lists all environment variables.
- External commands like ls, grep, cat, etc., as long as they are available on the system.
- Additionally, it supports redirections (input, output, append and heredoc) and pipes.

## Builtins

Minishell implements the following built-in commands:

- echo [-n] [message]: Prints a message to the screen. The -n option suppresses the newline at the end.
- export [NAME=VALUE]: Sets or updates environment variables.
- cd [path]: Changes the current directory to the specified path. Supports absolute and relative paths.
- pwd: Prints the full path of the current working directory.
- unset [NAME]: Removes environment variables.
- exit [value]: Exits Minishell. If an exit value is provided, it will be used as the exit code.

---
Minishell was developed by [@LuisTakeo](https://github.com/LuisTakeo) and [@drisanches](https://github.com/drisanches).

We hope you enjoy using Minishell! For any questions or issues, feel free to open an issue in the repository.

Happy coding and happy learning!
