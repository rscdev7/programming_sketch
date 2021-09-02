int speed;
int size;
float p;
int stato;
ArrayList<RainDrop> a;
float tr;
int flash;
int change;
void setup() {
  size (512,512);
  background (255);
  frameRate (60);
  speed=9;
  size=1;
  p=0.3;
  a=new ArrayList<RainDrop> ();
  stato=1;
  flash=0;
  change=0;
}

void draw () {
  if (stato==1) {
    if (change==1) { 
      fill (0,0,0,tr);
      noStroke();
      rect (0,0,512,512);
      if (tr<20) {
        tr=tr+0.2;
      }else{
        change=0;
        background(0);
      }
    }
    if (flash==1) {
      fill (255,255,255,tr);
      rect (0,0,512,512);
      if (tr>=0) {
        tr=tr-15;
      }else{
        flash=0;
      }
    }
    if (change==0&&flash==0) {
        background(0);
          int prob=int(p/8);
          int [] r=new int[prob];
          int count=0;
          int estrazione=0;
          for (int i=0;i<prob;i++) {
            r[i]=int(random (0,8));
          }
          for (int i=0;i<prob;i++) {
            estrazione=int(random (0,8));
            for (int j=0;j<prob;j++) {
              if (estrazione==r[j]) {
                count++;
                j=prob;
              }
            }
          }
          if (count==prob) {
            a.add (new RainDrop (random(0,513),0,speed+int(random(-2,3)),size+int(random(-2,3))));
          }
          if (a.size()>0) {
            for (int i=0;i<a.size();i++) {
              a.get(i).run();
            }
          }
    }
  }else{
    if (change==1) { 
      fill (255,255,255,tr);
      noStroke();
      rect (0,0,512,512);
      if (tr<50) {
        tr=tr+0.2;
      }else{
        change=0;
        background(255);
      }
    }
  }
}

void keyPressed () {
  if (key=='+') {
    speed+=2;
    size+=5;
    for (int i=0;i<a.size();i++) {
      a.get(i).setDim(size);
      a.get(i).setSpeed(speed);
    }
    p+=0.1;
    constrain (p,0.3,0.8);
  }
  if (key=='-') {
    if(speed-2>=9) speed-=2;
    if(size-5>=1)size-=5;
    for (int i=0;i<a.size();i++) {
      a.get(i).setDim(size);
      a.get(i).setSpeed(speed);
    }
    p-=0.1;
    constrain (p,0.3,0.8);
  }
  if (flash==0&&stato==1&&key=='T'||key=='t') {
        flash=1;
        tr=100;  
  }
}

void mousePressed () {
  if (mouseButton==RIGHT) {
    if (stato==0) {
      stato=1;
      change=1;
      tr=0;
    }else{
      stato=0;
      change=1;
      tr=0;
    }
  }  
}