## automake.am
##
## Automake.am for rivendell/utils/rdclilogedit
##
##   (C) Copyright 2016 Fred Gleason <fredg@paravelsystems.com>
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

AM_CPPFLAGS = -Wall -DPREFIX=\"$(prefix)\" -I$(top_srcdir)/lib @QT4_CFLAGS@ -DQT3_SUPPORT -I/usr/include/Qt3Support
LIBS = -L$(top_srcdir)/lib
MOC = @QT_MOC@

# The dependency for qt's Meta Object Compiler (moc)
moc_%.cpp:	%.h
	$(MOC) $< -o $@

bin_PROGRAMS = rdclilogedit

dist_rdclilogedit_SOURCES = help.cpp\
                            operations.cpp\
                            parser.cpp\
                            rdclilogedit.cpp rdclilogedit.h

nodist_rdclilogedit_SOURCES = moc_rdclilogedit.cpp

rdclilogedit_LDADD = @LIB_RDLIBS@ @LIBVORBIS@ @QT4_LIBS@ -lQt3Support

CLEANFILES = *~\
             *.idb\
             *ilk\
             *.obj\
             *.pdb\
             *.qm\
             moc_*

MAINTAINERCLEANFILES = *~\
                       Makefile.in\
                       moc_*
