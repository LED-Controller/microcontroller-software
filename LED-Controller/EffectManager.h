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

void effectLoop() {
  if(currentEffect == "null") {
    return;
  }

  if(currentEffect == "NORMAL_PARTY") {
    effect_NormalParty();
  }
}
