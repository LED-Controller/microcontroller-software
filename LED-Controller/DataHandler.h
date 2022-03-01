

void handleData(String data) {
  if(data == "ping") {
    client.println("pong");
    lastPing = millis();
  } else if(data == "random") {
    randomColor();
  }
}
