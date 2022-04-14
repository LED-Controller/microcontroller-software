String currentEffect = "null";

void activateEffect(String effectName) {
  currentEffect = effectName;
}

void disableEffect() {
  currentEffect = "null";
}

unsigned long lastEffectTimer = 0;

void effect_NormalParty() {
  if((millis() - lastEffectTimer) > 500) {
    lastEffectTimer = millis();
    updateColor(random(20, 240), random(20, 240), random(20, 240), random(20, 240));
    neoFill(random(20, 240), random(20, 240), random(20, 240));
  }
}


long firstPixelHue = 0;
unsigned long looping = 0;

void effect_Rainbow() {
  if((millis() - looping) > 5) {
    looping = millis();
  } else {
    return;
  }
  
  if(firstPixelHue < 5*65536) {
    firstPixelHue += 256;
  } else {
    firstPixelHue = 0;
  }
  
  for(int i = 0; i<strip.numPixels(); i++) {
    int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
    strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
  }
  
  strip.show();
}



void effectLoop() {
  if(currentEffect == "null") {
    return;
  }

  if(currentEffect == "NORMAL_PARTY") {
    effect_NormalParty();
  } else if(currentEffect == "RAINBOW") {
    effect_Rainbow();
  }
}
