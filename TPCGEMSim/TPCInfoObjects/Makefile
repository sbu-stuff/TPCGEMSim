# change install destination if you don't have root priviliges
# e. g. to ${HOME}
INSTALLDIR = /usr/local
SHELL = /bin/bash

all:
	@(cd src; make)

clean:
	@(cd src; make clean)

distclean: clean
	rm lib/*

install:
	$(shell if [ ! -d $(INSTALLDIR)/lib ] ; then mkdir $(INSTALLDIR)/lib; fi)
	install -m 755 lib/* $(INSTALLDIR)/lib
	$(shell if [ ! -d $(INSTALLDIR)/include ] ; then mkdir $(INSTALLDIR)/include; fi)
	install -m 755 include/* $(INSTALLDIR)/include

docu:
	@(cd doc; doxygen TPCInfoObjects.dox)