PROGNAME := App
SRCROOT := Src
LIBDIR := 
LIBS :=
OUTDIR := Build
TARGET := $(OUTDIR)/$(PROGNAME)
SRCDIRS := $(shell find $(SRCROOT) -type d)
SRCS = $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.cpp))
OBJS := $(addprefix $(OUTDIR)/,$(patsubst %.cpp,%.o,$(SRCS)))

CC = g++
CFLAGS = -Wall -std=c++11

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(OUTDIR)/%.o: %.cpp
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CC) $(CFLAGS) -o $@ -c $<

test: $(TARGET)
	./build/app

clean:
	rm -rf $(OUTDIR)