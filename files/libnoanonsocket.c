#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
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
		int len;
		struct rpc_connection	*conn;

		/*
		 * In nspluginwrapper-1.4.4 Linux binaries
		 * it looks USE_ANONYMOUS_SOCKETS is defined.
		 * In the anonymous socket case path[0] is '\0'
		 * and actual anon socket pathname is stored from path[1].
		 *
		 * See _rpc_socket_path() in nspluginwrapper-1.4.4/src/rpc.c
		 * for details.
		 */

		conn = (uint8_t *)my_addr - offsetof(struct rpc_connection, socket_addr);
		len = strlen(&conn->socket_path[1]) + 1;
		memmove(conn->socket_path, &conn->socket_path[1], len);
		len = strlen(&sun->sun_path[1]) + 1;
		memmove(sun->sun_path, &sun->sun_path[1], len);
	}
	return bindfunc(sockfd, my_addr, addrlen);
}
