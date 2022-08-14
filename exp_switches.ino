
int A = 7;
int B = 8;
int C = 12;
float delta = 500;
float max_rpm = 100;
float rpm = 0;
float freq = 0;
float gap = 0;
int Ts = 20;
int T = 4/Ts; // settling time = Ts = 4/T
unsigned long time_now = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);

  digitalWrite(B, LOW);
  digitalWrite(C, LOW); 
  digitalWrite(A, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  spin();

  //  if(millis() < 30000)
  //  delta = decrease(delta);

  //  if(millis() > 30000)
  //  delta = increase(delta);

  // print elapsed time since upload
  // Serial.print(millis());
  // Serial.print('\n');
}

void spin(){
  digitalWrite(C, LOW);
  digitalWrite(A, HIGH);   
  wait();

  digitalWrite(A, LOW); 
  digitalWrite(B, HIGH);
  wait();

  digitalWrite(B, LOW);   
  digitalWrite(C, HIGH);
  wait();

}

 float wait(){
  time_now = millis();
  gap = calc_gap();
  while(millis() < time_now + gap) { // wait for gap ms
  }
 }

float calc_gap(){
  // use exponential model
  // convert ms to s
  rpm = max_rpm*(1-exp(-T*millis()/1000)); 
  Serial.println(rpm);
  freq = rpm/60; // 1rev/min * 1min/60s | Hz
  gap = 1/(6*freq) * 1000; // 1s*1000ms/s | ms
  Serial.println(gap);
  return gap;
}
