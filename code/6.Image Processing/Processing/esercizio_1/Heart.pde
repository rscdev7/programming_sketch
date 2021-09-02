class Heart{
  float posX;
  float posY;
  float sx;
  float sy;
  boolean alive;
  Heart (float posX,float posY,float sx,float sy) {
    this.posX=posX;
    this.posY=posY;
    this.sx=sx;
    this.sy=sy;
    this.alive=true;
  }
  void display () {
    noStroke();
    if (alive==true) {
      fill(230,0,0);
    }else{
      fill(128,128,128);  
    }
    bezier(posX,posY,posX+30,posY-30,posX+20,posY-60,posX,posY-30);
    bezier(posX,posY,posX-30,posY-30,posX-20,posY-60,posX,posY-30);  
  }
  void move () {
    if (alive==false) {
      sy=sy+(0.1+((00374%21)/80));    
    }
    posX+=sx;
    posY+=sy;
  }
  void run() {
    move();
    display();
  }
  boolean check () {
    if (mouseX>=posX-30&&mouseX<=posX+30&&mouseY<=posY&&mouseY>=posY-60) {
      alive=false;
      return true;
    }else{
      return false;  
    }
  }
}