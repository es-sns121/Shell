top = .

src = $(top)/src

production_host: 
	$(MAKE) -C $(src)

.PHONY: clean
clean:
	$(MAKE) -C $(src) clean
