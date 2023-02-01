#==============================================================================
SHELL   = sh
#------------------------------------------------------------------------------
NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32m
ERROR_COLOR=\x1b[31m
WARN_COLOR=\x1b[33m
OK_STRING=$(OK_COLOR)✓$(NO_COLOR)
ERROR_STRING=$(ERROR_COLOR)⨯$(NO_COLOR)
WARN_STRING=$(WARN_COLOR)problems$(NO_COLOR)
#------------------------------------------------------------------------------
CC      = gcc
LD      = gcc
CFLAGS  = -O2 -Wall -Wextra
CFLAGS += -Wno-unused-parameter -Wno-unused-function -Wno-unused-result
CFLAGS += -Wno-format-truncation
CFLAGS += -D_XOPEN_SOURCE_EXTENDED
LIBS    = `pkg-config --cflags --libs glib-2.0` -lncurses -lncursesw -lm
INCLDS  = -I $(INC_DIR)
INCLDS += -I $(INC_DIR)/$(MDL_DIR)
INCLDS += -I $(INC_DIR)/$(VIW_DIR)
INCLDS += -I $(INC_DIR)/$(CTL_DIR)
INCLDS_TST  = $(INCLDS)
INCLDS_TST += -I $(INC_DIR_TST)
#------------------------------------------------------------------------------
BIN_DIR = .
BIN_DIR_TST = .
BLD_DIR = build
BLD_DIR_TST = build_tst
DOC_DIR = docs
INC_DIR = includes
INC_DIR_TST = includes_tst
LOG_DIR = log
OUT_DIR = Resultados
SRC_DIR = src
TST_DIR = tests
UTI_DIR = scripts
MDL_DIR = model
VIW_DIR = view
CTL_DIR = controller
#------------------------------------------------------------------------------
PROGRAM = programa-principal
PROGRAM_TST = programa-testes
#------------------------------------------------------------------------------
TRASH   = $(PROGRAM) $(PROGRAM_TST) $(BLD_DIR) $(BLD_DIR_TST) $(DOC_DIR)/{html,latex} $(LOG_DIR) $(OUT_DIR)
#------------------------------------------------------------------------------
MAIN    = $(wildcard $(SRC_DIR)/*.c)

SRC     = $(wildcard $(SRC_DIR)/$(MDL_DIR)/*.c)
SRC    += $(wildcard $(SRC_DIR)/$(VIW_DIR)/*.c)
SRC    += $(wildcard $(SRC_DIR)/$(CTL_DIR)/*.c)
OBJS    = $(patsubst $(SRC_DIR)/%.c,$(BLD_DIR)/%.o,$(MAIN))
OBJS   += $(patsubst $(SRC_DIR)/%.c,$(BLD_DIR)/%.o,$(SRC))
DEPS    = $(patsubst $(BLD_DIR)/%.o,$(BLD_DIR)/%.d,$(OBJS))

TST       = $(wildcard $(TST_DIR)/*.c)
OBJS_TST  = $(patsubst $(TST_DIR)/%.c,$(BLD_DIR_TST)/%.o,$(TST))
OBJS_TST += $(patsubst $(TST_DIR)/%.c,$(BLD_DIR)/%.o,$(SRC))
DEPS_TST  = $(patsubst $(BLD_DIR_TST)/%.o,$(BLD_DIR_TST)/%.d,$(OBJS_TST))
#==============================================================================

vpath %.c $(SRC_DIR)
vpath %.c $(TST_DIR)

.DEFAULT_GOAL = build

define show
@./$(UTI_DIR)/fmt.sh --color $(1) --type $(2) $(3)
endef

$(BLD_DIR)/%.d: %.c
	-$(call show,cyan,reset,"Generating $(shell basename $@) ... ")
	@$(CC) -M $(INCLDS) $(LIBS) $(CFLAGS) $< -o $@
	@echo -e "$(OK_STRING)"

$(BLD_DIR)/%.o: %.c
	-$(call show,blue,reset,"Building $(shell basename $@) ... ")
	@$(CC) -c $(INCLDS) $(LIBS) $(CFLAGS) $< -o $@
	@echo -e "$(OK_STRING)"

$(BIN_DIR)/$(PROGRAM): $(DEPS) $(OBJS)
	-$(call show,green,bold,"Compiling $(shell basename $@) ... ")
	@$(CC) $(INCLDS) $(CFLAGS) -o $@ $(OBJS) $(LIBS)
	@echo -e "$(OK_STRING)"

$(BLD_DIR_TST)/%.d: %.c
	-$(call show,cyan,reset,"Generating $(shell basename $@) ... ")
	@$(CC) -M $(INCLDS_TST) $(LIBS) $(CFLAGS) $< -o $@
	@echo -e "$(OK_STRING)"

$(BLD_DIR_TST)/%.o: %.c
	-$(call show,blue,reset,"Building $(shell basename $@) ... ")
	@$(CC) -c $(INCLDS_TST) $(LIBS) $(CFLAGS) $< -o $@
	@echo -e "$(OK_STRING)"

$(BIN_DIR_TST)/$(PROGRAM_TST): $(DEPS_TST) $(OBJS_TST)
	-$(call show,green,bold,"Compiling $(shell basename $@) ... ")
	@$(CC) $(INCLDS_TST) $(CFLAGS) -o $@ $(OBJS_TST) $(LIBS)
	@echo -e "$(OK_STRING)"

.PHONY: build # Compile binary program
build compile: setup $(BIN_DIR)/$(PROGRAM) $(BIN_DIR_TST)/$(PROGRAM_TST)

run go: build
	@./$(BIN_DIR)/$(PROGRAM) $(ARGS)

.PHONY: test # Run tests
test: build
	@./$(BIN_DIR)/$(PROGRAM_TST) $(ARGS)

.PHONY: format fmt # Format source files and scripts
format fmt:
	-$(call show,yellow,reset,"C and Headers files")
	@echo ":"
	@-clang-format -verbose -i $(SRC_DIR)/*.c $(INC_DIR)/*.h
	@-clang-format -verbose -i $(SRC_DIR)/$(MDL_DIR)/*.c $(SRC_DIR)/$(CTL_DIR)/*.c $(SRC_DIR)/$(VIW_DIR)/*.c
	@-clang-format -verbose -i $(INC_DIR)/$(MDL_DIR)/*.h $(INC_DIR)/$(CTL_DIR)/*.h $(INC_DIR)/$(VIW_DIR)/*.h
	@-clang-format -verbose -i $(TST_DIR)/*.c $(INC_DIR_TST)/*.h
	@echo ""
	-$(call show,yellow,reset,"Shell files")
	@echo ":"
	@shfmt -w -i 2 -l -ci .

.PHONY: lint # Lint code
lint:
	@splint -retvalint -hints -I $(INC_DIR) \
		$(SRC_DIR)/*

.PHONY: check # Check for memory leaks with valgrind
check: LOG = $(LOG_DIR)/`date +%Y-%m-%d_%H:%M:%S`
check: CFLAGS += -g -Og
check: build
	@valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all \
		--log-file=$(LOG).log ./$(BIN_DIR)/$(PROGRAM) $(ARGS)

.PHONY: debug # Run program with debugger
debug: CFLAGS = -Wall -Wextra -O0 -g -D_XOPEN_SOURCE_EXTENDED
debug: build
	gdb ./$(BIN_DIR)/$(PROGRAM)

.PHONY: doc # Generate documentation
documentation doc:
	@doxygen $(DOC_DIR)/Doxyfile

setup:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(BLD_DIR)
	@mkdir -p $(BLD_DIR_TST)
	@mkdir -p $(BLD_DIR)/$(MDL_DIR)
	@mkdir -p $(BLD_DIR)/$(VIW_DIR)
	@mkdir -p $(BLD_DIR)/$(CTL_DIR)
	@mkdir -p $(LOG_DIR)
	@mkdir -p $(OUT_DIR)

.PHONY: clean # Delete build artifacts
clean:
	@echo -n "Cleaning ... "
	@-rm -rf $(TRASH)
	@echo -e "$(OK_STRING)"

.PHONY: help # Generate list of targets with descriptions
help:
	@grep '^.PHONY: .* #' Makefile | sed 's/\.PHONY: \(.*\) # \(.*\)/    \1 \t \2/'

