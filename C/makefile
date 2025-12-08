CFLAGS = -O3 -MMD -MP -Wall

PROGRAMS = programm
OBJECTS = endprodukt.o teil.o schritt.o utils.o main.o cache.o

ALLOBJECTS = $(OBJECTS) $(OBJECTS:%.o=%.d)

default: $(PROGRAMS)

$(PROGRAMS): $(OBJECTS)
	$(CC) -o $@ $^

clean:
	-rm -f $(ALLOBJECTS) $(PROGRAMS)

-include $(OBJECTS:%.o=%.d)
