class Seed{
  float posX;
  float posY;
  float sx;
  float sy;
  float d;
  color c;
  boolean legato;
  Seed (float posX,float posY,float sx,float sy,float d,color c,boolean legato) {
    this.posX=posX;
    this.posY=posY;
    this.sx=sx;
    this.sy=sy;
    this.d=d;
    this.c=c;
    this.legato=legato;
  }
  void display () {
    fill(c);
    stroke (0,0,0);
    ellipse(posX,posY,d,d);
  }
  void move () {
    posX=posX+sx;
    posY=posY+sy;
  }
  void run() {
    move();
    display();
  }
  void change (float sx,float sy) {
    this.sx=sx;
    this.sy=sy;
  }
  boolean legato () {
    return legato;  
  }
  void ch () {
    legato=!legato;  
  }
  float getX() {return posX;}
  float getY() {return posY;}
  float getDim() {return d;}
}