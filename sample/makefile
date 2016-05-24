SRCSDIR = ./SRC/
INCSDIR = ./INC/
OBJSDIR = ./OBJ/


SRCS	= 	$(SRCSDIR)RTSP_player.cpp


NAME = Client


OBJS = $(SRCS:$(SRCSDIR)%.cpp=$(OBJSDIR)%.o)

CPPFLAGS	= -std=c++14  -O3  -I$(INCSDIR) -I/usr/locale/include/opencv -I/usr/locale/include/opencv2 -I /usr/local/include -I /usr/local/include/liveMedia -I /usr/local/include/BasicUsageEnvironment -I /usr/local/include/groupsock -I /usr/local/include/UsageEnvironment
	
LDLIBS		= -L/usr/local/lib/ -lm -lpthread -lopencv_objdetect -lopencv_features2d -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio -lopencv_core -lliveMedia -lgroupsock -lBasicUsageEnvironment -lUsageEnvironment

CXX = g++

RM = rm -f

all: $(NAME)

$(OBJSDIR)%.o:	$(SRCSDIR)%.cpp
		@echo "Compiling $<"
		@$(CXX) $(CFLAGS) -c $< -o $@ $(CPPFLAGS)

$(NAME): $(OBJS)
		@echo "Linking Client"
		@$(CXX) $(LDFLAGS) -o $(NAME) $(OBJS) $(LDLIBS)

tree:
	mkdir -p OBJ

clean :
	$(RM) $(OBJS) $(OBJS_TEST)

fclean : clean
	$(RM) $(NAME) $(NAME_TEST)

re: fclean all

.PHONY: all clean fclean re
