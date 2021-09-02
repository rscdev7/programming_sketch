class Fireball{
  float posX;
  float posY;
  float sx;
  float sy;
  float d;
  Fireball (float posX,float posY,float d,float sx,float sy) {
    this.posX=posX;
    this.posY=posY;
    this.d=d;
    this.sx=sx;
    this.sy=sy;
  }
  void display() {
    fill(165,42,42);
    noStroke();
    ellipse(posX,posY,d,d);
  }
  void move() {
    posX+=sx;
    posY+=sy;
  }
  void chy () {
    sy+=0.1;
  }
  void run() {
    move();
    chy();
    display();
  }

}