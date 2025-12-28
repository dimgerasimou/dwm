# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRCDIR   = src
INCDIR   = $(SRCDIR)/inc
BUILDDIR = build
OBJDIR   = $(BUILDDIR)/obj
BINDIR   = $(BUILDDIR)/bin
DOCDIR   = docs

SRC = drw.c dwm.c util.c
OBJ = $(SRC:%.c=$(OBJDIR)/%.o)

BIN = $(BINDIR)/dwm

CPPFLAGS += -I$(INCDIR) -I.

# Pretty Output
ECHO := /bin/echo -e
COLOR_RESET := \033[0m
COLOR_GREEN := \033[1;32m
COLOR_YELLOW := \033[1;33m
COLOR_BLUE := \033[1;34m
COLOR_MAGENTA := \033[1;35m
COLOR_CYAN := \033[1;36m

all: $(BIN)

$(OBJDIR) $(BINDIR):
	@mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@$(ECHO) "$(COLOR_BLUE)Compiling:$(COLOR_RESET) $<"
	@$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@

$(OBJ): config.h config.mk

config.h:
	@$(ECHO) "$(COLOR_MAGENTA)Using default config:$(COLOR_RESET) $@"
	@cp config.def.h $@

$(BIN): $(OBJ) | $(BINDIR)
	@$(ECHO) "$(COLOR_GREEN)Linking:$(COLOR_RESET) $@"
	@$(CC) -o $@ $(OBJ) $(LDFLAGS)

clean:
	@$(ECHO) "$(COLOR_YELLOW)Cleaning...$(COLOR_RESET)"
	@rm -rf $(BUILDDIR)

install: all
	@$(ECHO) "$(COLOR_CYAN)Installing dwm at:$(COLOR_RESET) $(DESTDIR)$(PREFIX)/bin/dwm"
	@mkdir -p $(DESTDIR)$(PREFIX)/bin
	@cp -f $(BIN) $(DESTDIR)$(PREFIX)/bin/dwm
	@chmod 755 $(DESTDIR)$(PREFIX)/bin/dwm
	@mkdir -p $(DESTDIR)$(MANPREFIX)/man1
	@sed "s/VERSION/$(VERSION)/g" < $(DOCDIR)/dwm.1 > $(DESTDIR)$(MANPREFIX)/man1/dwm.1
	@chmod 644 $(DESTDIR)$(MANPREFIX)/man1/dwm.1

uninstall:
	@$(ECHO) "$(COLOR_MAGENTA)Uninstalling dwm from:$(COLOR_RESET) $(DESTDIR)$(PREFIX)/bin/dwm"
	@rm -f $(DESTDIR)$(PREFIX)/bin/dwm $(DESTDIR)$(MANPREFIX)/man1/dwm.1

.PHONY: all clean install uninstall

