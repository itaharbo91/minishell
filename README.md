# Minishell

A minimal but feature-rich UNIX shell implementation written in C, supporting pipes, redirections, builtins, and more.

> ⭐ **Project completed with all bonus features implemented**

## 📋 Description

**Minishell** is a collaborative project implementing a functional shell that replicates core `bash` functionality. This implementation includes **all mandatory requirements plus bonus features**. It features:

- **Complete lexer/parser** with Abstract Syntax Tree (AST) generation
- **Logical operators** (`&&`, `||`) with short-circuit evaluation **[BONUS]**
- **Command grouping** with parentheses `()` (subshells) **[BONUS]**
- **Pipes and redirections** (>, <, >>, <<)
- **Built-in commands** (cd, pwd, echo, env, export, unset, exit)
- **Environment variable expansion** ($VAR, $?)
- **Quote handling** (single `'` and double `"` quotes with different expansion rules)
- **Word splitting** after variable expansion
- **Wildcard expansion** (*, ?, [...]) **[BONUS]**
- **Heredoc support** (<<) with multiple heredocs
- **Signal handling** (CTRL+C, CTRL+D, CTRL+\)
- **Command execution** with proper exit codes and PATH resolution

## 🚀 Compilation

```bash
make          # Compile the shell
make clean    # Remove object files
make fclean   # Remove everything including binary
make re       # Recompile from scratch
```

### Requirements

```bash
# Linux
sudo apt-get install libreadline-dev

# macOS
brew install readline
```

## 💻 Usage

```bash
./minishell
```

Once in the shell:
```bash
minishell$ ls -la                        # External commands
minishell$ echo "Hello"                  # Builtin: echo
minishell$ cd /tmp                       # Builtin: cd (with -, ~ support)
minishell$ export VAR=value              # Builtin: export
minishell$ cat file | grep pattern       # Pipes
minishell$ cat < input > output          # Redirections
minishell$ cat << EOF                    # Heredoc
minishell$ $HOME/file                    # Variable expansion
minishell$ ls *.c                        # Wildcards
minishell$ echo '$VAR'                   # Single quotes: no expansion
minishell$ echo "$VAR"                   # Double quotes: expansion
minishell$ cmd1 && cmd2                  # AND: cmd2 only if cmd1 succeeds
minishell$ cmd1 || cmd2                  # OR: cmd2 only if cmd1 fails
minishell$ (cmd1 | cmd2) > output        # Grouping with redirections
minishell$ exit 42                       # Exit with status
minishell$ CTRL+C, CTRL+D, CTRL+\        # Signal handling
```

## 🧠 Architecture

### 1. Lexer (Tokenization)

Converts input string into tokens:
```
Input: echo "hello world" | grep hello
↓
Tokens: [echo, "hello world", |, grep, hello]
```

**Components:**
- `lexer.c` - Main tokenization loop
- `tokenizer.c` - Token identification
- `quote_token.c` - Quoted string handling
- `word_token.c` - Word/variable token parsing
- `meta_tokens.c` - Operators (|, >, <, >>, <<)

### 2. Parser (AST Generation)

Builds Abstract Syntax Tree from tokens with operator precedence:
```
Input: echo hello && cat file || ls
↓
AST Structure:
         OR
        /  \
      AND   LS
      /  \
    ECHO  CAT
```

**Parsing Hierarchy (by precedence):**
1. **Logical operators** (`&&`, `||`) - lowest precedence **[BONUS]**
   - `parse_and_or.c` - Handles AND/OR with short-circuit evaluation
2. **Pipes** (`|`)
   - `parse_pipe.c` - Connects commands with pipes
3. **Command groups** (`()`) **[BONUS]**
   - `parse_group.c` - Subshells with isolated redirections
4. **Simple commands** (arguments + redirections)
   - `parse_cmd.c` - Parses individual commands

**Key features:**
- Operator precedence: `||` = `&&` < `|` < simple commands
- Short-circuit evaluation for `&&` and `||`
- Subshell execution for grouped commands `()`
- Redirection binding per command/group
- Comprehensive error detection

### 3. Expander (Variable & Wildcard Processing)

**Quote Handling:**
```bash
# Single quotes: NO expansion
echo '$HOME'            → $HOME (literal)
echo '$USER'            → $USER (literal)

# Double quotes: YES expansion
echo "$HOME"            → /home/user
echo "Hello $USER"      → Hello itaharbo
echo "\$VAR"            → $VAR (escaped)

# No quotes: expansion + word splitting
echo $PATH              → /usr/bin /usr/local/bin (splits on IFS)
```

