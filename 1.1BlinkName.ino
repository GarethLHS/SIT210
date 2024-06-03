// GarethLHS
// Subject: SIT210 Embedded System Development
// Task 1.1BlinkName


const int buttonPin = 2;  // the number of the pushbutton pin
const int ledPin = 13;    // the number of the LED pin

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    //digitalWrite(ledPin, HIGH);
    gareth();
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    //dit();
    //dit();
    //dit();
  }
}


void gareth(){
  g();
  a();
  r();
  e();
  t();
  h();
}

void a(){
    //a .-
  dit();
  dah();
}
// b, c, d, 

void e(){
  //e .
  dit();
}

//f,

void g(){
  //g --.
  dah();
  dah();
  dit();
}

void h(){
  //h .....
  dit();
  dit();
  dit();
  dit();
  dit();
}

//i
//j, 
//k,
//l
//m,
//n,
//o,
//p,
//q,

void r(){
  //r .-.
  dit();
  dah();
  dit();
}
//s

 void t(){
  //t -
  dah();
 } 

//u,v,w,x,y,z

void dah(){
  digitalWrite(ledPin, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1500);       // 3 units               // wait for a second
  digitalWrite(ledPin, LOW);   // turn the LED off by making the voltage LOW
  delay(500);   // intercharacter time 1 unit
}

void dit(){
    digitalWrite(ledPin, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(500);    // 1 unit                   // wait for a second
  digitalWrite(ledPin, LOW);   // turn the LED off by making the voltage LOW
  delay(500);   // intercharacter time 1 unit
}
