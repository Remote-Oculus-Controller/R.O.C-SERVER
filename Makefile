##
## Makefile for  in /home/roussi_h/rendu/Epikong/etape_2
## 
## Made by ROUSSILLE
## Login   <roussi_h@epitech.net>
## 
## Started on  Wed Dec  3 11:23:09 2014 ROUSSILLE
## Last update Wed Dec 10 01:07:34 2014 ROUSSILLE
##
##

SRCSDIR = ./SRC/
INCSDIR = ./INC/


OBJSDIR = ./OBJ/


SRCS	= 	$(SRCSDIR)Main/main.cpp \
		$(SRCSDIR)Parser/YAMLParser.cpp \
		$(SRCSDIR)Network/Server.cpp \
		$(SRCSDIR)Network/TcpServer.cpp \
		$(SRCSDIR)RTSPFactory/RTSPFactory.cpp \
		$(SRCSDIR)Network/H264LiveServerMediaSession.cpp \
		$(SRCSDIR)Network/LiveSourceWithx264.cpp \
		$(SRCSDIR)Encoder/x264Encoder.cpp \
		$(SRCSDIR)Encoder/x265Encoder.cpp \
		$(SRCSDIR)Video/Camera.cpp \
		$(SRCSDIR)Processing/ImgProcessing.cpp \
		$(SRCSDIR)Processing/Canny.cpp \
		$(SRCSDIR)Processing/FaceDetect.cpp \
		$(SRCSDIR)Processing/RedCirclesDetect.cpp \
		$(SRCSDIR)Interpretor/Reader.cpp \
		$(SRCSDIR)Manager/Manager.cpp \

		

NAME = Server

OBJS = $(SRCS:$(SRCSDIR)%.cpp=$(OBJSDIR)%.o)

CPPFLAGS	=--std=c++0x  -O3  -I$(INCSDIR) -I/usr/locale/include/opencv -I/usr/locale/include/opencv2 -I /usr/local/include -I /usr/local/include/liveMedia -I /usr/local/include/BasicUsageEnvironment -I /usr/local/include/groupsock -I /usr/local/include/UsageEnvironment

LDLIBS		= -L/usr/local/lib/ -lm -lpthread -lx264 -lx265 -lswscale -lavutil -lopencv_objdetect -lopencv_features2d -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio -lopencv_core -lliveMedia -lgroupsock -lBasicUsageEnvironment -lUsageEnvironment

CXX = g++

RM = rm -f

all: $(NAME)


$(OBJSDIR)%.o:	$(SRCSDIR)%.cpp
		@echo "Compiling $<"
		@$(CXX) $(CFLAGS) -c $< -o $@ $(CPPFLAGS)

$(NAME): $(OBJS)
	@echo "Linking Server"
	@$(CXX) $(LDFLAGS) -o $(NAME) $(OBJS) $(LDLIBS)

clean :
	$(RM) $(OBJS)

fclean : clean 
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