**Variable Expansion ($VAR):**
```bash
echo $HOME              → /home/user
echo "$USER"            → itaharbo
echo $?                 → [exit code of last command]
echo ${VAR}             → Variable with braces
```

**Word Splitting:**
After variable expansion, unquoted results are split on whitespace (IFS):
```bash
VAR="one two three"
echo $VAR               → one two three (3 separate arguments)
echo "$VAR"             → one two three (1 argument)
```

**Wildcard Expansion (*, ?, [...]):**
```bash
ls *.c                  → Expands to all .c files
ls file?.txt            → Matches: file1.txt, filea.txt
ls [abc]*.c             → Matches: a*.c, b*.c, c*.c
```
> **[BONUS]** - Full wildcard implementation with directory traversal

**Implementation files:**
- `consume_single_quote.c` - Single quote: preserve everything literally
- `consume_double_quote.c` - Double quote: expand variables, keep spaces
- `consume_unquoted.c` - No quotes: expand + word split
- `expand_variable.c` - $VAR and $? expansion
- `word_split.c` - Split expanded values on whitespace
- `wildcards*.c` (5 files) - Pattern matching implementation

### 4. Executor (Command Execution)

Handles command execution with logical operators:

**Logical Operators (`&&`, `||`):**
```bash
# AND: execute cmd2 ONLY if cmd1 succeeds (exit code 0)
cmd1 && cmd2

# OR: execute cmd2 ONLY if cmd1 fails (exit code != 0)
cmd1 || cmd2

# Complex chains
cmd1 && cmd2 || cmd3    # If cmd1 OK: run cmd2, else: run cmd3
```
> **[BONUS]** - Short-circuit evaluation implementation

**Command Types:**
- **Built-in commands** - execute in shell process (no fork)
- **External commands** - fork/exec child process
- **Pipes** - connect processes with pipes
- **Redirections** - redirect stdin/stdout/stderr
- **Heredoc** - handle << operator
- **Grouped commands** `()` - execute in subshell with own environment **[BONUS]**

**Execution flow:**
```
Logical operator (&&/||)? → Evaluate left, conditionally execute right
    ↓ No
Built-in? → Execute in shell
    ↓ No
Fork child process
    ↓
Find command in PATH
    ↓
Apply redirections
    ↓
Execute (execve syscall)
```

**Implementation files:**
- `executor.c` - Main execution dispatcher
- `exec_cmd.c` - Simple command execution
- `exec_pipe.c` - Pipeline execution
- `exec_builtins.c` - Built-in command dispatcher
- `external_cmd.c` - External command execution with PATH
- `find_path.c` - PATH resolution
- `heredoc.c`, `mult_heredoc.c` - Heredoc handling
- `redirections.c` - File descriptor manipulation

### 5. Built-in Commands

```bash
echo [-n] [args...]      # Print arguments
cd [path]                # Change directory (supports -, ~)
pwd                      # Print working directory
export VAR=value         # Export variable to environment
env                       # Display environment variables
unset VAR                # Remove variable
exit [code]              # Exit shell with optional code
```

**Key details:**
- `cd` supports:
  - `cd ..` - parent directory
  - `cd -` - previous directory
  - `cd ~` - home directory
  - Relative and absolute paths
- `echo` supports `-n` flag to suppress newline
- `export` makes variables available to child processes
- Exit codes properly tracked and returned

## 📊 Technical Details

### Pipe Implementation

```
cmd1 | cmd2 | cmd3

Fork: cmd1
├─ Close stdout
├─ dup2(pipe1_write)
└─ Exec cmd1

Fork: cmd2
├─ dup2(pipe1_read) → stdin
├─ dup2(pipe2_write) → stdout
└─ Exec cmd2

Fork: cmd3
├─ dup2(pipe2_read) → stdin
└─ Exec cmd3

Parent: wait for all children
```

### Redirection Handling

```bash
cmd > file              # Redirect stdout to file (create/truncate)
cmd >> file             # Redirect stdout to file (append)
cmd < file              # Redirect stdin from file
cmd << DELIMITER        # Heredoc: read until DELIMITER

cmd > out 2>&1          # Redirect both stdout and stderr
cmd 2> error.log        # Redirect stderr
```

