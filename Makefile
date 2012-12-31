APP = pipin

include $(SDK_DIR)/Makefile.defs

OBJS = \
	$(ASSETS).gen.o \
	game.o \
	cube.o \
	main.o

ASSETDEPS += \
	assets/*.png \
	$(ASSETS).lua
CDEPS += *.h

include $(SDK_DIR)/Makefile.rules
