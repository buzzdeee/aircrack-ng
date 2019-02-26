# Aircrack-ng
#
# Copyright (C) 2017 Joseph Benden <joe@benden.us>
#
# Autotool support was written by: Joseph Benden <joe@benden.us>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
#
# In addition, as a special exception, the copyright holders give
# permission to link the code of portions of this program with the
# OpenSSL library under certain conditions as described in each
# individual source file, and distribute linked combinations
# including the two.
#
# You must obey the GNU General Public License in all respects
# for all of the code used other than OpenSSL.
#
# If you modify file(s) with this exception, you may extend this
# exception to your dnl version of the file(s), but you are not obligated
# to do so.
#
# If you dnl do not wish to do so, delete this exception statement from your
# version.
#
# If you delete this exception statement from all source files in the
# program, then also delete it here.

SRC_LINECOUNT	= %D%/linecount.cpp

SRC_PTW			= %D%/aircrack-ptw-lib.c

SRC_AC			= %D%/aircrack-ng.c
SRC_AC_ALL  	= %D%/aircrack-ng.c

SRC_AD			= %D%/airdecap-ng.c
SRC_PF			= %D%/packetforge-ng.c
SRC_AR			= %D%/aireplay-ng.c
SRC_ADU			= %D%/airodump-ng.c

SRC_AT			= %D%/airtun-ng.c
SRC_IV			= %D%/ivstools.c
SRC_AS			= %D%/airserv-ng.c
SRC_WS			= %D%/wesside-ng.c
SRC_BS			= %D%/besside-ng.c
SRC_BC			= %D%/besside-ng-crawler.c
SRC_AL			= %D%/airolib-ng.c

SRC_COW			= %D%/cowpatty.c

SRC_ES			= %D%/easside-ng.c
SRC_BUDDY		= %D%/buddy-ng.c
SRC_MI			= %D%/makeivs-ng.c
SRC_AB			= %D%/airbase-ng.c
SRC_AU			= %D%/airdecloak-ng.c
SRC_TT			= %D%/tkiptun-ng.c
SRC_WC			= %D%/wpaclean.c
SRC_AV			= %D%/airventriloquist-ng.c

SRC_ACLIB		= %D%/crypto.c $(SSEC_INT) %D%/uniqueiv.c %D%/session.c %D%/fragments.c %D%/communications.c %D%/dump_write.c

if LIBGCRYPT
SRC_AC			+= %D%/aircrack-crypto/sha1-git.c
SRC_AC_ALL 		+= %D%/aircrack-crypto/sha1-git.c
SRC_ACLIB 		+= %D%/aircrack-crypto/sha1-git.c
SRC_AD 			+= %D%/aircrack-crypto/sha1-git.c
SRC_PF 			+= %D%/aircrack-crypto/sha1-git.c
SRC_IV 			+= %D%/aircrack-crypto/sha1-git.c
SRC_AR 			+= %D%/aircrack-crypto/sha1-git.c
SRC_ADU 		+= %D%/aircrack-crypto/sha1-git.c
SRC_AT 			+= %D%/aircrack-crypto/sha1-git.c
SRC_AB 			+= %D%/aircrack-crypto/sha1-git.c
SRC_AL 			+= %D%/aircrack-crypto/sha1-git.c
SRC_WS 			+= %D%/aircrack-crypto/sha1-git.c
SRC_TT 			+= %D%/aircrack-crypto/sha1-git.c
SRC_BS 			+= %D%/aircrack-crypto/sha1-git.c
SRC_AV 			+= %D%/aircrack-crypto/sha1-git.c
endif

COMMON_CFLAGS = $(LIBAC_CFLAGS) $(PTHREAD_CFLAGS) $(CRYPTO_CFLAGS) $(ZLIB_CFLAGS)
COMMON_LDADD = $(PTHREAD_LIBS) $(CRYPTO_LIBS) $(ZLIB_LIBS)

bin_PROGRAMS += aircrack-ng \
                airdecap-ng \
                packetforge-ng \
                ivstools \
                kstats \
                makeivs-ng \
                airdecloak-ng

if EXPERIMENTAL
if HAVE_PCAP
bin_PROGRAMS += besside-ng-crawler
endif
endif

bin_PROGRAMS += wpaclean

sbin_PROGRAMS += airbase-ng \
                 aireplay-ng \
                 airodump-ng \
                 airserv-ng \
                 airtun-ng

