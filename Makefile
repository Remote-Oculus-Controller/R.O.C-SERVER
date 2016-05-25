SRCSDIR = ./SRC/
INCSDIR = ./INC/
OBJSDIR = ./OBJ/


SRCS	= 	$(SRCSDIR)Main/main.cpp \
					$(SRCSDIR)Parser/YAMLParser.cpp \
					$(SRCSDIR)Parser/ConfigParser.cpp \
					$(SRCSDIR)Network/Server.cpp \
					$(SRCSDIR)Network/TcpServer.cpp \
					$(SRCSDIR)RTSPFactory/RTSPFactory.cpp \
					$(SRCSDIR)Network/H264LiveServerMediaSession.cpp \
					$(SRCSDIR)Network/LiveSourceWithx264.cpp \
					$(SRCSDIR)Encoder/x264Encoder.cpp \
					$(SRCSDIR)Video/Camera.cpp \
					$(SRCSDIR)Processing/ImgProcessing.cpp \
					$(SRCSDIR)Processing/CannyEdge.cpp \
					$(SRCSDIR)Processing/FaceDetect.cpp \
					$(SRCSDIR)Processing/RedCirclesDetect.cpp \
					$(SRCSDIR)Processing/Arrow.cpp \
					$(SRCSDIR)Processing/ImgProcessingWrapper.cpp \
					$(SRCSDIR)Interpretor/Reader.cpp \
					$(SRCSDIR)Manager/Manager.cpp \
					$(SRCSDIR)Manager/VideoManager.cpp \
					$(SRCSDIR)Singletons/VideoManagerSingleton.cpp \
					$(SRCSDIR)Singletons/ImgProcessingWrapperSingleton.cpp \
					$(SRCSDIR)Sync/LockList.cpp \
					$(SRCSDIR)Sync/Semaphore.cpp \
					$(SRCSDIR)Logger/Logger.cpp


SRCS_TEST = $(SRCSDIR)Test/main.cpp

NAME = Server

NAME_TEST = test

OBJS = $(SRCS:$(SRCSDIR)%.cpp=$(OBJSDIR)%.o)

OBJS_TEST = $(SRCS_TEST:$(SRCSDIR)%.cpp=$(OBJSDIR)%.o)

CPPFLAGS	= -std=c++1y  -O3  -I$(INCSDIR) -I/usr/locale/include/opencv -I/usr/locale/include/opencv2 -I /usr/local/include -I /usr/local/include/liveMedia -I /usr/local/include/BasicUsageEnvironment -I /usr/local/include/groupsock -I /usr/local/include/UsageEnvironment

LDLIBS		= -L/usr/local/lib/ -lm -lpthread -lx264 -lswscale -lavutil -lopencv_objdetect -lopencv_features2d -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio -lopencv_core -lliveMedia -lgroupsock -lBasicUsageEnvironment -lUsageEnvironment

LDLIBS_TEST = -lgtest

CXX = g++

RM = rm -f

all: $(NAME)

$(OBJSDIR)%.o:	$(SRCSDIR)%.cpp
		@echo "Compiling $<"
		@$(CXX) $(CFLAGS) -c $< -o $@ $(CPPFLAGS)

$(NAME): $(OBJS)
		@echo "Linking Server"
		@$(CXX) $(LDFLAGS) -o $(NAME) $(OBJS) $(LDLIBS)

test: $(OBJS_TEST)
	@echo "Linking Server (test mode) $<"
	@$(CXX) $(LDFLAGS) -o $(NAME_TEST) $(OBJS_TEST) $(LDLIBS) $(LDLIBS_TEST)

tree:
	mkdir -p OBJ
	mkdir -p OBJ/Compressor/
	mkdir -p OBJ/Encoder/
	mkdir -p OBJ/Interpretor/
	mkdir -p OBJ/Main/
	mkdir -p OBJ/Manager/
	mkdir -p OBJ/Network/
	mkdir -p OBJ/Parser/
	mkdir -p OBJ/Processing/
	mkdir -p OBJ/RTSPFactory/
	mkdir -p OBJ/Singletons/
	mkdir -p OBJ/Test/
	mkdir -p OBJ/Video/
	mkdir -p OBJ/Sync/
	mkdir -p OBJ/Logger/

clean :
	$(RM) $(OBJS) $(OBJS_TEST)

fclean : clean
	$(RM) $(NAME) $(NAME_TEST)

re: fclean all

.PHONY: all clean fclean re
