You y;
int inf;
int sup;
ArrayList<Blade> b;
int count;
float p=0.05;
void setup () {
  size(700,700);
  background (0);
  frameRate (60);
  y=new You (150,150,100);
  y.run();
  inf=3;
  sup=10;
  b=new ArrayList<Blade> ();
  loop();
}

void draw () {
  background (0);
  y.run();
  if (count==180) {
    y.incDim(5);
    inf++;
    sup++;
    count=0;
  }else{
    count++;
  }
  if (b.size()>0) {
    for (int i=0;i<b.size();i++) {
      b.get(i).run();
      if (y.isHitted(b.get(i))) {
        noLoop();
        textAlign (CENTER);
        textSize(30);
        fill(255,255,0);
        text ("GAME OVER",350,350);
      }
    }
  }
  if (random(0,1)<p) {
    b.add(new Blade (-50,random (0,701),random(inf,sup),0));
  }
}

void keyPressed () {
  if (key=='R'||key=='r')  {
    setup();  
  }
  
}