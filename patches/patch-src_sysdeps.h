--- src/sysdeps.h.orig	2012-11-14 15:58:12.000000000 +0100
+++ src/sysdeps.h	2012-11-14 15:58:23.000000000 +0100
@@ -40,7 +40,11 @@
 #include <limits.h>
 
 // NSPluginWrapper paths and identification strings
+#ifdef __linux__
 #define NPW_CONNECTION_PATH "/org/wrapper/NSPlugins"
+#else
+#define NPW_CONNECTION_PATH "/tmp/_org_wrapper_NSPlugins"
+#endif
 #define NPW_VIEWER_BASE "npviewer"
 #define NPW_VIEWER NPW_VIEWER_BASE
 #define NPW_WRAPPER_BASE "npwrapper"
