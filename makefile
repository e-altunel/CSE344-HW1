CC = gcc
RELEASE_FLAGS = -O2 -Wall -Wextra -Werror -std=c99 -pedantic -DNDEBUG
DEBUG_FLAGS = -g3 -Wall -Wextra -Werror -std=c99 -pedantic
TEST_FLAGS = $(DEBUG_FLAGS) 
AR = ar
ARFLAGS = rcs
MEMCHECKFLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1 --trace-children=yes -q
MEMCHECK = valgrind $(MEMCHECKFLAGS) 

SRCDIR = src
OBJDIR = obj
DOBJDIR = debug
INCDIR = inc
LIBDIR = lib
BINDIR = bin
TESTDIR = test
TESTOBJDIR = $(TESTDIR)/obj
TESTINCDIR = $(TESTDIR)/inc
TESTBINDIR = $(TESTDIR)/bin

SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))
DOBJ = $(patsubst $(SRCDIR)/%.c, $(DOBJDIR)/%.o, $(SRC))
INC = $(wildcard $(INCDIR)/*.h)
TESTSRC = $(wildcard $(TESTDIR)/*.c)
TESTOBJ = $(patsubst $(TESTDIR)/%.c, $(TESTOBJDIR)/%.o, $(TESTSRC))
TESTINC = $(wildcard $(TESTINCDIR)/*.h)
TESTBIN = $(patsubst $(TESTDIR)/%.c, $(TESTBINDIR)/%.out, $(TESTSRC))

TARGET_NAME = cse344
TARGET = lib$(TARGET_NAME).a
DTARGET = lib$(TARGET_NAME)d.a
NAME = main
DNAME = maind

TARGET_PATH = $(LIBDIR)/$(TARGET)
DTARGET_PATH = $(LIBDIR)/$(DTARGET)
NAME_PATH = $(BINDIR)/$(NAME).out
DNAME_PATH = $(BINDIR)/$(DNAME).out

all: $(TARGET_PATH) $(NAME_PATH)

debug: $(DTARGET_PATH) $(DNAME_PATH)

$(TARGET_PATH): $(OBJ)
	@mkdir -p $(LIBDIR)
	@echo "\033[1;33mCreating\033[0m $@"
	@$(AR) $(ARFLAGS) $@ $^

$(NAME_PATH): $(TARGET_PATH) $(NAME).c
	@mkdir -p $(BINDIR)
	@echo "\033[1;33mLinking\033[0m $<"
	@$(CC) $(RELEASE_FLAGS) -I$(INCDIR) -L$(LIBDIR) -o $@ $(NAME).c -l$(TARGET_NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC)
	@mkdir -p $(OBJDIR)
	@echo "\033[1;33mCompiling\033[0m $<"
	@$(CC) $(RELEASE_FLAGS) -I$(INCDIR) -c $< -o $@

$(DTARGET_PATH): $(DOBJ)
	@mkdir -p $(LIBDIR)
	@echo "\033[1;33mCreating\033[0m $@"
	@$(AR) $(ARFLAGS) $@ $^

$(DNAME_PATH): $(DTARGET_PATH) $(NAME).c
	@mkdir -p $(BINDIR)
	@echo "\033[1;33mLinking\033[0m $<"
	@$(CC) $(DEBUG_FLAGS) -I$(INCDIR) -L$(LIBDIR) -o $@ $(NAME).c -l$(TARGET_NAME)d

$(DOBJDIR)/%.o: $(SRCDIR)/%.c $(INC)
	@mkdir -p $(DOBJDIR)
	@echo "\033[1;33mCompiling\033[0m $<"
	@$(CC) $(DEBUG_FLAGS) -I$(INCDIR) -c $< -o $@


test: $(TESTBIN)
	@echo "\033[1;32mRunning tests...\033[0m\n"
	@for test in $(TESTBIN); do \
		echo "\033[1;32mRunning\033[0m $$test"; \
	  $(MEMCHECK) $$test; \
		echo "\n"; \
	done
	
$(TESTBINDIR)/%.out: $(TESTOBJDIR)/%.o $(TARGET_PATH) $(INC) $(TESTINC)
	@mkdir -p $(TESTBINDIR)
	@echo "\033[1;33mLinking\033[0m $<"
	@$(CC) $(TEST_FLAGS) -I$(INCDIR) -I$(TESTINCDIR) -L$(LIBDIR) -o $@ $< -l$(TARGET_NAME)

$(TESTOBJDIR)/%.o: $(TESTDIR)/%.c $(INC) $(TESTINC)
	@mkdir -p $(TESTOBJDIR)
	@echo "\033[1;33mCompiling\033[0m $<"
	@$(CC) $(TEST_FLAGS) -I$(INCDIR) -I$(TESTINCDIR) -c $< -o $@

test-file: $(TESTBINDIR)/$(TESTFILE).out
	@echo "\033[1;32mRunning tests...\033[0m\n"
	@echo "\033[1;32mRunning\033[0m $(TESTBINDIR)/$(TESTFILE).out"
	@$(MEMCHECK) $(TESTBINDIR)/$(TESTFILE).out
	

clean:
	@echo "\033[1;31mCleaning...\033[0m"
	@rm -rf $(OBJDIR) $(DOBJDIR) $(LIBDIR) $(BINDIR) $(TESTBINDIR) $(TESTOBJDIR)

re: clean all

.PHONY: all clean re debug test
.PRECIOUS: $(OBJ) $(DOBJ) $(TESTOBJ)