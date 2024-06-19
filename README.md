# Minishell

As beautiful as a shell! This [@42SP](https://github.com/42sp) project is a simple implementation of a Unix shell, created for educational purposes, using all the knowledge adquired in 42 so far. It allows users to execute basic commands, just like in a real terminal.

## Introduction

The existence of shells is linked to the very existence of IT.
At the time, all developers agreed that communicating with a computer using aligned
1/0 switches was seriously irritating.
It was only logical that they came up with the idea of creating a software to communicate with a computer using interactive lines of commands in a language somewhat
close to the human language.

## Features

- Execution of simple commands (e.g., `ls`, `echo`)
- Input and output redirection (`>`, `<`)
- Support for pipes (`|`) and multiple commands
- Environment variable manipulation
- Execution of built-in commands like `cd`, `exit`, and `env`
- Basic signal handling (e.g., `Ctrl+C`, `Ctrl+D`)

## Prerequisites

To compile and run Minishell, you will need the Readline library. Follow the steps below to install it on your system:

### Ubuntu/Debian

```bash
sudo apt-get update
sudo apt-get install libreadline-dev
```

### Fedora
```bash
Copiar código
sudo dnf install readline-devel
```

### macOS (using Homebrew)
```bash
Copiar código
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
