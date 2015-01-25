--- src/npw-wrapper.c.orig	2012-11-14 16:01:37.000000000 +0100
+++ src/npw-wrapper.c	2012-11-14 16:00:38.000000000 +0100
@@ -3863,9 +3863,15 @@
 	return;
 
   char *connection_path =
+#ifdef __linux__
 	g_strdup_printf("%s/%s/%d-%d/%ld",
 					NPW_CONNECTION_PATH, plugin_file_name,
 					getpid(), init_count, random());
+#else
+	g_strdup_printf("%s_%s_%d-%d_%ld",
+					NPW_CONNECTION_PATH, plugin_file_name,
+					getpid(), init_count, random());
+#endif
 
   // Start plug-in viewer
   if ((g_plugin.viewer_pid = fork()) == 0) {
