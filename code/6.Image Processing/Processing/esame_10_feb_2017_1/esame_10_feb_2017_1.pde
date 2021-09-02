ArrayList<Fireball> a;
Volcano v1;
Volcano v2;
Volcano v3;
boolean stato;
float p=0.20;
void setup() {
    size(640,480);
    background(0);
    frameRate (60);
    a=new ArrayList<Fireball>();
    v1=new Volcano (random(40,600),480);
    v2=new Volcano (random(40,600),480);
    v3=new Volcano (random(40,600),480);
    stato=false;
}

void draw () {
  background(0);
  v1.display();
  if (stato==true&&random(0,1)<p) {
    a.add(v1.create());
  }
  v2.display();
  if (stato==true&&random(0,1)<p) {
    a.add(v2.create());
  }
  v3.display();
  if (stato==true&&random(0,1)<p) {
    a.add(v3.create());
  }
  if (a.size()>0) {
    for (int i=0;i<a.size();i++) {
      a.get(i).run();   
    }
  }
}

void keyPressed () {
  if (key=='N'||key=='n') {
    stato=!stato;  
  }
}