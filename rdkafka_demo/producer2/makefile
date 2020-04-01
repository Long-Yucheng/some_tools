CUR_DIR := $(shell pwd)
SUB_DIR := src

MAKELIST = @for subdir in $(SUB_DIR); \
do \
cd $(CUR_DIR)/$$subdir && make; \
done

MAKECLEAN = @for subdir in $(SUB_DIR); \
do \
cd $(CUR_DIR)/$$subdir && make clean; \
done

all:
	$(MAKELIST)

clean:
	$(MAKECLEAN)