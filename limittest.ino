int A = 7;
int B = 8;
int C = 12;
int delta = 800;

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
  spin();
}

void spin(){
  digitalWrite(C, LOW);
  digitalWrite(A, HIGH);   
  delay(delta);

  delta = decrease(delta);

  digitalWrite(A, LOW); 
  digitalWrite(B, HIGH);
  delay(delta);

  delta = decrease(delta);

  digitalWrite(B, LOW);   
  digitalWrite(C, HIGH);
  delay(delta);

  delta = decrease(delta);
  //Serial.println(delta);
}

int decrease(int x){
  if (x > 80){
    x = x - int(x*0.02);
  }
  return x;
}
