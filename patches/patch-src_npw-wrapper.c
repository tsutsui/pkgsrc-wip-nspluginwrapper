--- src/npw-wrapper.c.orig	2012-11-14 16:01:37.000000000 +0100
+++ src/npw-wrapper.c	2012-11-14 16:00:38.000000000 +0100
--- src/npw-wrapper.c.orig	2011-07-01 03:18:57.000000000 +0000
+++ src/npw-wrapper.c
@@ -3867,6 +3867,32 @@ static void plugin_init(int is_NP_Initia
 					NPW_CONNECTION_PATH, plugin_file_name,
 					getpid(), init_count, random());
 
+#if !defined(__linux__)
+/* workaround USE_ANONYMOUS_SOCKETS on server-side linux binaries */
+  {
+	char *path;
+	int n, len;
+	char *tmpdir = "/tmp";
+
+	n = strlen(tmpdir);
+	len = strlen(connection_path);
+	if ((path = (char *)malloc(n + 1 + len + 1)) == NULL)
+	   return;
+
+	n = sprintf(path, "%s/", tmpdir);
+	for (int i = 0; i < len; i++) {
+	  char ch = connection_path[i];
+	  if (ch == '/')
+		ch = '_';
+	  path[n++] = ch;
+	}
+	path[n] = '\0';
+
+	free(connection_path);
+	connection_path = path;
+  }
+#endif
+
   // Start plug-in viewer
   if ((g_plugin.viewer_pid = fork()) == 0) {
 	char *argv[8];
