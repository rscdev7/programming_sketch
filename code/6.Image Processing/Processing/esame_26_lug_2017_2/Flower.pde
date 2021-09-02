class Flower{
  float posX;
  float posY;
  color g;
  Petal[] pet;
  float diam;
  Flower (float posX,float posY,color g) {
    this.posX=posX;
    this.posY=posY;
    this.g=g;
    this.diam=25;
    pet=new Petal[6];
    for (int i=0;i<6;i++) {
      //pet[i]=new Petal (posX,posY,g,0);  
      pet[i]=new Petal (posX,posY,g,i*60);
    }
  }
  void display () {
    /*pushMatrix();
    translate (posX,posY);
    for (int i=0;i<6;i++) {
      pushMatrix();
      rotate(radians(60*i));
      pet[i].setPos(0,0);
      pet[i].run();
      popMatrix();
    }
    popMatrix();*/
    for (int i=0;i<6;i++) {
      pet[i].run();
    }
    fill(255,255,0);
    ellipse (posX,posY,diam,diam);
  }
  boolean check (float x,float y) {
    if (dist(posX,posY,x,y)<=diam/2) {
      return true;  
    }else{
      return false;    
    }
  }
  void turn_on_pt () {
      boolean w=true;
      int k=0;
      int []in=new int[6];
      for (int i=0;i<6;i++) {
        if (pet[i].getState()==false) {
          w=false; 
          in[k]=i;
          k++;
        }
      }
      if (w==false) {
        int d=int(random(0,k));
        pet[in[d]].turn_on(random(-5,2),random(-5,2));
      }
  }
}