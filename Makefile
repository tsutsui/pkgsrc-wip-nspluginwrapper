# $NetBSD: Makefile,v 1.34 2012/10/28 06:30:24 asau Exp $
#

DISTNAME=	nspluginwrapper-1.4.4
CATEGORIES=	www
MASTER_SITES=	http://nspluginwrapper.org/download/ \
		http://download.opensuse.org/distribution/12.1/repo/oss/suse/x86_64/
DISTFILES=	${DISTNAME}.tar.gz ${DISTNAME}-2.2.1.x86_64.rpm

MAINTAINER=	abs@NetBSD.org
HOMEPAGE=	http://nspluginwrapper.org/
COMMENT=	Use Netscape compatible plugins from other platforms
LICENSE=	gnu-gpl-v2

EMUL_PLATFORMS=		linux-i386
EMUL_MODULES.linux=	base gtk2 x11
NOT_FOR_PLATFORM=	Linux-*-*

HAS_CONFIGURE=		yes
USE_LANGUAGES=		c c++
USE_TOOLS+=		gmake pkg-config
CONFIGURE_ARGS+=	--prefix=${PREFIX}

PLUGIN_SUBDIR=		lib/nspluginwrapper/i386/linux
PLUGIN_INSTDIR=		${PREFIX}/${PLUGIN_SUBDIR}
PLUGIN_SRCDIR=		${WRKDIR}/usr/${PLUGIN_SUBDIR}

LDFLAGS.DragonFly=	-lgmodule-2.0

SUBST_CLASSES+=		npw-config
SUBST_STAGE.npw-config=	post-patch
SUBST_FILES.npw-config=	src/npw-config.c
SUBST_SED.npw-config=	-e "s|/usr/pkg/|${PREFIX}/|g"

SUBST_CLASSES+=		npviewer
SUBST_STAGE.npviewer=	post-build
SUBST_FILES.npviewer=	${PLUGIN_SRCDIR}/npviewer
SUBST_SED.npviewer=	-e "s|/usr/|${PREFIX}/|g"

INSTALLATION_DIRS=	${PLUGIN_INSTDIR}

post-extract:
	cp files/libnoanonsocket.c ${WRKDIR}/${DISTNAME}/src

post-install:
	${INSTALL_LIB} ${PLUGIN_SRCDIR}/libnoxshm.so ${DESTDIR}${PLUGIN_INSTDIR}
	${INSTALL_LIB} ${WRKDIR}/${DISTNAME}/libnoanonsocket.so ${DESTDIR}${PLUGIN_INSTDIR}
	${INSTALL_SCRIPT} ${PLUGIN_SRCDIR}/npviewer ${DESTDIR}${PLUGIN_INSTDIR}
	${INSTALL_LIB} ${PLUGIN_SRCDIR}/npviewer.bin ${DESTDIR}${PLUGIN_INSTDIR}

.include "../../devel/glib2/buildlink3.mk"
.include "../../www/curl/buildlink3.mk"
.include "../../x11/gtk2/buildlink3.mk"
.include "../../x11/libX11/buildlink3.mk"
.include "../../x11/libXt/buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
