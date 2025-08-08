void sensor() {
  temperature_val = dht.readTemperature();
  humidity_val = dht.readHumidity();

  if(isnan(temperature_val)){temperature_val = 0;}
  if(isnan(humidity_val)){humidity_val = 0;}

  if(temperature_val > 100){temperature_val = 100;}
  if(humidity_val > 100){humidity_val = 100;}

  if(temperature_val != 0 && temperature_val != 100){
    temperature = temperature_val;
  }

  if(humidity_val != 0 && humidity_val != 100){
    humidity = humidity_val;
  }

  for(int i = 0; i <= 1; i++) {
    adc_plot[i] = analogRead(sens_sm[i]);
    sm_plot[i] = map(adc_plot[i], 0, 1320, 0, 100);

    if(sm_plot[i] <= 0)  { sm_plot[i] = 0; }
    if(sm_plot[i] >= 100){ sm_plot[i] = 100; }

  }

  // === Tambahan log ke Serial Monitor ===
  Serial.println("==== SENSOR LOG ====");
  Serial.print("Temperature (C): ");
  Serial.println(temperature);
  Serial.print("Humidity (%): ");
  Serial.println(humidity);
  Serial.print("Soil Moisture Plot 1 (%): ");
  Serial.println(sm_plot[0]);
  Serial.print("Soil Moisture Plot 2 (%): ");
  Serial.println(sm_plot[1]);
  Serial.println("====================");
  Serial.println();
}
