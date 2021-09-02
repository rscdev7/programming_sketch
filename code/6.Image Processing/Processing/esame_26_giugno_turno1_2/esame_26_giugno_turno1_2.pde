ArrayList<Seed> f;
ArrayList<Group> g;
void setup() {
  size(512,512);
  background(255);
  f=new ArrayList<Seed>();
  g=new ArrayList<Group>();
}

void draw () {
  background(255); 
  if (f.size()>0) {
    int l=0;
    for (int i=0;i<f.size();i++) {
      l=0;
      for (int j=0;j<g.size()&&l==0;j++) {
        if (g.get(j).checkTouch(f.get(i))==true) {
          f.remove(i);
          l=1;
        }
      }
      if (l==0) f.get(i).run();
    }    
  }
  for (int i=0;i<g.size();i++) {
      g.get(i).setSpeed();
      g.get(i).display();
  }
}

void keyPressed () {
  if (key=='N'||key=='n') {
    g.add(new Group(random(12,500),random(530,560)));  
  }
}

void mousePressed () {
  if (mouseButton==RIGHT) {
    setup();  
  }
  if (mouseButton==LEFT) {
    color c=color (random(0,255),random(0,255),random(0,255));
    f.add(new Seed (mouseX,mouseY,0,5,random(7,21),c,false));  
  }
}