class Sponge {
  float posX;
  float posY;
  float dim;
  color c;
  Sponge (float posX,float posY,float dim) {
    this.posX=posX;
    this.posY=posY;
    this.dim=dim;
    this.c=color(200,200,100);  
  }
  void display () {
    noStroke();
    fill(this.c);
    rectMode (CENTER);
    rect (posX,posY,dim,dim);
  }
  void move () {
    posY=mouseY; 
    posX=mouseX;
  }
  void run () {
    move ();
    display();
  }
  int adsorb (Stain f) {
    //if (dist(posX,posY,f.getX(),f.getY())<20) {
       if (f.getX()-(f.getDiam()/2)>=posX-(dim/2) && f.getX()+(f.getDiam()/2)<=posX+(dim/2) && f.getY()-(f.getDiam()/2)>=posY-(dim/2) && f.getY()+(f.getDiam()/2)<=posY+(dim/2)) {
      dim=dim+(f.getDiam()/2);
      this.c=color((red(c)+red(f.getColor()))/2,(green(c)+green(f.getColor()))/2,(blue(c)+blue(f.getColor()))/2);
      return 1;
    }else{
      return 0;
    }
  }
  void reset () {
    this.dim=30;
    c=color(200,200,100);
  }
}