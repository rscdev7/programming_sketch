class Stain {
  float posX;
  float posY;
  float diam;
  color c;
  Stain (float posX,float posY,float diam,color c) {
    this.posX=posX;
    this.posY=posY;
    this.diam=diam;
    this.c=c;
  }
  void display () {
    noStroke();
    fill(this.c);
    ellipse (posX,posY,diam,diam);
  }
  void move () {
    posY=posY+random(0,5); 
    posX=posX+random(-1,2);
  }
  void run () {
    move ();
    display();
  }
  float getY () {
    return posY;
  }
  float getX () {
    return posX;
  }
  float getDiam () {
    return diam;
  }
  color getColor () {
    return c;  
  }
}