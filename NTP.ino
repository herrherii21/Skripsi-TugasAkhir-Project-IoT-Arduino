void get_time(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  // Hari 
  char now_day[10];
  strftime(now_day, 10, "%A", &timeinfo);
  //Serial.println(now_day);
  current_day = String(now_day);

  // Tanggal
  char now_date[3];
  strftime(now_date, 3, "%d", &timeinfo);
  //Serial.println(now_date);
  
  // bulan
  char now_month[10];
  strftime(now_month, 10, "%B", &timeinfo);
  //Serial.println(now_month);
  
  // Tahun
  char now_year[5];
  strftime(now_year, 5, "%Y", &timeinfo);
  //Serial.println(now_year);

  // Format ke tanggal lengkap
  current_date = String(now_date) + " " + String(now_month) + " " + String(now_year);
  //Serial.println(current_date);


  // Jam
  char now_hour[3];
  strftime(now_hour, 3, "%H", &timeinfo);
  //Serial.println(now_hour);
  
  // Menit
  char now_minute[3];
  strftime(now_minute, 3, "%M", &timeinfo);
  current_minute = atoi(now_minute);
  //Serial.println(now_minute);

  // Format ke Waktu HH:mm
  current_time = String(now_hour) + ":" + String(now_minute);
  //Serial.println(current_time);

  current_minute = atoi(now_minute);
  
  // Detik
  char now_second[3];
  strftime(now_second, 3, "%S", &timeinfo);
  current_second = atoi(now_second);
  //Serial.println(current_second);
}
