class Basket{  
  float posX;
  float posY;
  int cont;
  Basket(float posX,float posY,int cont) {
    this.posX=posX;
    this.posY=posY;
    this.cont=cont;
  }
  void display () {
    fill(128,128,128);
    rectMode(CORNER);
    rect(posX,posY,75,100);
  }
  boolean check (Wastepaper w) {
    if (posX<=w.getX()&&w.getX()<=posX+75&&posY<=w.getY()&&w.getY()<=posY+100) {
      cont++;
      return true;  
    }else{
      return false;  
    }
  }
  int getC() {
    return cont;  
  }
}