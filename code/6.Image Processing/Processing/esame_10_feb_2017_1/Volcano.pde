class Volcano {
  float posX;
  float posY;
  /*float v2X;
  float v2Y;
  float v3X;
  float v3Y;
  float v4X;
  float v4Y;*/
  Volcano (float posX,float posY) {
    this.posX=posX;
    this.posY=posY;
    /*this.v2X=v2X;
    this.v2Y=v2Y;
    this.v3X=v3X;
    this.v3Y=v3Y;
    this.v4X=v4X;
    this.v4Y=v4Y;*/
    //float v2X,float v2Y,float v3X,float v3Y,float v4X,float v4Y
  }
  void display () {
    fill(165,42,42);
    stroke(165,42,42);
    triangle(posX,posY,posX+20,posY,posX+20,posY-60);
    rect(posX+20,posY-60,30,60);
    triangle(posX+50,posY,posX+70,posY,posX+50,posY-60);
  }
  Fireball create () {
    Fireball b=new Fireball (posX+20+15,posY-60,random(5,10),random(-2,2),random(-8,-2));  
    return b;
  }
}