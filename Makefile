uuid_rain:
	gcc uuid_rain.c -luuid -o uuid_rain

clean:
	rm uuid_rain

install:
	mkdir -p $(DESTDIR)/usr/bin
	install -m 0755 uuid_rain $(DESTDIR)/usr/bin/uuid_rain
