MODULE_big = conv_units

OBJS =  								\
	$(WIN32RES) 						\
	conv_units.o 						\
	instructions_store_dynamic.o 		\
	instructions_store_shared_mem.o 	\
	converter_functions.o 				\
	converter.o

EXTENSION = conv_units
REGRESS = conv_units

DATA = conv_units--1.0.sql

ifdef USE_PGXS
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
else
subdir = contrib/conv_units
top_builddir = ../..
include $(top_builddir)/src/Makefile.global
include $(top_srcdir)/contrib/contrib-global.mk
endif