### Signal Management

- **CTRL+C (SIGINT)** - Cancel current command
- **CTRL+D (EOF)** - Exit shell gracefully
- **CTRL+\ (SIGQUIT)** - Quit with core dump (bash-like behavior)

### Exit Status Tracking

```bash
$?                      # Exit code of last command
minishell$ false; echo $?
1
minishell$ true; echo $?
0
minishell$ cmd_not_found; echo $?
127
```

## 📈 Parsing Strategy

**Input:** `echo "hello" | cat < file > out`

**Lexer Output:**
```
WORD(echo) QUOTE(hello) PIPE WORD(cat) REDIR_IN(file) REDIR_OUT(out)
```

**Parser Output (AST):**
```
COMMAND_LIST
  ├─ CMD_NODE(echo "hello")
  │  └─ NEXT → PIPE
  │
  └─ CMD_NODE(cat)
     ├─ STDIN: < file
     ├─ STDOUT: > out
     └─ PREV ← PIPE
```

## 🧪 Testing

```bash
# Basic commands
./minishell
minishell$ echo test
minishell$ pwd
minishell$ ls -la

# Variables
minishell$ export TEST=hello
minishell$ echo $TEST
minishell$ unset TEST
minishell$ echo $TEST

# Quotes
minishell$ echo '$HOME'              # Prints: $HOME (no expansion)
minishell$ echo "$HOME"              # Prints: /home/user (expansion)
minishell$ echo Hello   World        # Word splitting
minishell$ echo "Hello   World"      # Preserves spaces

# Logical operators
minishell$ true && echo "success"    # Prints: success
minishell$ false && echo "won't print"
minishell$ false || echo "printed"   # Prints: printed
minishell$ true || echo "won't print"
minishell$ cmd1 && cmd2 && cmd3      # Chain of AND
minishell$ cmd1 || cmd2 || cmd3      # Chain of OR

# Command grouping
minishell$ (echo a; echo b) | cat    # Subshell piped to cat
minishell$ (cd /tmp && ls) && pwd    # Grouped commands, then pwd
minishell$ (echo test) > file.txt    # Redirect group output

# Pipes
minishell$ ls | grep .c | wc -l
minishell$ cat file | sort | uniq

# Redirections
minishell$ echo "test" > file.txt
minishell$ cat < file.txt
minishell$ echo "more" >> file.txt
minishell$ cat file.txt | wc

# Heredoc
minishell$ cat << EOF
minishell> hello
minishell> world
minishell> EOF

# Exit codes
minishell$ false; echo $?            # Prints: 1
minishell$ true; echo $?             # Prints: 0
minishell$ ls /nonexistent 2>/dev/null; echo $?  # Prints: 127

# Wildcards
minishell$ ls *.c
minishell$ echo file[0-9].txt
minishell$ rm test?.txt
```

## 📚 Project Structure

