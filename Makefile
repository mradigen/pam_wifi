build:
	g++ -shared -o pam_wifi.so pam_wifi.cpp -lpam -fPIC

install: build
	rm /lib/security/pam_wifi.so; true
	cp pam_wifi.so /lib/security
