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

Add the following line to your `/etc/pam.d/system-auth`:
```
auth       sufficient                  pam_wifi.so
```

Your final `/etc/pam.d/system-auth` might look like this:
```
-auth      [success=2 default=ignore]  pam_systemd_home.so
auth       sufficient                  pam_wifi.so
auth       [success=1 default=bad]     pam_unix.so          nullok
auth       [default=die]               pam_faillock.so      authfail
```

Set your desired SSID in `/etc/pam_wifi.conf`:
```sh
touch /etc/pam_wifi.conf
sudo echo "YOUR_SSID_HERE" > /etc/pam_wifi.conf
```

## Building
```sh
make build
```
