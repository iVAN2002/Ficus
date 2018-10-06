include $(ROOT)/rules.make

SRC = $(wildcard *.s *.c *.cpp)
OBJ = $(addsuffix .o,$(basename $(SRC)))

all: $(OBJ)
	@mkdir -p $(BUILD_DIR)/kernel
	$(CC) $(LDFLAGS) $(CRTBEGIN) $^ $(CRTEND) -o $(BUILD_DIR)/alice $(BUILD_DIR)/flibc.a

clean:
	@rm -rf *.o

.PHONY: all