```
minishell/
├── Makefile
├── includes/
│   ├── minishell.h          # Main header
│   └── minishell_structs.h  # Data structures (AST nodes, tokens)
├── libft/                   # Custom C library
├── srcs/
│   ├── main.c               # Entry point
│   ├── init_shell.c         # Shell initialization
│   ├── prompt.c             # Prompt display with readline
│   │
│   ├── lexer/               # Tokenization (5 files)
│   │   ├── lexer.c          # Main tokenization loop
│   │   ├── tokenizer.c      # Token type detection
│   │   ├── quote_token.c    # Quote handling
│   │   ├── word_token.c     # Word/variable tokens
│   │   └── meta_tokens.c    # Operator tokens (|, &&, ||, >, <)
│   │
│   ├── parser/              # AST Construction (5 files)
│   │   ├── parser.c         # Entry point
│   │   ├── parse_and_or.c   # Logical operators (&&, ||)
│   │   ├── parse_pipe.c     # Pipe operator (|)
│   │   ├── parse_group.c    # Command grouping with ()
│   │   ├── parse_cmd.c      # Simple commands
│   │   └── parser_utils.c   # Helper functions
│   │
│   ├── expands/             # Expansion Engine (9 files)
│   │   ├── expand.c         # Main expansion dispatcher
│   │   ├── expand_token.c   # Token-level expansion
│   │   ├── expand_variable.c        # $VAR and $? expansion
│   │   ├── consume_single_quote.c   # Single quotes (no expansion)
│   │   ├── consume_double_quote.c   # Double quotes (with expansion)
│   │   ├── consume_unquoted.c       # Unquoted (expansion + split)
│   │   ├── word_split.c             # Word splitting on IFS
│   │   ├── expand_helpers.c         # Helper functions
│   │   └── expand_token_helpers.c   # Token helpers
│   │
│   ├── wildcards/           # Pattern Matching (5 files)
│   │   ├── wildcards.c                 # Main wildcard logic
│   │   ├── wildcards_pattern_match.c   # Pattern matching (*, ?, [...])
│   │   ├── wildcards_directory.c       # Directory reading
│   │   ├── wildcards_handlers.c        # Match handlers
│   │   └── wildcards_token_utils.c     # Utility functions
│   │
│   ├── executor/            # Execution Engine (9 files)
│   │   ├── executor.c       # Main execution dispatcher
│   │   ├── exec_cmd.c       # Simple command execution
│   │   ├── exec_pipe.c      # Pipeline execution
│   │   ├── exec_builtins.c  # Built-in dispatcher
│   │   ├── external_cmd.c   # External command execution
│   │   ├── find_path.c      # PATH resolution
│   │   ├── heredoc.c        # Heredoc processing
│   │   ├── mult_heredoc.c   # Multiple heredoc support
│   │   ├── redirections.c   # File descriptor manipulation
│   │   └── init_and_dup.c   # FD duplication
│   │
│   ├── builtins/            # Built-in Commands (11 files)
│   │   ├── cd.c             # Change directory
│   │   ├── cd_helpers.c     # CD helpers (-, ~, ..)
│   │   ├── pwd.c            # Print working directory
│   │   ├── echo.c           # Echo with -n flag
│   │   ├── env.c            # Display environment
│   │   ├── export.c         # Export variables
│   │   ├── export_utils.c   # Export helpers
│   │   ├── unset.c          # Unset variables
│   │   ├── exit.c           # Exit shell
│   │   ├── add_exported.c   # Variable management
│   │   └── env_to_envp.c    # Environment conversion
│   │
│   └── utils/               # Utilities (5 files)
│       ├── signals.c        # Signal handlers (SIGINT, SIGQUIT)
│       ├── sig_heredoc.c    # Heredoc signal handling
│       ├── all_utilities.c  # General utilities
│       └── utils_2.c        # More utilities
│
└── tests/                   # Test scripts
```

**Total: 53 C files** implementing a complete shell with advanced features.

## 🎓 42 School

Common Core Project - Cercle 3

## 📌 Key Features Implemented

### Mandatory Part ✅
✅ **Complete Shell Loop** - prompt, parse, execute, repeat
✅ **Lexer/Parser** - Proper tokenization and AST generation with operator precedence
✅ **Pipes** - Multiple pipes with proper process management
✅ **Redirections** - Input/Output/Append/Heredoc redirections (`<`, `>`, `>>`, `<<`)
✅ **Heredoc** - Multi-line input with multiple heredoc support
✅ **Built-in Commands** - cd, pwd, echo, env, export, unset, exit
✅ **Variable Expansion** - $VAR, $?, $HOME, etc.
✅ **Quote Handling** - Single quotes (literal) vs double quotes (expansion)
✅ **Signal Handling** - CTRL+C, CTRL+D, CTRL+\
✅ **Exit Status Tracking** - Proper exit codes
✅ **Environment Variables** - Full environment management
✅ **Memory Management** - Proper cleanup and leak prevention

### Bonus Part ⭐
✅ **Logical Operators** - `&&` (AND) and `||` (OR) with short-circuit evaluation
✅ **Command Grouping** - Subshells with `()` for isolated execution
✅ **Wildcard Expansion** - `*`, `?`, `[abc]` patterns with directory traversal
✅ **Word Splitting** - IFS-based splitting after variable expansion

## 🤝 Collaboration

Co-developed with raisufaj. Collaborative project with shared responsibility on all components.

## 👤 Authors

[@itaharbo91](https://github.com/itaharbo91)
[@raisufaj](https://github.com/raisufaj)

---

**GitHub Description**: Feature-complete UNIX shell with all bonus features: logical operators (&&/||), subshells, wildcards, pipes, redirections, quote handling, and variable expansion - 53 C files implementing a full bash-like interpreter.