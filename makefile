CC = gcc
CCFLAGS = -Wall -Wextra -Werror -pedantic
NDEBUG = -DNDEBUG

SRCDIR = src
OBJDIR = build
DEBUG_OBJSDIR = debug_build
INCDIR = inc

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
DEBUG_OBJS = $(patsubst $(SRCDIR)/%.c, $(DEBUG_OBJSDIR)/%.o, $(SRCS))
INCS = $(wildcard $(INCDIR)/*.h)

NAME = main.out

all: run

run: build
	@echo "\n\nRunning $(NAME)\n\n"
	@./$(NAME)

build: $(NAME)

$(NAME): main.c $(OBJS) $(INCS)
	$(CC) $(CCFLAGS) $(NDEBUG) -I$(INCDIR) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCS)
	@mkdir -p $(OBJDIR)
	$(CC) $(CCFLAGS) $(NDEBUG) -I$(INCDIR) -c -o $@ $<

debug: debug_run

debug_run: debug_build
	@echo "\n\nRunning debug_$(NAME)\n\n"
	@./debug_$(NAME)

debug_build: debug_$(NAME)

debug_$(NAME): main.c $(DEBUG_OBJS) $(INCS)
	$(CC) $(CCFLAGS) -I$(INCDIR) -o $@ $^

$(DEBUG_OBJSDIR)/%.o: $(SRCDIR)/%.c $(INCS)
	@mkdir -p $(DEBUG_OBJSDIR)
	$(CC) $(CCFLAGS) -I$(INCDIR) -c -o $@ $<


clean:
	rm -rf $(OBJDIR)
	rm -rf $(DEBUG_OBJSDIR)
	rm -f $(NAME)
	rm -f debug_$(NAME)
	rm -f *.zip

re: clean all

zip:
	zip -r EmirhanAltunel_200104004035_hw1.zip src inc makefile main.c

.PHONY: all clean re zip run build debug debug_run debug_build