class Petal {
  float posX;
  float posY;
  color c;
  float sx;
  float sy;
  float theta;
  boolean state;
  Petal (float posX,float posY,color c,float theta) {
    this.posX=posX;
    this.posY=posY;
    this.c=c;
    this.sx=0;
    this.sy=0;
    this.theta=theta;
    this.state=false;
  }
  void display () {
    noStroke();
    fill(c);
    pushMatrix();
    translate(posX,posY);
    //rotate(radians(theta));
    rotate(radians(-theta));
    //bezier(0,0,0+50,0-50,0+100,0,0,0);
    bezier(0,0,50,-50,50,50,0,0);
    popMatrix();
  }
  void move () {
    if (state==true){
      posX+=sx;
      posY+=sy;
      sx+=0.3;
      sy+=0.3;
      //sx+=5;
      //sy+=5;
    }
  }
  void run () {
    move();
    display();
  }
  void turn_on (float sx,float sy) {
    state=true;
    this.sx=sx;
    this.sy=sy;
  }
  boolean getState() {
    return state;  
  }
  /*void setPos (float x,float y) {
    this.posX=x;
    this.posY=y;
  }*/
}