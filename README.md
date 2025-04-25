# Minishell

Minishell is a custom implementation of a command-line interpreter that replicates core functionalities found in standard Unix shells. This project demonstrates fundamental concepts of Unix systems programming, including process management, file operations, and command interpretation.

## Authors
Minishell is developed as a team with [Nadia Galleze](https://github.com/Nadzg) as part of the 42 School curriculum, designed to deepen our understanding of Unix systems, process management, and interpreter design principles.

## Key Features

### Command Interpretation & Execution

Path-based executable location
Support for absolute and relative paths
Command history navigation

### Shell Grammar Support

Quote handling (single and double quotes)
Environment variable expansion
Exit status access ($?)

### I/O Capabilities

Standard input/output redirection
Append mode for output redirection
Here-document functionality
Command pipelines

### Interactive Controls

Signal handling (Ctrl+C, Ctrl+D, Ctrl+)
Command history retention

### Core Built-in Commands

echo: Text display with option support
cd: Directory navigation
pwd: Current directory reporting
export: Environment variable management
unset: Environment variable removal
env: Environment listing
exit: Shell termination

## Usage Examples

### Basic command execution
minishell> ls -la

### I/O redirection
minishell> cat < input.txt > output.txt

### Pipeline processing
minishell> cat file.txt | grep pattern | sort

### Environment variable usage
minishell> echo $HOME

## Implementation Notes
This project adheres to strict memory management practices and follows standard Unix programming conventions. The implementation focuses on reliability and correctness while maintaining a clean codebase. This implementation uses the GNU Readline library for command-line input handling. Please note that Readline is known to have its own memory management characteristics. For more information on Readline's memory management, refer to the [GNU Readline documentation](https://tiswww.case.edu/php/chet/readline/readline.html).
