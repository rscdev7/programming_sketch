Sponge y;
ArrayList<Stain> a;
void setup () {
  size(700,700);
  background(0,252,252);
  y=new Sponge (50,50,30);
  a=new ArrayList<Stain> ();
}

void draw () {
  background(0,252,252);
  y.run();
  if (a.size()>0) {
    for (int i=0;i<a.size();i++) {
      a.get(i).run();
    }
  }
  if (a.size()>0) {
    for (int i=0;i<a.size();i++) {
      if(y.adsorb(a.get(i))==1) {
        a.remove(i);  
      }
    }
  }
}

void keyPressed () {
  if (key=='S'||key=='s') {
    a.add(new Stain (random(50,651),-30,random(10,51),color(random(0,256),random(0,256),random(0,256))));  
  }
  if (key=='R'||key=='r') {
    y.reset();
  }
}