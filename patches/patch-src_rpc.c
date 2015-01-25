$NetBSD$

The Linux nspluginwrapper-1.4.4 binaries seems built USE_ANONYMOUS_SOCKETS
enabled. In that case we have to handle socket path rename for plugin side
in npw_wrappwer.c and libnoanonsocket.so wrapper library.

--- src/rpc.c.orig	2012-11-14 16:01:37.000000000 +0100
+++ src/rpc.c
@@ -609,16 +609,7 @@
 #if USE_ANONYMOUS_SOCKETS
   n = 0;
 #else
-#if 0
-  char *tmpdir = getenv("TMPDIR");
-  if (tmpdir == NULL)
-	tmpdir = "/tmp";
-#else
-  // XXX don't use TMPDIR because the length of the resulting path
-  // could exceed the size of sun_path[] (typically 108 bytes on Linux)
-  char *tmpdir = "/tmp";
-#endif
-  n = strlen(tmpdir);
+  n = -1;
 #endif
 
   len = strlen(ident);
@@ -630,14 +621,8 @@
   strcpy(&path[1], ident);
   n = 1 + len;
 #else
-  n = sprintf(path, "%s/", tmpdir);
-  for (int i = 0; i < len; i++) {
-    char ch = ident[i];
-    if (ch == '/')
-      ch = '_';
-    path[n++] = ch;
-  }
-  path[n] = '\0';
+  strcpy(path, ident);
+  n = len;
 #endif
 
   if (*pathp)
