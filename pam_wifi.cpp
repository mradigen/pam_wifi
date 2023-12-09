#include <fstream>
#include <iostream>
#include <security/_pam_types.h>
#include <security/pam_appl.h>
#include <security/pam_modules.h>

using namespace std;

string get_connected_SSID() {
  FILE *fp = popen("iw dev wlan0 info | grep ssid | awk '{print $2}'", "r");
  if (fp == nullptr) {
    perror("popen");
    exit(1);
  }

  char line[100];
  string connectedSSID = "-1";

  if (fgets(line, sizeof(line), fp) != nullptr) {
    connectedSSID = line;
  }
  pclose(fp);

  connectedSSID.erase(connectedSSID.find_last_not_of("\n\r") + 1);
  return connectedSSID;
}

string get_config_SSID() {
  ifstream configFile("/etc/pam_wifi.conf");
  if (!configFile.is_open())
    return "";

  string line;
  getline(configFile, line);

  return line;
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc,
                                   const char **argv) {
  cout << "> Authenticating using connected WiFi" << endl;

  // Get SSID
  string config_SSID = get_config_SSID();
  string connected_SSID = get_connected_SSID();

  cout << "> Connected WiFi is: " + connected_SSID << endl;

  if (config_SSID == connected_SSID) {
    cout << "> Grant access? ";
    char confirmation = cin.get();
    if (confirmation == '\n' || confirmation == 'y') {
      cout << "> Access granted" << endl;
      return PAM_SUCCESS;
    }
  }
  cout << "! Access denied" << endl;
  return PAM_AUTH_ERR;
}
