include $(ROOT)/rules.make

SRC = $(wildcard *.s *.c *.cpp)
OBJ = $(addsuffix .o,$(basename $(SRC)))

all: $(OBJ)
	@$(AR) cvq $(BUILD_DIR)/flibc.a $(OBJ)

clean:
	@rm -rf *.o

.PHONY: all
