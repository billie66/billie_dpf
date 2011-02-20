# 2010.2.22

#DIR = ./out/
#TAR_DIR = ./out/

src = $(wildcard *.c)
obj = $(patsubst %.c, $(DIR)%.o, $(src))
target =	main 

CC =	gcc
CFLAGS =	-Wall -g -c 
LDFLAGS	=	-Wall -g  -ljpeg 
LDFLAGS +=	-lfreetype 

all: $(target)

$(target): $(obj)
	$(CC) -o $@ $^ $(LDFLAGS)

$(DIR)%.o:%.c
	$(CC) -o $@ $(CFLAGS) $< 

clean:
	-rm -f $(target)
	-rm -f $(obj)
	-rm -f *~

.PHONY: clean
test:
	@echo $(src)
	@echo $(obj)
