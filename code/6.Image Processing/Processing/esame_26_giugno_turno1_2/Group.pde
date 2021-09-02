class Group{
  float posX;
  float posY;
  ArrayList<Seed> w;
  int num;
  Group(float posX,float posY) {
    this.posX=posX;
    this.posY=posY;
    w=new ArrayList<Seed> ();
    w.add (new Seed (posX,posY,20,30,40,color(random(0,255),random(0,255),random(0,255)),true));
    num++;
  }
  void display () {
    for (int i=0;i<w.size();i++) {
      w.get(i).run();  
    }    
  }
  void setSpeed () {
    for (int i=0;i<w.size();i++) {
      w.get(i).change(random(-2,2),random(-3,0)+(0.25*num));  
    }
  }
  boolean checkTouch (Seed r) {
     for (int i=0;i<w.size();i++) {
      if (dist(w.get(i).getX(),w.get(i).getY(),r.getX(),r.getY())<((w.get(i).getDim()/2)+(r.getDim()/2))) {
        r.ch();
        w.add(r); 
        num++;
        return true;
      }
    }
    return false;
  }
}