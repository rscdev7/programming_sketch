class Wastepaper {
  float posX;
  float posY;
  float sy;
  float d;
  boolean m;
  Wastepaper(float posX,float posY,float sy,float d) {
    this.posX=posX;
    this.posY=posY;
    this.sy=sy;
    this.d=d;
    this.m=false;
  }
  void display () {
    fill(255,255,255);
    stroke(0,0,0);
    pushMatrix ();
    translate(posX,posY);
    rectMode(CENTER);
    for (int i=0;i<4;i++) {
      pushMatrix();
      rotate(radians(22.5*i));
      rect(0,0,d,d);
      popMatrix();
    }
    popMatrix();
  }
  void move(float x,float y) {
    this.posX=x;
    this.posY=y;
  }
  void mov() {
    this.posY+=sy;
  }
  boolean check (float x,float y) {
    if (dist(posX,posY,x,y)<d) {
      return true;  
    }else{
      return false;  
    }
  }
  void ch() {
    m=!m;  
  }
  float getX() {return posX;}
  float getY(){return posY;}
  boolean getM(){return m;}
}