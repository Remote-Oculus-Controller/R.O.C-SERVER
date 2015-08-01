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
		$(SRCSDIR)Network/Server.cpp \
		$(SRCSDIR)Network/UdpServer.cpp \
		$(SRCSDIR)Network/TcpServer.cpp \
		$(SRCSDIR)Video/Camera.cpp \
		$(SRCSDIR)Video/CameraV4l2.cpp \
		$(SRCSDIR)Video/v4l2uvc.cpp \


NAME = Server

OBJS = $(SRCS:$(SRCSDIR)%.cpp=$(OBJSDIR)%.o)

CPPFLAGS	=--std=c++0x  -O3  -I$(INCSDIR) -I/usr/locale/include/opencv -I/usr/locale/include/opencv2

LDLIBS		=-L/usr/local/lib/ -lpthread -lopencv_objdetect -lopencv_features2d -lopencv_imgproc -lopencv_imgcodecs -lopencv_highgui -lopencv_videoio -lopencv_core

CXX = g++

RM = rm -f

all: $(NAME)


$(OBJSDIR)%.o: 	 $(SRCSDIR)%.cpp
				 $(CXX) -c -o $@ $< $(CPPFLAGS)

$(NAME): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(NAME) $(OBJS) $(LDLIBS)

clean :
	$(RM) $(OBJS)

fclean : clean 
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
