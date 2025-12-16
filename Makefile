map.test: CFLAGS := -DMAP_C_TEST
map.test:
	$(CC) $(CFLAGS) lib/map.c -o $@

.PHONY: clean
clean:
	rm -rf map.test

.PHONY: test
test: map.test
