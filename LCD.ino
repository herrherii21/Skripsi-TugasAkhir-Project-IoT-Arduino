void display_sens(){
  // temperature
  lcd.setCursor(0,0); lcd.print("T:");
  lcd.setCursor(2,0); sprintf(mTemp, "%3d", temperature); lcd.print(mTemp);
  lcd.setCursor(5,0); lcd.print(char(223));
  lcd.setCursor(6,0); lcd.print("C");
  
  // humidity
  lcd.setCursor(0,1); lcd.print("H:");
  lcd.setCursor(2,1); sprintf(mTemp, "%3d", humidity); lcd.print(mTemp);
  lcd.setCursor(6,1); lcd.print("%");
  
  // plot1
  lcd.setCursor(9,0); lcd.print("P1:");
  lcd.setCursor(12,0); sprintf(mPlot1, "%3d", sm_plot[0]); lcd.print(mPlot1);
  lcd.setCursor(15,0); lcd.print("%");

  // plot2
  lcd.setCursor(9,1); lcd.print("P2:");
  lcd.setCursor(12,1); sprintf(mPlot2, "%3d", sm_plot[1]); lcd.print(mPlot2);
  lcd.setCursor(15,1); lcd.print("%");
}
