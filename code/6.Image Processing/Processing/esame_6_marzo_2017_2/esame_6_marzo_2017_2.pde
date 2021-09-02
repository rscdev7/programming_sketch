BubbleGun a;
ArrayList<Bubble> b;
void setup () {
  frameRate(60);
  size(512,512);
  background(195,220,238);
  a=new BubbleGun (200,200);
  a.run();
  b=new ArrayList<Bubble>();
}

void draw () {
  background(195,220,238);
  if (a.getState()==true&&mousePressed&&mouseButton==LEFT) {
         b.add(a.shot());
  }
  if (b.size()>0) {
    for (int i=0;i<b.size();i++) {
      if (b.get(i).check()==0) {
        b.get(i).run();
      }else{
        b.remove(i);  
      }
    }
  }
  a.run();
}

void keyPressed () {
  if (key=='c'||key=='C') {
    a.change();
  }
}

void mousePressed () {
  if (mouseButton==LEFT&&a.getState()==false) {
    b.add(a.shot());
  }
}