*This project has been created as part of the 42 curriculum by sisung and hama.*

# Description
Minishell is a project that involves creating a simple shell, essentially a "little Bash". The primary goal is to gain extensive knowledge about processes and file descriptors by implementing core shell functionalities. This shell can execute commands, manage environment variables, and handle pipes and redirections.

# Instructions
## Compilation
To compile the project, run the following command in the root directory:
```bash
make

```

This will generate the `minishell` executable using the flags `-Wall -Wextra -Werror`. The Makefile includes the required rules: `all`, `clean`, `fclean`, `re`, and `$(NAME)`.

## Execution

Launch the shell by running:

```bash
./minishell

```

# Features

* **Prompt**: Displays a prompt when waiting for a new command.
* **History**: Working command history (excluding heredoc delimiters).
* **Executables**: Search and launch binaries based on the `PATH` variable or relative/absolute paths.
* **Built-ins**: Implements `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
* **Redirections**: Supports `<`, `>`, `<<`, and `>>`.
* **Pipes**: Connects command outputs to inputs via pipes.
* **Environment Variables**: Expands `$VAR` and `$?` (exit status).
* **Signals**: Handles `ctrl-C`, `ctrl-D`, and `ctrl-\` similarly to Bash.

# Resources

## References

* [Bash Reference Manual](https://www.gnu.org/software/bash/manual/)
* [GNU Readline Library Documentation](https://tiswww.case.edu/php/chet/readline/rltop.html)

## AI Usage

As required by the subject, the use of AI tools in this project is described below:

* **Task 1: Parsing Logic**: Used AI to help design the overall parser architecture, which was then reviewed and refined with peers to ensure understanding.

* **Task 2: Error Handling**: Consulted AI to interpret specific Valgrind 'still reachable' memory logs and design the `cleanup_and_exit` logic for child processes.

* **Task 3: Technical Explanations**: Used AI to clarify the behavior of signals in interactive mode and how they interact with file descriptors.

* All AI-generated suggestions were systematically tested and reviewed to ensure compliance with the project's requirements.

# Technical Choices

## 1. Parsing & Pipeline Architecture
The shell employs a modular parsing strategy divided into Lexer, Tokenizer, and Parser stages to ensure strict compliance with Bash behavior.
- **Tokenization**: The input line is split into tokens while respecting single and double quotes.
- **Pipeline Structure**: Commands separated by pipes are organized into a `t_pipeline` linked list. Each node (`t_cmd`) contains its own `argv` array and a redirection list (`t_redir`).
- **Expansion**: Environment variables ($VAR) and the exit status ($?) are expanded during the parsing phase before execution.

## 2. Robust Memory Management
Adhering to the "zero-leak" policy (excluding `readline`), the project implements a rigorous cleanup strategy.
- **Centralized Freeing**: A `free_pipeline` function systematically deallocates the entire AST-like structure after each execution cycle.
- **Child Process Cleanup**: To eliminate "still reachable" memory in Valgrind, child processes explicitly call a cleanup function to free duplicated heap memory (such as `envp` and command structures) before calling `exit()` or `execve()` failure.

## 3. Signal Handling Strategy
Following the subject's constraints, signal management is designed to be minimal and safe.
- **Global Variable**: A single global integer is used solely to store the signal number, preventing unsafe access to main data structures within the signal handler.
- **Interactive Mode**: Specific handlers for `ctrl-C` and `ctrl-\` ensure the shell remains interactive and responsive, mimicking Bash's behavior.

## 4. Built-in Implementation
Built-in commands are integrated directly into the shell's process to manage the environment and shell state effectively.
- **Environment Management**: `export` and `unset` modify a duplicated environment list, ensuring changes persist throughout the session.
- **Path Lookup**: Commands are resolved by scanning the `PATH` variable or via absolute/relative paths, with careful handling of edge cases where `PATH` is unset.

## 5. Execution Architecture (Execution Part)

The execution layer is responsible for transforming the parsed command structures into
actual running processes. This part focuses on correct process control, file descriptor
management, and faithful reproduction of Bash-like behavior.

The execution logic is divided into **single command execution** and **pipeline execution**.

---

### 5.1 Single Command Execution

When a single command is detected (no pipe):

1. The command is first checked for emptiness.
2. Built-in commands that must affect the shell state (`cd`, `export`, `unset`, `exit`)
   are executed **directly in the parent process**.
3. All other commands are executed in a **child process** created via `fork()`.

For parent-builtins with redirections:
- The original `stdin` and `stdout` are saved using `dup()`
- Redirections are applied
- The built-in is executed
- File descriptors are restored afterward

This ensures that redirections do not permanently affect the shell’s input/output.

---

### 5.2 Pipeline Execution

When multiple commands are connected by pipes:

- Each command runs in its own child process
- Pipes are created dynamically using `pipe()`
- `dup2()` is used to connect:
  - the previous command’s output to the next command’s input
- All unnecessary file descriptors are closed immediately to prevent leaks

Built-in commands inside pipelines are executed **in child processes**, matching Bash behavior.
State-changing built-ins inside pipelines do not affect the parent shell.

The exit status of the **last command in the pipeline** is stored as the shell’s last status.

---

### 5.3 External Command Execution

External commands are executed using `execve()`.

Execution rules:
- If the command contains `/`, it is treated as an absolute or relative path
- Otherwise, the `PATH` environment variable is searched
- If `PATH` is unset or the command is not found:
  - `command not found` is printed
  - exit status `127` is returned
- Permission errors return exit status `126`

Path resolution is implemented manually to strictly follow project constraints.

---

### 5.4 Environment Handling During Execution

- Minishell maintains its own duplicated `envp`
- Built-in commands (`export`, `unset`) modify this internal environment
- External commands receive the updated environment via `execve()`
- Changes persist only during the shell session, as required

---

### 5.5 Signal Handling During Execution

Signal behavior differs between parent and child processes:

- **Parent process**
  - Ignores `SIGINT` and `SIGQUIT` during execution
  - Remains interactive

- **Child processes**
  - Restore default signal behavior
  - Allow signals to terminate commands as in Bash

This separation ensures correct interactive behavior without unexpected shell termination.

---

### 5.6 Exit Handling

The `exit` built-in is executed only in the parent process.

Behavior:
- `exit` without arguments exits with the last command’s status
- Numeric arguments are parsed and reduced to an unsigned char
- Invalid arguments produce an error message and exit status `2`
- When executed, a `should_exit` flag is set to safely terminate the main loop

This avoids abrupt exits and ensures proper memory cleanup.

---

## 6. Summary of Execution Responsibilities

The execution part ensures:

- Correct parent vs child execution logic
- Safe and reversible redirections
- Accurate pipeline behavior
- Persistent environment handling
- Bash-compatible exit statuses and signals

All execution paths were tested extensively using manual tests and Valgrind to ensure
stability and correctness under edge cases.
