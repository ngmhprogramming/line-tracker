#define S2_1 2
#define SOUT_1 3
#define S2_2 4
#define SOUT_2 5
#define SPEED 150
#define GAP 1
#define AIA A0
#define AIB A1
#define BIA A2
#define BIB A3
#define calibrate 1
#define L_HARDCODE 20
#define R_HARDCODE 20

int total, left_l, left_h, right_l, right_h, L_THRESHOLD = L_HARDCODE, R_THRESHOLD = R_HARDCODE;
bool left, right;
void setup() {
  //Colour Sensors
  pinMode(S2_1, OUTPUT);
  pinMode(SOUT_1, INPUT);
  pinMode(S2_2, OUTPUT);
  pinMode(SOUT_2, INPUT);

  //Motors
  pinMode(AIA, OUTPUT);
  pinMode(AIB, OUTPUT);
  pinMode(BIA, OUTPUT);
  pinMode(BIB, OUTPUT);

  //Colour Sensors
  digitalWrite(S2_1, HIGH);
  digitalWrite(S2_2, HIGH);

  //Calibration Mode
  //Average of 100 readings at 20 millisecond intervals
  Serial.begin(9600);
  if(calibrate){
    Serial.println("Get ready");
    delay(2000);
    Serial.println("White");
    total = 0;
    for(int i = 0; i < 100; i++){
      total += pulseIn(SOUT_1, LOW);
      delay(20);
    }
    total /= 100;
    left_l = total;
    total = 0;
    for(int i = 0; i < 100; i++){
      total += pulseIn(SOUT_2, LOW);
      delay(20);
    }
    total /= 100;
    right_l = total;
    Serial.println("Done");
    Serial.println("Get ready");
    delay(3000);
    Serial.println("Black");
    total = 0;
    for(int i = 0; i < 100; i++){
      total += pulseIn(SOUT_1, LOW);
      delay(20);
    }
    total /= 100;
    left_h = total;
    total = 0;
    for(int i = 0; i < 100; i++){
      total += pulseIn(SOUT_2, LOW);
      delay(20);
    }
    total /= 100;
    right_h = total;
    Serial.println("Done");
    L_THRESHOLD = (left_l+left_h)/2;
    R_THRESHOLD = (right_l+right_h)/2;
    Serial.println(L_THRESHOLD);
    Serial.println(R_THRESHOLD);
  }
}

void moveLeftForward(){
  analogWrite(AIB, SPEED);
  delay(GAP);
  analogWrite(AIB, 0);
}

void moveRightForward(){
  analogWrite(BIA, SPEED);
  delay(GAP);
  analogWrite(BIA, 0);
}

bool blackLeft(){
  return pulseIn(SOUT_1, LOW) >= L_THRESHOLD;
}

bool blackRight(){
  return pulseIn(SOUT_2, LOW) >= R_THRESHOLD;
}

void loop() {
  left = blackLeft();
  right = blackRight();
  if(left == right){
    //When both are white or both are black, move forward
    moveLeftForward();
    moveRightForward();
  } else if(left){
    //If the left is on black, turn left until both are same
    moveRightForward();
  } else if(right){
    //If the right is on black, turn right until both are same
    moveLeftForward();
  }
}
