void setup()
{
  pinMode(5, OUTPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT); 
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT); 
  pinMode(13, INPUT);
}

void loop()
{
  if(digitalRead(13) == HIGH){ //do
    tone(5, 261);   	
  }
  else if(digitalRead(12) == HIGH){// re
    tone(5, 297);		
  }
  else if(digitalRead(11) == HIGH){ //mi
    tone(5, 330);		
  }
  else if(digitalRead(10) == HIGH){//fa
    tone(5, 352);		
  }
  else if(digitalRead(9) == HIGH){//sol
    tone(5, 396);		
  }
  else if(digitalRead(8) == HIGH){ //la
    tone(5, 440);
  }
  else if(digitalRead(7) == HIGH){ //si
    tone(5, 495);
  }
  else if(digitalRead(6) == HIGH){ //do
    tone(5, 528);
  }
  else{
    noTone(5);
  }
  delay(50);
}
