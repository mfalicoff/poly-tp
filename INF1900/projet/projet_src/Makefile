.PHONY: all base clean install

LIB_FOLDER=libstatic
SRC_FOLDER=execdir

all:
	$(MAKE) -C $(LIB_FOLDER)
	$(MAKE) -C $(SRC_FOLDER)


clean:
	$(MAKE) -C $(LIB_FOLDER) $@
	$(MAKE) -C $(SRC_FOLDER) $@