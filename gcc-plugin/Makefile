PLUGIN=plugin.so
SOURCES=        plugin.cc 		$(END)

include ../Makefile.common

.PHONY: test
test: $(PLUGIN)
	$(CCPLUGIN) -c -o /dev/null ./uudecode/uudecode.c