if HAVE_SQLITE3
bin_PROGRAMS += airolib-ng
endif

if EXPERIMENTAL
bin_PROGRAMS += buddy-ng

sbin_PROGRAMS += airventriloquist-ng

if HAVE_AIRPCAP_OR_PCAP
sbin_PROGRAMS += besside-ng \
                 easside-ng \
                 tkiptun-ng \
                 wesside-ng
endif
endif

aircrack_ng_SOURCES = $(SRC_AC_ALL) $(SRC_LINECOUNT)
aircrack_ng_CFLAGS = $(COMMON_CFLAGS) $(SQLITE3_CFLAGS) $(LIBPTW_CFLAGS)
aircrack_ng_LDADD = $(LIBAIRCRACK_UTIL_LIBS) $(LIBAC_LIBS) $(SQLITE3_LDFLAGS) $(SQLITE3_LIBS) $(LIBPTW_LIBS) $(COMMON_LDADD) $(CRYPTO_LIBS) $(HWLOC_LIBS)

if STATIC_BUILD
aircrack_ng_CFLAGS += -DDYNAMIC=0
aircrack_ng_LDADD += $(LIBAIRCRACK_CRYPTO@SIMD_SUFFIX@_LIBS)
else
aircrack_ng_LDFLAGS = -rdynamic
endif

airdecap_ng_SOURCES = $(SRC_AD)
airdecap_ng_CFLAGS = $(COMMON_CFLAGS)
airdecap_ng_LDADD = $(COMMON_LDADD) $(LIBAC_LIBS) $(LIBAIRCRACK_UTIL_LIBS) $(CRYPTO_LIBS)

packetforge_ng_SOURCES = $(SRC_PF)
packetforge_ng_CFLAGS = $(COMMON_CFLAGS) $(LIBNL_CFLAGS)
packetforge_ng_LDADD = $(COMMON_LDADD) $(LIBAC_LIBS) $(LIBAIRCRACK_OSDEP_LIBS) $(LIBAIRCRACK_UTIL_LIBS) $(CRYPTO_LIBS)

aireplay_ng_SOURCES = $(SRC_AR)
aireplay_ng_CFLAGS = $(COMMON_CFLAGS) $(LIBNL_CFLAGS)
aireplay_ng_LDADD = $(COMMON_LDADD) $(LIBAIRCRACK_OSDEP_LIBS) $(LIBAC_LIBS) $(AIRPCAP_LIBS) $(LIBAIRCRACK_UTIL_LIBS) $(CRYPTO_LIBS)

airodump_ng_SOURCES = $(SRC_ADU) $(LIBMCS)
airodump_ng_CFLAGS = $(COMMON_CFLAGS) $(PCRE_CFLAGS) $(LIBNL_CFLAGS)
airodump_ng_LDADD = $(COMMON_LDADD) $(PCRE_LIBS) $(LIBAIRCRACK_OSDEP_LIBS) $(LIBAC_LIBS) $(AIRPCAP_LIBS) $(LIBAIRCRACK_UTIL_LIBS) $(CRYPTO_LIBS)

airserv_ng_SOURCES = $(SRC_AS)
airserv_ng_CFLAGS = $(COMMON_CFLAGS) $(LIBNL_CFLAGS)
airserv_ng_LDADD = $(COMMON_LDADD) $(LIBAIRCRACK_OSDEP_LIBS) $(LIBAC_LIBS) $(AIRPCAP_LIBS) $(LIBAIRCRACK_UTIL_LIBS) $(CRYPTO_LIBS)

airtun_ng_SOURCES = $(SRC_AT)
airtun_ng_CFLAGS = $(COMMON_CFLAGS) $(LIBNL_CFLAGS)
airtun_ng_LDADD = $(COMMON_LDADD) $(LIBAIRCRACK_OSDEP_LIBS) $(LIBAC_LIBS) $(AIRPCAP_LIBS) $(LIBAIRCRACK_UTIL_LIBS) $(CRYPTO_LIBS)

ivstools_SOURCES = $(SRC_IV)
ivstools_CFLAGS = $(COMMON_CFLAGS)
ivstools_LDADD = $(COMMON_LDADD) $(LIBAC_LIBS) $(LIBAIRCRACK_UTIL_LIBS) $(CRYPTO_LIBS)

