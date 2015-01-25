#include <sys/socket.h>
#include <sys/types.h>
#include <stddef.h>
#include <dlfcn.h>

struct osockaddr_un {
        uint16_t        sa_family;      /* address family */
        char            sun_path[108];    /* up to 108 bytes of direct address */
};

struct rpc_connection {
  int type;
  int refcnt;
  int status;
  int socket;
  char *socket_path;
  struct osockaddr_un socket_addr;
  socklen_t socket_addr_len;
  int server_socket;
  int server_thread_active;
};


int	(*bindfunc)(int, const struct sockaddr *, int) = NULL;

int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen)
{
	struct osockaddr_un	*sun;

	if (bindfunc == NULL) {
		bindfunc = dlsym(RTLD_NEXT,"bind");
		if (bindfunc == NULL)
			return -1;
	}
	sun = (struct osockaddr_un *) my_addr;
	if (sun != NULL && sun->sa_family == AF_LOCAL && sun->sun_path[0] == '\0') {
		char	*p, *q;
		struct rpc_connection	*conn;

		conn = (void *) my_addr - offsetof(struct rpc_connection, socket_addr);
		p = sun->sun_path;
		q = conn->socket_path;
		while (q[1]) {
			*q = q[1];
			*p = q[1];
			++q;
			++p;
		}
		*q = '\0';
		*p = '\0';
	}
	return bindfunc(sockfd, my_addr, addrlen);
}
