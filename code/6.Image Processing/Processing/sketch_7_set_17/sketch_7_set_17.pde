int t;
PImage q;
void setup () {
  size (768,256);
  t=128;
  q=loadImage ("lena.png");
  q.filter(GRAY);
  q.resize(256,256);
  
}

void draw () {
  PImage [] n=split(q,t);
  image (q,0,0);
  image(n[0],257,0);
  image (n[1],514,0);
  textSize(15);
  fill(255,0,0);
  text("Val: "+t+" ",0,15);
}

void keyPressed () {
  if (key=='+'&&t<255) {
    t++;
  }
  if (key=='-'&&t>1) {
    t--;
  }
  println ("Val "+t+" ");
}

void mousePressed () {
   if (mouseX>=2&&mouseX<=253&&mouseY>=2&&mouseY<=253) {
       t=int(green(q.get(mouseX,mouseY)));
   }
}

PImage [] split (PImage f,int t) {
  PImage r=f.copy();
  PImage d=f.copy();
  r.loadPixels();
  d.loadPixels();
  f.loadPixels();
  for (int i=0;i<f.pixels.length;i++) {
     if (green(f.pixels[i])<t) {
         d.pixels[i]=color(0);
     }else{
         r.pixels[i]=color(0);
     }
  }
  PImage [] w;
  w=new PImage [2];
  w[0]=r;
  w[1]=d;
  return w;
}