kstats_SOURCES = %D%/kstats.c
kstats_CFLAGS = $(LIBAC_CFLAGS) $(PTHREAD_CFLAGS)
kstats_LDADD = $(COMMON_LDADD) $(LIBAC_LIBS)

wesside_ng_SOURCES = $(SRC_WS)
wesside_ng_CFLAGS = $(COMMON_CFLAGS) $(LIBNL_CFLAGS)
wesside_ng_LDADD = $(COMMON_LDADD) $(LIBAIRCRACK_OSDEP_LIBS) $(LIBAC_LIBS) $(LIBPTW_LIBS) $(AIRPCAP_LIBS) $(LIBAIRCRACK_UTIL_LIBS) $(CRYPTO_LIBS)

easside_ng_SOURCES = $(SRC_ES)
easside_ng_CFLAGS = $(COMMON_CFLAGS) $(LIBNL_CFLAGS)
easside_ng_LDADD = $(COMMON_LDADD) $(LIBAIRCRACK_OSDEP_LIBS) $(LIBAC_LIBS) $(AIRPCAP_LIBS) $(LIBAIRCRACK_UTIL_LIBS) $(CRYPTO_LIBS)

buddy_ng_SOURCES = $(SRC_BUDDY)
buddy_ng_CFLAGS = $(LIBAC_CFLAGS) $(PTHREAD_CFLAGS)
buddy_ng_LDADD = $(COMMON_LDADD) $(LIBAC_LIBS) $(LIBAIRCRACK_UTIL_LIBS) $(CRYPTO_LIBS)

besside_ng_SOURCES = $(SRC_BS)
besside_ng_CFLAGS = $(COMMON_CFLAGS) $(PCRE_CFLAGS) $(LIBNL_CFLAGS)
besside_ng_LDADD = $(COMMON_LDADD) $(PCRE_LIBS) $(LIBAIRCRACK_OSDEP_LIBS) $(LIBAC_LIBS) $(LIBPTW_LIBS) $(AIRPCAP_LIBS) $(LIBAIRCRACK_UTIL_LIBS) $(CRYPTO_LIBS)

besside_ng_crawler_SOURCES = $(SRC_BC)
besside_ng_crawler_CFLAGS = $(COMMON_CFLAGS) $(PCAP_CFLAGS)
besside_ng_crawler_LDADD = $(COMMON_LDADD) $(PCAP_LIBS) $(LIBAC_LIBS) $(CRYPTO_LIBS)

makeivs_ng_SOURCES = $(SRC_MI)
makeivs_ng_CFLAGS = $(COMMON_CFLAGS)
makeivs_ng_LDADD = $(COMMON_LDADD) $(LIBAC_LIBS) $(LIBAIRCRACK_UTIL_LIBS) $(CRYPTO_LIBS)

airolib_ng_SOURCES = $(SRC_AL) $(LIBCOW)
airolib_ng_CFLAGS = $(COMMON_CFLAGS) $(SQLITE3_CFLAGS) -DHAVE_REGEXP
airolib_ng_LDADD = $(COMMON_LDADD) $(SQLITE3_LDFLAGS) $(SQLITE3_LIBS) $(LIBAC_LIBS) $(LIBCOW_LIBS) $(LIBAIRCRACK_UTIL_LIBS) $(CRYPTO_LIBS)

airbase_ng_SOURCES = $(SRC_AB)
airbase_ng_CFLAGS = $(COMMON_CFLAGS) $(LIBNL_CFLAGS)
airbase_ng_LDADD = $(COMMON_LDADD) $(LIBAIRCRACK_OSDEP_LIBS) $(LIBAC_LIBS) $(AIRPCAP_LIBS) $(LIBAIRCRACK_UTIL_LIBS) $(CRYPTO_LIBS)

airdecloak_ng_SOURCES = $(SRC_AU)
airdecloak_ng_CFLAGS = $(COMMON_CFLAGS)
airdecloak_ng_LDADD = $(COMMON_LDADD) $(LIBAIRCRACK_OSDEP_LIBS) $(LIBAC_LIBS) $(AIRPCAP_LIBS) $(LIBAIRCRACK_UTIL_LIBS) $(CRYPTO_LIBS)

tkiptun_ng_SOURCES = $(SRC_TT)
tkiptun_ng_CFLAGS = $(COMMON_CFLAGS) $(LIBNL_CFLAGS)
tkiptun_ng_LDADD = $(COMMON_LDADD) $(LIBAIRCRACK_OSDEP_LIBS) $(LIBAC_LIBS) $(AIRPCAP_LIBS) $(LIBAIRCRACK_UTIL_LIBS) $(CRYPTO_LIBS)

