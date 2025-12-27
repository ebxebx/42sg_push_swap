*This project has been created as part of the 42 curriculum by zchoo.*

# Description

The goal of this project is:


Internally, the project uses:


# Instructions
### Compilation

To compile the project (mandatory part only):

```bash
make
```

Compile and run:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
   get_next_line_bonus.c get_next_line_utils_bonus.c main.c \
   -o gnl_test

./gnl_test test1.txt test2.txt test3.txt
```

You can also use Valgrind to check for memory leaks and invalid accesses:
```bash
valgrind --leak-check=full --show-leak-kinds=all ./gnl_test some_file.txt
```

# Resources
## Documentation & references

## Tester

## Use of AI in this project
AI (ChatGPT) was used during this project in the following ways:
