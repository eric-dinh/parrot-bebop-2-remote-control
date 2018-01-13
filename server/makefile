IDIR = out/Unix-base/staging/usr/include
CC = gcc
CFLAGS=-I$(IDIR)

LIBS = -larsal -larcommands -larcontroller -lardatatransfer -lardiscovery -larmavlink \
	   -larmedia -larnetwork -larnetworkal -larstream -larstream2 -larupdater -larutils \
	   -lcurl -ljson -lssl -lcrypto -ltls -lmux -lpomp

_DEPS = commands.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = commands.o server.o 



$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

server: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) -Lout/Unix-base/staging/usr/lib $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
