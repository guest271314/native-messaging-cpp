// C++ Native Messaging host
// https://browserext.github.io/native-messaging/
// https://developer.chrome.com/docs/apps/nativeMessaging/
// https://discourse.mozilla.org/t/webextension-with-native-messaging-c-app-side/30821
#include <iostream>
using namespace std;

void sendMessage(string message) {
  string data = message.data();
  uint32_t size = uint32_t(message.size());
  char *length = reinterpret_cast<char *>(&size);
  fwrite(length, 4, sizeof(char), stdout);
  fwrite(message.c_str(), message.length(), sizeof(char), stdout);
  fflush(stdout);
}

string getMessage() {
  char length[4];
  fread(length, 4, sizeof(char), stdin);
  uint32_t len = *reinterpret_cast<uint32_t *>(length);
  // Uncomment to exit when message length is 0.
  // if (!len) { exit(EXIT_SUCCESS); }
  char message[len];
  fread(message, len, sizeof(char), stdin);
  string content(message, message + sizeof(message) / sizeof(message[0]));
  return content;
}

int main(int argc, char *argv[]) {
  while (true) {
    string message = getMessage();
    sendMessage(message);
    // Build JSON array
    /*
    string data = "[";
    // Remove double quotation marks from beginning, end of string.
    // .substr(1, message.length() - 2);
    data += message; 
    data += ", ";
    for(int i = 0; i < argc; i++) {
      string arg = string(argv[i]);
      data += "\"";
      data += arg;
      data += "\"";
      if (i < argc -1) {
        data += ", ";
      }
    }
    data += "]";
    sendMessage(data);
    */
  }
  return 0;
}
