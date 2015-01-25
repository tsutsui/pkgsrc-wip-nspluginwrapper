$NetBSD$

Adapt for glib-2.32.

--- src/npw-player.c.orig	2009-01-02 08:54:10.000000000 +0000
+++ src/npw-player.c
@@ -24,8 +24,6 @@
 #include <dlfcn.h>
 #include <unistd.h>
 #include <glib.h>
-#include <glib/gstdio.h>
-#include <glib/gthread.h>
 #include <gtk/gtk.h>
 #include <gdk/gdkx.h>
 #include <gdk/gdkkeysyms.h>
