# pam_wifi

This PAM module authorizes the user given the system is connected to a set SSID. This SSID can be set in `/etc/pam_wifi.conf`.

## Disclaimer:
Just in case you don't already know why not to use this, anyone can rename their access point to be the same as the set SSID to authenticate against. (given the attacker knows the SSID you are authenticating against)

The code is really bad, credits to my C proficiency.

This was made for educational purposes and I might refine it in the future.

## Building
```sh
make build
```

## Installing
```sh
sudo make install
```

## Usage

Add the following line to your `/etc/pam.d/sudo`:
```
auth       sufficient                  pam_wifi.so
```

Your final `/etc/pam.d/sudo` might look like this:
```
auth		sufficient	pam_wifi.so
auth		include		system-auth
account		include		system-auth
session		include		system-auth
```

Set your desired SSID in `/etc/pam_wifi.conf`:
```sh
echo "YOUR_SSID_HERE" | sudo tee /etc/pam_wifi.conf
```
