String split(String s, int index) {
  char parser = ' ';
  String rs="";
  int parserIndex = index;
  int parserCnt=0;
  int rFromIndex=0, rToIndex=-1;
  while (index >= parserCnt) {
    rFromIndex = rToIndex+1;
    rToIndex = s.indexOf(parser,rFromIndex);
    if (index == parserCnt) {
      if (rToIndex == 0 || rToIndex == -1) return "";
      return s.substring(rFromIndex,rToIndex);
    } else parserCnt++;
  }
  return rs;
}

void handleData(String data) {
  if(data == "ping") {
    sendToServer("pong");
    lastPing = millis();
  } else if(data.startsWith("F1")) {
    // F1 {r} {g} {b}
    int rColor = split(data, 1).toInt();
    int gColor = split(data, 2).toInt();
    int bColor = split(data, 3).toInt();

    updateColor(rColor, gColor, bColor, 0);
    sendToServer("ok");
  } else if(data.startsWith("F2")) {
    // F1 {r} {g} {b} {w}
    int rColor = split(data, 1).toInt();
    int gColor = split(data, 2).toInt();
    int bColor = split(data, 3).toInt();
    int wColor = split(data, 4).toInt();

    updateColor(rColor, gColor, bColor, wColor);
    sendToServer("ok");
  } else if(data == "OFF") {
    updateColor(0, 0, 0, 0);
    sendToServer("ok");
  } else if(data.startsWith("X1")) {
    Serial.println("neopixel not supported yet");
    sendToServer("nsy");
  }
  sendToServer("error");
}
