CLIENT = client
SERVER = server

CLIENTSRC = client.c
SERVERSRC = server.c

CLIENTOBJS := ${CLEINTSRCS:.c=.o}
SERVEROBJS := ${SERVERSRCS:.c=.o}

CLIENTHEADER = client.h
SERVERHEADER = server.h

FLAGS = -Wall -Wextra -Werror

all:	$(CLIENT) $(SERVER)

$(CLIENT):	$(CLIENTOBJS)
	cc $(FLAGS) -o $(CLIENT) $(CLIENTOBJS)

$(SERVER):	$(SERVEROBJS)
	cc $(FLAGS) -o $(SERVER) $(SERVEROBJS)

$(CLIENTOBJS):	$(CLIENTSRCS)
	cc -c $(FLAGS) $(CLIENTSRCS)

$(SERVEROBJS):	$(SERVERSRCS)
	cc -c $(FLAGS) $(SERVERSRCS)

clean:
	rm -f $(CLIENTOBJS) $(SERVEROBJS)

fclean:	clean
	rm -f $(CLIENT) $(SERVER)

re:	fclean all