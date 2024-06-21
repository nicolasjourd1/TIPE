# Alternative GNU Make workspace makefile autogenerated by Premake

ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifeq ($(config),debug)
  Application_config = debug

else ifeq ($(config),release)
  Application_config = release

else
  $(error "invalid configuration $(config)")
endif

PROJECTS := Application

.PHONY: all clean help $(PROJECTS) 

all: $(PROJECTS)

Application:
ifneq (,$(Application_config))
	@echo "==== Building Application ($(Application_config)) ===="
	@${MAKE} --no-print-directory -C . -f Application.make config=$(Application_config)
endif

clean:
	@${MAKE} --no-print-directory -C . -f Application.make clean

help:
	@echo "Usage: make [config=name] [target]"
	@echo ""
	@echo "CONFIGURATIONS:"
	@echo "  debug"
	@echo "  release"
	@echo ""
	@echo "TARGETS:"
	@echo "   all (default)"
	@echo "   clean"
	@echo "   Application"
	@echo ""
	@echo "For more information, see https://github.com/premake/premake-core/wiki"