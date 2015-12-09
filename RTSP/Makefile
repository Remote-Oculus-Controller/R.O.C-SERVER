# project name (generate executable with this name)
TARGET   = rtsp-server

CC       = g++

# change these to set the proper directories where each files shoould be
SRCDIR   = sources
INCDIR	 = includes
OBJDIR   = objects
BINDIR   = bin

# compiling flags here
CFLAGS   = -I $(INCDIR) -I /usr/local/include/liveMedia -I /usr/local/include/groupsock/ -I /usr/local/include/UsageEnvironment  -I /usr/local/include/BasicUsageEnvironment/


LINKER   = g++ -o 

# linking flags here
LFLAGS   = -L /usr/local/lib -lBasicUsageEnvironment -lUsageEnvironment -lgroupsock  -lliveMedia 

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
rm       = rm -f


$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(OBJECTS) $(LFLAGS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONEY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONEY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
