int A = 7;
int B = 8;
int C = 12;
float delta = 300;
float drop;
float jump;
float time_now;
float period = 6*delta/((float)1000); // 1 rev in s
float rpm = 60/((float)period); // 1 rev in min
long inp;
  

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  
  digitalWrite(A, LOW);
  digitalWrite(B, LOW); 
  digitalWrite(C, LOW);
}

void loop(){
  spin(delta);
  // spin_other(delta);
  if (Serial.available()){
    inp = Serial.parseInt();
    delta = manual_control(delta, inp);
    rpm = get_rpm(delta);
  }
  spin();
  spin_other();
  Serial.println(delta);
  Serial.println(rpm);
}

int get_rpm(float x){
  period = 6*x/((float)1000); // 1 rev in s
  rpm = 60/((float)period); // 1 rev in min
  return rpm;
}

void spin(float delta){
  digitalWrite(C, LOW);
  digitalWrite(A, HIGH);   
  wait(delta);

  //delta = decrease(delta);

  digitalWrite(A, LOW); 
  digitalWrite(B, HIGH);
  wait(delta);

  //delta = decrease(delta);

  digitalWrite(B, LOW);   
  digitalWrite(C, HIGH);
  wait(delta);

  //delta = decrease(delta);
  
}

void spin_other(float delta){
  digitalWrite(B, LOW);
  digitalWrite(A, HIGH);   
  wait(delta);

  // delta = decrease(delta);

  digitalWrite(A, LOW); 
  digitalWrite(C, HIGH);
  wait(delta);

  // delta = decrease(delta);

  digitalWrite(C, LOW);   
  digitalWrite(B, HIGH);
  wait(delta);

  // delta = decrease(delta);
  //Serial.print(delta);
}

void wait(float delta){
  time_now = millis();
  while (millis() - time_now < delta){
  }
}

int decrease(float x){
  if (x > 100){
    drop = 0.05;
  }
  else if (x > 60){
    drop = 0.03;
  }
  else if (x > 15){
    drop = 0.01;
  }
  else{
    drop = 0;
  }
  x = int(x - (x*drop));
  //Serial.println(x);
  return x;
}

int manual_control(float x, long cmd){
  if (cmd == 2){
    x = decrease(x); // speed up
  }
  else if (cmd == 1){
    x = increase(x); // slow down
  }
  return x;
}

int increase(float x){
  if (x > 100){
    jump = 0.05;
  }
  else if (x > 60){
    jump = 0.03;
  }
  else if (x > 15){
    jump = 0.01;
  }
  else{
    jump = 0;
  }
  x = x + (x*drop);  
  return x;
}
