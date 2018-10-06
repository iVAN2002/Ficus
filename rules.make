%.s.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
    
%.o: %.cpp
	$(CXX) $(CFLAGS) $< -o $@
