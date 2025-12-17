map.test: CFLAGS := -std=c99 -Wall -Wextra -Werror -pedantic -DMAP_C_TEST
map.test:
	$(CC) $(CFLAGS) lib/map.c -o $@

set.test: CFLAGS := -std=c99 -Wall -Wextra -Werror -pedantic -DSET_C_TEST
set.test:
	$(CC) $(CFLAGS) lib/set.c -o $@

.PHONY: docs
docs:
	for file in lib/*.h lib/Makefile; do \
		python3 scripts/docs.py $$file; \
	done
	scripts/index.sh

.PHONY: clean
clean:
	rm -rf map.test set.test *.dSYM

.PHONY: test
test: map.test set.test
	./map.test
	./set.test
