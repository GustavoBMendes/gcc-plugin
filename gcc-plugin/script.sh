#!/bin/bash

echo "Primeiro programa teste"

sleep 1

echo -e "PLUGIN=plugin.so
SOURCES=\
        plugin.cc \
		\$(END)

include ../Makefile.common

.PHONY: test
test: \$(PLUGIN)
	\$(CCPLUGIN) -c -o /dev/null ./8b10b/main.c" > Makefile

make clean 
make 
make test

echo "______________________"
echo "Segundo Programa teste"

sleep 1

echo -e "PLUGIN=plugin.so
SOURCES=\
        plugin.cc \
		\$(END)

include ../Makefile.common

.PHONY: test
test: \$(PLUGIN)
	\$(CCPLUGIN) -c -o /dev/null ./almabench/almabench.c" > Makefile

make clean
make
make test

echo "______________________"
echo "Terceiro Programa teste"

sleep 1

echo -e "PLUGIN=plugin.so
SOURCES=\
        plugin.cc \
		\$(END)

include ../Makefile.common

.PHONY: test
test: \$(PLUGIN)
	\$(CCPLUGIN) -c -o /dev/null ./correlation/correlation.c" > Makefile

make clean
make
make test

echo "______________________"
echo "Quarto Programa teste"

sleep 1

echo -e "PLUGIN=plugin.so
SOURCES=\
        plugin.cc \
		\$(END)

include ../Makefile.common

.PHONY: test
test: \$(PLUGIN)
	\$(CCPLUGIN) -c -o /dev/null ./health/health.c" > Makefile

make clean
make
make test

echo "______________________"
echo "Quinto Programa teste"

sleep 1

echo -e "PLUGIN=plugin.so
SOURCES=\
        plugin.cc \
		\$(END)

include ../Makefile.common

.PHONY: test
test: \$(PLUGIN)
	\$(CCPLUGIN) -c -o /dev/null ./Linpack/linpack-pc.c" > Makefile

make clean
make
make test

echo "______________________"
echo "Sexto Programa teste"

sleep 1

echo -e "PLUGIN=plugin.so
SOURCES=\
        plugin.cc \
		\$(END)

include ../Makefile.common

.PHONY: test
test: \$(PLUGIN)
	\$(CCPLUGIN) -c -o /dev/null ./matrix/matrix.c" > Makefile

make clean
make
make test

echo "______________________"
echo "Sétimo Programa teste"

sleep 1

echo -e "PLUGIN=plugin.so
SOURCES=\
        plugin.cc \
		\$(END)

include ../Makefile.common

.PHONY: test
test: \$(PLUGIN)
	\$(CCPLUGIN) -c -o /dev/null ./neural/neural.c" > Makefile

make clean
make
make test

echo "______________________"
echo "Oitavo Programa teste"

sleep 1

echo -e "PLUGIN=plugin.so
SOURCES=\
        plugin.cc \
		\$(END)

include ../Makefile.common

.PHONY: test
test: \$(PLUGIN)
	\$(CCPLUGIN) -c -o /dev/null ./puzzle/puzzle.c" > Makefile

make clean
make
make test

echo "______________________"
echo "Nono Programa teste"

sleep 1

echo -e "PLUGIN=plugin.so
SOURCES=\
        plugin.cc \
		\$(END)

include ../Makefile.common

.PHONY: test
test: \$(PLUGIN)
	\$(CCPLUGIN) -c -o /dev/null ./queens/queens.c" > Makefile

make clean
make
make test

echo "______________________"
echo "Décimo Programa teste"

sleep 1

echo -e "PLUGIN=plugin.so
SOURCES=\
        plugin.cc \
		\$(END)

include ../Makefile.common

.PHONY: test
test: \$(PLUGIN)
	\$(CCPLUGIN) -c -o /dev/null ./uudecode/uudecode.c" > Makefile

make clean
make
make test