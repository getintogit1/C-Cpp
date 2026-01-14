CFLAGS = -O3 -MMD -MP -Wall

PROGRAMS = programm
OBJECTS = endprodukt.o teil.o schritt.o main.o

ALLOBJECTS = $(OBJECTS) $(OBJECTS:%.o=%.d)

default: $(PROGRAMS)

$(PROGRAMS): $(OBJECTS)
	$(CXX) -o $@ $^

clean:
	-rm -f $(ALLOBJECTS) $(PROGRAMS)

-include $(OBJECTS:%.o=%.d)
