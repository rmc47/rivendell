## automake.am
##
## docs/automake.am for Rivendell
##
## (C) Copyright 2002-2016 Fred Gleason <fredg@paravelsystems.com>
##
##   This program is free software; you can redistribute it and/or modify
##   it under the terms of the GNU General Public License version 2 as
##   published by the Free Software Foundation.
##
##   This program is distributed in the hope that it will be useful,
##   but WITHOUT ANY WARRANTY; without even the implied warranty of
##   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##   GNU General Public License for more details.
##
##   You should have received a copy of the GNU General Public
##   License along with this program; if not, write to the Free Software
##   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
##
## Use automake to process this into a Makefile.in

if DOCBOOK_AM
  DOCBOOK_AM_OPT = docbook
endif

SUBDIRS = $(DOCBOOK_AM_OPT) examples\
          tables

EXTRA_DIST = ALSA.txt\
             ando_interface.odt\
             asound.conf-sample\
             catchd.txt\
             colors\
             copy_split_format.odt\
             datetime_wildcards.txt\
             implemented_macros.txt\
             ENCODERS.txt\
             GPIO.txt\
             JACK.txt\
             MESSAGE_BOX.txt\
             metadata_wildcards.txt\
             NEXGEN_FILTER.txt\
             NOW+NEXT.txt\
             PODCASTING.txt\
             RDMONITOR.txt\
             reports.txt\
             ripc.txt\
             RIVENDELL_FILTER.txt\
             SAGE_ENDEC.txt\
             scheduler_formats.ods\
             SWITCHERS.txt\
             WIN32.txt\
	     WINGS_FILTER.txt


CLEANFILES = *~
MAINTAINERCLEANFILES = *~\
                       aclocal.m4\
                       configure\
                       Makefile.in
