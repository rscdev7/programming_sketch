PImage o;
int s=80;
int mx1;
int my1;
int mx2;
int my2;
int k;
void setup () {
  size(512,512);
  o=loadImage ("lena.png");
  o.resize (512,512);
  image (o,0,0);
  k=0;
  rectMode(CORNER);
  mx1=0;
  mx2=0;
  my1=0;
  my2=0;
}

void draw () {
  image (o,0,0);
  noFill();
  strokeWeight(1);
  stroke(0,0,0);
  //rectMode(CENTER);
  rect(mouseX-s/2,mouseY-s/2,s,s);
  stroke (0,0,255);
  strokeWeight(5);
  if (k>0) rect(mx1-s/2,my1-s/2,s,s);
}

PImage swap (PImage w,int x1,int y1,int x2,int y2,int s){
  k=0;
  PImage m1=o.get(x1-s/2,y1-s/2,s,s);
  PImage m2=o.get(x2-s/2,y2-s/2,s,s);
  //PImage m1=o.get(x1,y1,s,s);
  //PImage m2=o.get(x2,y2,s,s);
  o.set(x1-s/2,y1-s/2,m2);
  o.set(x2-s/2,y2-s/2,m1);
  //o.set(x1,y1,m2);
  //o.set(x2,y2,m1);
  return o;
}

void mousePressed () {
  if (k==0) {
    mx1=mouseX;
    my1=mouseY;
    if ((mx1-s/2)<0) {
        mx1=5+s/2;
    }
    if ((my1-s/2)<0) {
        my1=5+s/2;
    }
    if ((mx1+s)>511) {
        mx1=mx1-s;
    }
    if ((my1+s)>511) {
        my1=my1-s;
    }
    k++;
  }else{
    mx2=mouseX;
    my2=mouseY;
    if ((mx2-s/2)<0) {
      mx2=5+s/2;
    }
    if ((my2-s/2)<0) {
      my2=5+s/2;
    }
    if ((mx2+s)>511) {
        mx2=mx2-s;
    }
    if ((my2+s)>511) {
        my2=my2-s;
    }
    swap (o,mx1,my1,mx2,my2,s);
  }
}

void keyPressed () {
  if (k==0&&key=='+'&&s+10<=150) {
    s+=10;
    setup();
  }
  if (k==0&&key=='-'&&s-10>=30) {
    s-=10;
    setup();
  }
}