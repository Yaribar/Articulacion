#define INICIO 5 //PULLUP
#define PARO 3 //PULLUP
#define SWITCH 7 //PULLDOWN
#define BOBINA1 8
#define BOBINA2 9
#define BOBINA3 10
#define BOBINA4 11

int  retardo=  5000;
const int pasosPorRevolucion = 200;  // Numero de pasos por revoluciones

bool inicio = 1;
bool origen = 0;
volatile bool paro = true;

void paro_sistema(){
    paro = false;
    Serial.println("paro");  
}

void setup() {
    //Se inicializa puerto serial:
    Serial.begin(115200);

    pinMode(INICIO, INPUT_PULLUP);
    pinMode(PARO, INPUT_PULLUP);
    pinMode(SWITCH, INPUT_PULLUP);
   
    pinMode(BOBINA1, OUTPUT);
    pinMode(BOBINA2, OUTPUT);
    pinMode(BOBINA3, OUTPUT);
    pinMode(BOBINA4, OUTPUT);

    attachInterrupt(digitalPinToInterrupt(PARO), paro_sistema, FALLING);
}

void loop() {
    //**********************
    //***     INICIO    ****
    //**********************
    while (inicio == 1){
      inicio = digitalRead(INICIO);
    }
    inicio=1;  
    Serial.println("bien");
    origen = digitalRead(SWITCH);
    delay(300);
    
    //*********************
    //***    ORIGEN    ****
    //*********************
    //retardo=20000;
    while(origen == 0){
        Serial.println("no origen");
        //MPasos.step(1);
        CW();
        origen = digitalRead(SWITCH);
        if(origen == 1){
            break;
        }     
    }
    retardo=10000;
    delay(2000);
    origen=1;
    
    //*********************
    //***      90°     ****
    //*********************
    //MPasos.setSpeed(160);
    int i=0;
    while(i<15){
        i=i+1;
        CCW();
    }    

    //**********************
    //***     CICLO     ****
    //**********************

    delay(2000);
    while(paro == 1 ){
        Serial.println("origen"); 
        
        //*********************************
        //***  TOMAR Y DEJAR OBJETO    ****
        //*********************************
        Serial.println("tomar y dejar");
        i=0;
        while(i<=10){
            i=i+1;
            CW();
        }
        delay(1000);
        
        //*********************
        //***      90°     ****
        //*********************
        Serial.println("90");
        i=0;
        while(i<=10){
            i=i+1;
            CCW();
        }
        delay(1000);

        //**********************
        //***   FIN CICLO   ****
        //**********************
    }
    if(paro == 0){
        Serial.println("exit");  
        paro = 1;
    }
    
}
void CW(){

    digitalWrite(BOBINA1, HIGH);
    digitalWrite(BOBINA2, LOW);
    digitalWrite(BOBINA3, LOW);
    digitalWrite(BOBINA4, LOW);
    delayMicroseconds (retardo);

    digitalWrite(BOBINA1, LOW);
    digitalWrite(BOBINA2, LOW);
    digitalWrite(BOBINA3, HIGH);
    digitalWrite(BOBINA4, LOW);
    delayMicroseconds (retardo);

    digitalWrite(BOBINA1, LOW);
    digitalWrite(BOBINA2, HIGH);
    digitalWrite(BOBINA3, LOW);
    digitalWrite(BOBINA4, LOW);
    delayMicroseconds (retardo);

    digitalWrite(BOBINA1, LOW);
    digitalWrite(BOBINA2, LOW);
    digitalWrite(BOBINA3, LOW);
    digitalWrite(BOBINA4, HIGH);
    delayMicroseconds (retardo);

}

void CCW(){

    digitalWrite(BOBINA1, LOW);
    digitalWrite(BOBINA2, LOW);
    digitalWrite(BOBINA3, LOW);
    digitalWrite(BOBINA3, HIGH);
    delayMicroseconds (retardo);

    digitalWrite(BOBINA1, LOW);
    digitalWrite(BOBINA2, HIGH);
    digitalWrite(BOBINA3, LOW);
    digitalWrite(BOBINA3, LOW);
    delayMicroseconds (retardo);

    digitalWrite(BOBINA1, LOW);
    digitalWrite(BOBINA2, LOW);
    digitalWrite(BOBINA3, HIGH);
    digitalWrite(BOBINA3, LOW);
    delayMicroseconds (retardo);

    digitalWrite(BOBINA1, HIGH);
    digitalWrite(BOBINA2, LOW);
    digitalWrite(BOBINA3, LOW);
    digitalWrite(BOBINA3, LOW);
    delayMicroseconds (retardo);

}
