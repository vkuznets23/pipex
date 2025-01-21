## Overview
The pipex project is a recreation of the Unix shell pipeline (|) functionality in C. It takes two commands and connects them using a pipe, allowing the output of the first command to serve as the input for the second. The program replicates the following shell behavior:

**Authorized Functions**: 
`open`, `close`, `read`, `write`, `malloc`, `free`, `perror`, `strerror`, `access`, `dup`, `dup2`, `execve`, `exit`, `fork`, `pipe`, `unlink`, `wait`, `waitpid`
Any equivalent functions coded by you (e.g., `ft_printf`)

## Table of contents

## How It Works
**Process Creation:**
- The program creates two child processes using fork():
- The first child process executes cmd1, redirecting input from file1 and output to the pipe.
- The second child process executes cmd2, redirecting input from the pipe and output to file2.

**Piping:**
- The pipe() system call creates a unidirectional data channel between cmd1 and cmd2.

**File Redirection:**
- Input redirection is achieved using dup2() to replace standard input/output with file descriptors.

**Command Execution:**
- The execve() function is used to replace the child processes with the specified commands.

## Limitation
- Commands must be provided with their full paths if they are not in the PATH environment variable.
- The program does not handle shell-specific syntax like pipes (|) or redirects (>/<) beyond the specified use case.

## Getting started
``` bash
git clone https://github.com/vkuznets23/pipex pipex
cd pipex
make
```

## Execution
The program is using the following syntax:

``` bash
./pipex < file1 cmd1 | cmd2 > file2
```
- `file1`: The input file to read data from.
- `cmd1`: The first shell command with its parameters (quoted).
- `cmd2`: The second shell command with its parameters (quoted).
- `file2`: The output file to write the final result

## Usage examples
### Command
``` bash
./pipex infile "ls -l" "wc -l" outfile
```

### Shell Equivalent
``` bash
< infile ls -l | wc -l > outfile
```

### Command
``` bash
./pipex infile "grep a1" "wc -w" outfile
```

### Shell Equivalent
``` bash
< infile grep a1 | wc -w > outfile
```

## Contribution
Contributions are welcome! If you find a bug or have a suggestion for improvement, feel free to open an issue or submit a pull reques
