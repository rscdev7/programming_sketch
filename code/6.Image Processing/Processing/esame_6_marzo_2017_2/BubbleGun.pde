class BubbleGun {
  float posX;
  float posY;
  boolean stato;
  BubbleGun (float posX,float posY) {
    this.posX=posX;
    this.posY=posY;
    this.stato=false;
  }
  void display () {
    noStroke();
    rectMode (CENTER);
    fill(0,0,255);
    rect (posX,posY,100,20);
    rectMode (CORNERS);
    if (stato==false) {
      fill(0,0,255);  
    }else{
      fill(255,0,0);
    }
    rect (posX-50,posY+10,posX-20,posY);
    
  }
  void move() {
    posX=mouseX;
    posY=mouseY;
  }
  void run() {
    move();
    display ();  
  }
  void change () {
    stato=!stato;  
  }
  Bubble shot () {
    float diam=random(10,41);
    return new Bubble (mouseX+50,(mouseY+10)-(diam/2),diam,random(4,65),random(4,11),random(2,5));    
  }
  boolean getState () {
    return stato;  
  }
}