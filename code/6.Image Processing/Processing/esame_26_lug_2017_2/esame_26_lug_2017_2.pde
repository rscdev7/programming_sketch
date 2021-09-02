ArrayList<Flower> a;
void setup(){
  size(512,512);
  background(255);
  a=new ArrayList<Flower>();
}

void draw () {
  background(255);
  if (a.size()>0) {
    for (int i=0;i<a.size();i++) {
      a.get(i).display();
    }
  }
}

void keyPressed () {
  if (keyCode==ALT) {
    setup(); 
  }
  if (keyCode==CONTROL) {
    color q =color(255,random(0,256),255);
    a.add(new Flower(random(50,451),random(50,451),q)); 
  }
}

void mousePressed () {
  for (int i=0;i<a.size();i++) {
    if (a.get(i).check(mouseX,mouseY)==true) {
      a.get(i).turn_on_pt();
    }
  }
}