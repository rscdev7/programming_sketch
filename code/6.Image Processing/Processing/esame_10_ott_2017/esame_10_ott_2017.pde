PImage y;
int t;
void setup() {
  size (768,256);
  y=loadImage ("lena.png");
  y.resize (256,256);
  t=0;
  image (y,0,0);
  image (colorplus(y,t),257,0);
  image (chroma(colorplus(y,t)),514,0);
}

void draw () {
  image (y,0,0);
  image (colorplus(y,t),257,0);
  image (chroma(colorplus(y,t)),514,0);
}

void keyPressed () {
  if (key=='+'&&t<=45) {
    t+=5;
  }
  if (key=='-'&&t>=5) {
    t-=5;
  }
}
PImage colorplus (PImage I,int t) {
  PImage c=I.copy();
  I.loadPixels();
  c.loadPixels ();
  float r;
  float g;
  float b;
  for (int i=0;i<I.pixels.length;i++) {
      r=red(I.pixels[i]);
      g=green(I.pixels[i]);
      b=blue(I.pixels[i]);
      float mx=max(r,g,b);
      if (mx==r){
        c.pixels[i]=color (constrain(r+t,0,255),constrain(g-t,0,255),constrain(b-t,0,255));
      }
      if (mx==g){
        c.pixels[i]=color (constrain(r-t,0,255),constrain(g+t,0,255),constrain(b-t,0,255));
      }  
      if (mx==b){
        c.pixels[i]=color (constrain(r-t,0,255),constrain(g-t,0,255),constrain(b+t,0,255));
      }
  }
  c.updatePixels ();
  return c;
}

PImage chroma (PImage a) {
  PImage s=a.copy ();
  s.filter (GRAY);
  a.loadPixels ();
  s.loadPixels();
  float r;
  float g;
  float b;
  for (int i=0;i<a.pixels.length;i++) {
      r=red(a.pixels[i]);
      g=green(a.pixels[i]);
      b=blue(a.pixels[i]);
      float max=max (r,g,b);
      float min=min (r,g,b);
      s.pixels[i]=color (max-min);
  }
  s.updatePixels();
  return s;
}