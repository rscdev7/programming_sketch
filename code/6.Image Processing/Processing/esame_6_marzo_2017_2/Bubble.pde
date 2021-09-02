class Bubble {
  float posX;
  float posY;
  float diam;
  float sx;
  float sy;
  float lim;
  Bubble (float posX,float posY,float diam,float sx,float sy,float lim) {
    this.posX=posX;
    this.posY=posY;
    this.diam=diam;
    this.sx=sx;
    this.sy=sy;
    this.lim=lim;
  }
  void display () {
      noStroke();
      fill (0,130,233);
      ellipse (posX,posY,diam,diam);
      fill(255,255,255);
      ellipse(((posX-(diam/2))+posX)/2,(posY+(posY-(diam/2)))/2,(diam/2)/4,(diam/2)/4);
  }
  void move () {
    sy+=0.4;
    if (sx-0.2>=lim) {
      sx-=0.2;
    }
    posY=posY-abs(sy);
    posX=posX+log(sx);
  }
  void run() {
    move();
    display();  
  }
  int check () {
    if (posX<0||posX-diam/2<0||posY<0||posY-diam/2<0) {
      return 1;  
    }else{
      return 0;
    }
  }
}