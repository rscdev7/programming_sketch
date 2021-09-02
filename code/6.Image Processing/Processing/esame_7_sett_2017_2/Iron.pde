class Iron {
    float posX;
    float posY;
    color c;
    int dim;
    int verso;
    Iron (int dim,float posX,float posY) {
      this.posX=posX;
      this.posY=posY;
      this.dim=dim;
      float d=random (80,161);
      this.c=color (d);
      this.verso=1;
    }
    void display() {
      noStroke();
      fill(this.c);
      ellipse (posX,posY,dim,dim);
    }
    void move (Magnet m,int v) {
      this.verso=v;
      float sx=(m.getX()-this.posX)/dist(posX,posY,m.getX(),m.getY());
      float sy=(m.getY()-this.posY)/dist(posX,posY,m.getX(),m.getY());
      sx=verso*sx*2;
      sy=verso*sy*2;
      posX+=sx;
      posY+=sy;
    }
    void run(Magnet m,int v) {
      move(m,v);
      display();
    }
}