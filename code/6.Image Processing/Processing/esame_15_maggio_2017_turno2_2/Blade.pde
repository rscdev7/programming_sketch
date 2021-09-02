class Blade {
  float posCX;
  float posCY;
  float sx;
  int A;
  Blade (float posCX,float posCY,float sx,int A) {
    this.posCX=posCX;
    this.posCY=posCY;
    this.sx=sx;
    this.A=A; 
  }
  void display() {
    noStroke();
    fill(255,0,0);
    pushMatrix();
    translate (posCX,posCY);
    rotate (radians(A));
    for (int i=0;i<12;i++) {
      pushMatrix();
      rotate (i*radians(30));
      triangle (0,0,0,40,25,40);
      popMatrix();
    }
    popMatrix();
  }
  void move () {
    if (sx>0) {
      posCX+=sx;
      A+=sx;
    }
  }
  void run () {
    move ();
    display();
  }
  float getX() {
    return posCX;  
  }
  float getY() {
    return posCY;  
  }
}