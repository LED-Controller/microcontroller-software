String split(String data, int index) {
  char separator = ' ';
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  String result = found > index ? data.substring(strIndex[0], strIndex[1]) : "";
  result.trim();
  return result;
}

void handleData(String data) {
  if(data == "ping") {
    sendToServer("pong");
    lastPing = millis();
    return;
  } else if(data.startsWith("F1")) {
    // F1 {r} {g} {b}
    int rColor = split(data, 1).toInt();
    int gColor = split(data, 2).toInt();
    int bColor = split(data, 3).toInt();

    updateColor(rColor, gColor, bColor, 0);
    sendToServer("ok");
    return;
  } else if(data.startsWith("F2")) {
    // F1 {r} {g} {b} {w}
    int rColor = split(data, 1).toInt();
    int gColor = split(data, 2).toInt();
    int bColor = split(data, 3).toInt();
    int wColor = split(data, 4).toInt();

    updateColor(rColor, gColor, bColor, wColor);
    sendToServer("ok");
    return;
  } else if(data == "OFF") {
    updateColor(0, 0, 0, 0);
    neoFill(0, 0, 0);
    sendToServer("ok");
    return;
  } else if(data.startsWith("X1")) {
    int rColor = split(data, 1).toInt();
    int gColor = split(data, 2).toInt();
    int bColor = split(data, 3).toInt();
    neoFill(rColor, gColor, bColor);
    sendToServer("ok");
    return;
  }
  sendToServer("error");
}