wpaclean_SOURCES = $(SRC_WC)
wpaclean_CFLAGS = $(COMMON_CFLAGS) $(LIBNL_CFLAGS) $(LIBAIRCRACK_UTIL_CFLAGS)
wpaclean_LDADD = $(COMMON_LDADD) $(LIBAIRCRACK_OSDEP_LIBS) $(LIBAC_LIBS) $(AIRPCAP_LIBS) $(LIBAIRCRACK_UTIL_LIBS) $(CRYPTO_LIBS)

airventriloquist_ng_SOURCES = $(SRC_AV)
airventriloquist_ng_CFLAGS = $(COMMON_CFLAGS) $(LIBNL_CFLAGS)
airventriloquist_ng_LDADD = $(COMMON_LDADD) $(LIBAIRCRACK_OSDEP_LIBS) $(LIBAC_LIBS) $(AIRPCAP_LIBS) $(LIBAIRCRACK_UTIL_LIBS) $(CRYPTO_LIBS)

libaclib_la_SOURCES = $(SRC_ACLIB)
libaclib_la_CFLAGS = $(COMMON_CFLAGS) $(PCRE_CFLAGS) $(LIBAIRCRACK_UTIL_CFLAGS)
libaclib_la_LIBADD = $(PCRE_LIBS) $(LIBAIRCRACK_OSDEP_LIBS) $(LIBAIRCRACK_UTIL_LIBS) $(CRYPTO_LIBS)
if !STATIC_CRYPTO
libaclib_la_LIBADD += $(LIBAIRCRACK_UTIL_LIBS)
endif

libcow_la_SOURCES = $(SRC_COW)
libcow_la_CFLAGS = $(COMMON_CFLAGS) $(LIBCOW_CFLAGS)
if !STATIC_CRYPTO
libcow_la_LIBADD = $(COMMON_LDADD)
endif

libptw_la_SOURCES = $(SRC_PTW)
libptw_la_CFLAGS = $(COMMON_CFLAGS)
if !STATIC_CRYPTO
libptw_la_LIBADD = $(COMMON_LDADD)
endif

noinst_LTLIBRARIES += libaclib.la libptw.la libcow.la

EXTRA_DIST +=	%D%/wpaclean.c \
				%D%/buddy-ng.c \
				%D%/aircrack-ng.h \
				%D%/version.h \
				%D%/airventriloquist-ng.h \
				%D%/airdecloak-ng.h \
				%D%/airserv-ng.c \
				%D%/besside-ng.c \
				%D%/wkp-frame.h \
				%D%/airolib-ng.c \
				%D%/aircrack-ptw-lib.h \
				%D%/makeivs-ng.c \
				%D%/easside-ng.c \
				%D%/crctable.h \
				%D%/airdecap-ng.c \
				%D%/airodump-ng.h \
				%D%/airbase-ng.c \
				%D%/besside-ng-crawler.c \
				%D%/tkiptun-ng.c \
				%D%/kstats.c \
				%D%/easside.h \
				%D%/aireplay-ng.c \
				%D%/ivstools.c \
				%D%/pcap_local.h \
				%D%/aircrack-ng.c \
				%D%/airodump-ng.c \
				%D%/crypto.c \
				%D%/airdecloak-ng.c \
				%D%/packetforge-ng.c \
				%D%/airventriloquist-ng.c \
				%D%/uniqueiv.c \
				%D%/gcrypt-openssl-wrapper.h \
				%D%/uniqueiv.h \
				%D%/wesside-ng.c \
				%D%/airtun-ng.c \
				%D%/linecount.h \
				%D%/aircrack-ptw-lib.c \
				%D%/crypto.h \
				%D%/cowpatty.c \
				%D%/cowpatty.h \
				%D%/session.c \
				%D%/session.h \
				%D%/defs.h \
				%D%/dump_write.h \
				%D%/dump_write.c \
				%D%/fragments.h \
				%D%/fragments.c \
				%D%/communications.h \
				%D%/communications.c \
				%D%/station.h

include %D%/include/Makefile.inc
include %D%/aircrack-util/Makefile.inc
include %D%/aircrack-osdep/Makefile.inc
include %D%/aircrack-crypto/Makefile.inc