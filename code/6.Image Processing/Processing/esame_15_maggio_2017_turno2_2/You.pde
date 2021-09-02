class You {
  float posX;
  float posY;
  float dim;
  You (float posX,float posY,float dim) {
    this.posX=posX;
    this.posY=posY;
    this.dim=dim;
  }
  void display () {
    fill (239,63,207);
    noStroke();
    ellipse(posX,posY,dim,dim);
  }
  void move () {
    posX=mouseX;
    posY=mouseY;
  }
  void run () {
    move();
    display();
  }
  void incDim (float val) {
    this.dim+=val;  
  }
  boolean isHitted (Blade b) {
    if (dist (posX,posY,b.getX(),b.getY())<dim/2) {
      return true;
    }else{
      return false;  
    }
  }
}