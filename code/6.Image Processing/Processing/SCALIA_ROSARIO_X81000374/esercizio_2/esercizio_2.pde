PImage l;
float alfa;

void setup() {
  size(768,256);
  l=loadImage("lena.png");
  l.resize(256,256);
  background(128,128,128);
  alfa=0.5;
}

void draw() {
  background(128,128,128);
  image(randomlm(256,256),0,0);
  image(l,256,0);
  image(combine(l,randomlm(256,256),alfa),512,0);
  fill(255,0,0);
  textSize(20);
  text(alfa,0,20);
}

PImage randomlm(int a1,int a2) {
  PImage w=createImage(a1,a2,RGB);
  w.loadPixels();
  float r=0.0;
  float g=0.0;
  float b=0.0;
  for (int i=0;i<w.pixels.length;i++) {
      r=random(0,229);
      g=random(0,229);
      b=random(0,229);
      w.pixels[i]=color(r,g,b);
  }
  w.updatePixels();
  return w;
}

PImage combine (PImage I,PImage J,float a) {
  //Si presuppone che le 2 immagini in input abbiano
  //Dimensioni Identiche !
  PImage w=createImage (I.width,I.height,RGB);
  w.loadPixels();
  I.loadPixels();
  J.loadPixels();
  float r=0.0;
  float r2=0.0;
  float g=0.0;
  float g2=0.0;
  float b=0.0; 
  float b2=0.0;
  for (int i=0;i<w.pixels.length;i++) {
    r=red(I.pixels[i]);  
    r2=red(J.pixels[i]);
    g=green(I.pixels[i]);  
    g2=green(J.pixels[i]);
    b=blue(I.pixels[i]);  
    b2=blue(J.pixels[i]);
    w.pixels[i]=color((r*a)+(r2*(1-a)),(g*a)+(g2*(1-a)),(b*a)+(b2*(1-a)));
  }
  w.updatePixels();
  return w;
}

void keyPressed () {
  if (key=='+'&&alfa+0.1<=1) {
    alfa+=0.1;  
  }
  if (key=='-'&&alfa-0.1>=0) {
    alfa-=0.1;  
  }
}