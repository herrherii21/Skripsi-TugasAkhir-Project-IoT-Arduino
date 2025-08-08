void settings_plot1(){
  if(Firebase.getJSON(fbdo, "settings/plot1")) {
    data_settings_p1 = fbdo.jsonString();
    //Serial.println(data_json);

    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, data_settings_p1);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }

    day1[0] = doc["day1"];
    day2[0] = doc["day2"];
    day3[0] = doc["day3"];
    day4[0] = doc["day4"];
    day5[0] = doc["day5"];
    day6[0] = doc["day6"];
    day7[0] = doc["day7"];
    duration1[0] = doc["duration1"];
    duration1[1] = doc["duration2"]; 
    const char* mTime1 = doc["time1"];
    const char* mTime2 = doc["time2"];
    const char* mUnit1 = doc["unit1"];
    const char* mUnit2 = doc["unit2"];

    time1[0] = mTime1;
    time1[1] = mTime2;
    unit1[0] = mUnit1;
    unit1[1] = mUnit2;

    if(unit1[0] == "minute"){mDuration1[0] = duration1[0] * 60;} else {mDuration1[0] = duration1[0] / 1;}
    if(unit1[1] == "minute"){mDuration1[1] = duration1[1] * 60;} else {mDuration1[1] = duration1[1] / 1;}

    Serial.println(mDuration1[0]);
    Serial.println(mDuration1[1]);
  }
}

void settings_plot2(){
  if(Firebase.getJSON(fbdo, "settings/plot2")) {
    data_settings_p2 = fbdo.jsonString();
    //Serial.println(data_json);

    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, data_settings_p2);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }

    day1[1] = doc["day1"];
    day2[1] = doc["day2"];
    day3[1] = doc["day3"];
    day4[1] = doc["day4"];
    day5[1] = doc["day5"];
    day6[1] = doc["day6"];
    day7[1] = doc["day7"];
    duration2[0] = doc["duration1"];
    duration2[1] = doc["duration2"]; 
    const char* mTime1 = doc["time1"];
    const char* mTime2 = doc["time2"];
    const char* mUnit1 = doc["unit1"];
    const char* mUnit2 = doc["unit2"];

    time2[0] = mTime1;
    time2[1] = mTime2;
    unit2[0] = mUnit1;
    unit2[1] = mUnit2;

    if(unit2[0] == "minute"){mDuration2[0] = duration2[0] * 60;} else {mDuration2[0] = duration2[0] / 1;}
    if(unit2[1] == "minute"){mDuration2[1] = duration2[1] * 60;} else {mDuration2[1] = duration2[1] / 1;}
  }
}

void settings_lamp(){
  if(Firebase.getJSON(fbdo, "settings/lamp")) {
    data_settings_lamp = fbdo.jsonString();
    Serial.println(data_settings_lamp);

    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, data_settings_lamp);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }

    day1[2] = doc["day1"];
    day2[2] = doc["day2"];
    day3[2] = doc["day3"];
    day4[2] = doc["day4"];
    day5[2] = doc["day5"];
    day6[2] = doc["day6"];
    day7[2] = doc["day7"];
    const char* mTimeOn = doc["time-on"];
    const char* mTimeOff = doc["time-off"];
    
    time_on = mTimeOn;
    time_off = mTimeOff;
  }
}

void control(){
  if(Firebase.getJSON(fbdo, "control")) {
    data_control = fbdo.jsonString();
    //Serial.println(data_json);

    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, data_control);

    if (error) {
      Serial.print(F("deserializeJson() failed: "));
      Serial.println(error.f_str());
      return;
    }

    auto_plot1 = doc["auto-plot1"];
    auto_plot2 = doc["auto-plot2"];
    auto_lamp = doc["auto-lamp"];
    plot1 = doc["plot1"];
    plot2 = doc["plot2"];
    lamp = doc["lamp"];
    const char* mState = doc["state"];
    state = mState;
  }
}

void set_data(){
  currentDelay = millis();
  if(currentDelay - startDelay >= 3000){
    startDelay = currentDelay;
    FirebaseJson sm_json;
      sm_json.add("temperature", temperature);
      sm_json.add("humidity", humidity);
      sm_json.add("plot1", sm_plot[0]);
      sm_json.add("plot2", sm_plot[1]);
    Firebase.setJSON(fbdo, "monitoring", sm_json);
  }
}

void post_data(){
  currentPost = millis();
  if(currentPost - startPost >= 900000){ // ms
    startPost = currentPost;
    
    post_counter++; get_time();
    EEPROM.write(1, post_counter); EEPROM.commit();
    
    Serial.println("Post data");
    FirebaseJson json;
      json.add("id", post_counter);
      json.add("date", current_date);
      json.add("time", current_time);
      json.add("temperature", temperature);
      json.add("humidity", humidity);
      json.add("plot1", sm_plot[0]);
      json.add("plot2", sm_plot[1]);
    Firebase.setJSON(fbdo, "/data/" + String(post_counter), json);
  }
}
