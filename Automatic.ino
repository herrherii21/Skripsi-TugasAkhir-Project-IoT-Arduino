void automatic_plot1(){
  // Timer 1
  if((current_day == "Monday"    && day1[0] == true ||
      current_day == "Tuesday"   && day2[0] == true ||
      current_day == "Wednesday" && day3[0] == true ||
      current_day == "Thursday"  && day4[0] == true ||
      current_day == "Friday"    && day5[0] == true ||
      current_day == "Saturday"  && day6[0] == true ||
      current_day == "Sunday"    && day7[0] == true) && current_time == time1[0]){
    if(active_event[0] == false){
      state_pump_plot1 = true;        // Nyalakan Relay Pompa
      digitalWrite(valve1_pin, HIGH); // nyalakan Relay Valve 1
      active_timer[0] = true;         // Trigger timer on
      active_event[0] = true;         // Matikan event
      //Serial.println("goto active timer 1");
    }
  }else{active_event[0] = false;}
   
  if(timer_on[0] >= mDuration1[0]){
    state_pump_plot1 = false;        // Matikan Relay Pompa
    digitalWrite(valve1_pin, LOW);  // Matikan Relay Valve 1
    active_timer[0] = false;
    timer_on[0] = 0;
  }

  // Timer 2
  if((current_day == "Monday"    && day1[0] == true ||
      current_day == "Tuesday"   && day2[0] == true ||
      current_day == "Wednesday" && day3[0] == true ||
      current_day == "Thursday"  && day4[0] == true ||
      current_day == "Friday"    && day5[0] == true ||
      current_day == "Saturday"  && day6[0] == true ||
      current_day == "Sunday"    && day7[0] == true) && current_time == time1[1]){
    if(active_event[1] == false){
      state_pump_plot1 = true;        // Nyalakan Relay Pompa
      digitalWrite(valve1_pin, HIGH); // Nyalakan Relay Valve 1
      active_timer[1] = true;         // Trigger timer on
      active_event[1] = true;         // Matikan event
      //Serial.println("goto active timer 2");
    }
  }else{active_event[1] = false;}
   
  if(timer_on[1] >= mDuration1[1]){
    state_pump_plot1 = false;       // Matikan Relay Pompa
    digitalWrite(valve1_pin, LOW);  // Matikan Relay Valve 1
    active_timer[1] = false;
    timer_on[1] = 0;
  }
}

void automatic_plot2(){
  // Timer 1
  if((current_day == "Monday"    && day1[1] == true ||
      current_day == "Tuesday"   && day2[1] == true ||
      current_day == "Wednesday" && day3[1] == true ||
      current_day == "Thursday"  && day4[1] == true ||
      current_day == "Friday"    && day5[1] == true ||
      current_day == "Saturday"  && day6[1] == true ||
      current_day == "Sunday"    && day7[1] == true) && current_time == time2[0]){
    if(active_event[2] == false){
      state_pump_plot2 = true;        // Nyalakan Relay Pompa
      digitalWrite(valve2_pin, HIGH); // nyalakan Relay Valve 2
      active_timer[2] = true; // Trigger timer on
      active_event[2] = true; // Matikan event
      //Serial.println("goto active timer 2");
    }
  }else{active_event[2] = false;}
   
  if(timer_on[2] >= mDuration2[0]){
    state_pump_plot2 = false;      // Matikan Relay Pompa
    digitalWrite(valve2_pin, LOW); // Matikan Relay Valve 2
    active_timer[2] = false;
    timer_on[2] = 0;
  }

  // Timer 2
  if((current_day == "Monday"    && day1[1] == true ||
      current_day == "Tuesday"   && day2[1] == true ||
      current_day == "Wednesday" && day3[1] == true ||
      current_day == "Thursday"  && day4[1] == true ||
      current_day == "Friday"    && day5[1] == true ||
      current_day == "Saturday"  && day6[1] == true ||
      current_day == "Sunday"    && day7[1] == true) && current_time == time2[1]){
    if(active_event[3] == false){
      state_pump_plot2 = true;        // Nyalakan Relay Pompa
      digitalWrite(valve2_pin, HIGH); // Nyalakan Relay Valve 2
      active_timer[3] = true; // Trigger timer on
      active_event[3] = true; // Matikan event
      //Serial.println("goto active timer 2");
    }
  }else{active_event[3] = false;}
   
  if(timer_on[3] >= mDuration2[1]){
    state_pump_plot2 = false;       // Matikan Relay Pompa
    digitalWrite(valve2_pin, LOW);  // Matikan Relay Valve 2
    active_timer[3] = false;
    timer_on[3] = 0;
  }
}

void automatic_lamp(){
  if((current_day == "Monday"    && day1[2] == true ||
      current_day == "Tuesday"   && day2[2] == true ||
      current_day == "Wednesday" && day3[2] == true ||
      current_day == "Thursday"  && day4[2] == true ||
      current_day == "Friday"    && day5[2] == true ||
      current_day == "Saturday"  && day6[2] == true ||
      current_day == "Sunday"    && day7[2] == true) && current_time == time_on){
    digitalWrite(lamp_pin, HIGH);
  }
  if(current_time == time_off){
    digitalWrite(lamp_pin, LOW);
  } 
}
