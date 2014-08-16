#
#  Makefile
#  Andrews-Curtis Conjecture
#
#  Created by Kelly Davis on 8/27/11.
#
#

CXX = mpic++
CXXFLAGS = -O2 -march=native
LDFLAGS = -L/usr/local/lib/
LIBS = -lmpi \
       -lutil \
       -lopen-rte \
       -lopen-pal \
       -lboost_mpi-mt \
       -lboost_thread-mt \
       -lboost_system-mt \
       -lboost_date_time-mt \
       -lboost_serialization-mt

OBJS = main.o \
       relator.o \
       searcher.o \
       arguments.o \
       balanced_presentation_nursery.o

ac :  ${OBJS}
	${CXX} ${CXXFLAGS} -o $@  ${OBJS} ${LDFLAGS} ${LIBS}

clean:
	rm -fr *.o ac
