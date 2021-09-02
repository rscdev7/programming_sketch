PImage l;
int k;
String val;
String nc;
String ms;
void setup () {
  size(768,256);
  background(255);
  l=loadImage ("lena.png");
  l.resize(256,256);
  image(l,0,0);
  k=2;
  val="Valore k: ";
  ms="MSE ";
}

void draw () {
  background(255);
  image(l,0,0);
  image(rgbQuant(l,k),256,0);
  textSize(12);
  textAlign(LEFT);
  fill(0,0,0);
  text(val+k+"",550,50);
  nc="Numero Colori con "+k+" Livelli: ";
  text(nc,550,70);
  text(pow(k,3),550,90);
  float[] y=mse(l,rgbQuant(l,k));
  text(ms+" RED-RED "+y[0]+" ",550,110);
  text(ms+" GREEN-GREEN "+y[1]+" ",550,130);
  text(ms+" BLUE-BLUE "+y[2]+" ",550,150);
  text(ms+" MEDIA "+y[3]+" ",550,170);
}

PImage rgbQuant (PImage s,int n) {
  PImage w=s.copy();
  float red;  
  float green;
  float blue;
  w.loadPixels();
  for (int i=0;i<s.pixels.length;i++) {
        red=red (s.pixels[i]);
        green=green (s.pixels[i]);
        blue=blue (s.pixels[i]);
        red=floor((red*n)/256);
        green=floor((green*n)/256);
        blue=floor((blue*n)/256);
        red=floor((red/float(n-1))*255);
        green=floor((green/float(n-1))*255);
        blue=floor((blue/float(n-1))*255);
        w.pixels[i]=color(red,green,blue);
    }
    w.updatePixels();
    return w;
}

float[] mse(PImage I, PImage J)
{
  I.loadPixels();
  J.loadPixels();
  
  float[] mse={0,0,0,0};
  for(int i=0;i<I.pixels.length;i++)
  {
    mse[0]+=pow(red(I.pixels[i])-red(J.pixels[i]),2);
    mse[1]+=pow(green(I.pixels[i])-green(J.pixels[i]),2);
    mse[2]+=pow(blue(I.pixels[i])-blue(J.pixels[i]),2);
  }
  
  mse[0]=mse[0]/I.pixels.length;
  mse[1]=mse[1]/I.pixels.length;
  mse[2]=mse[2]/I.pixels.length;
  mse[3]=(mse[0]+mse[1]+mse[2])/(3.0);
 
  return mse;
}
/*float[] mse (PImage im1,PImage im2) {
  float [] d=new float [4];
  if (im1.width==im2.width&&im2.height==im1.height) {
    float sred=0.0;  
    float sgreen=0.0;
    float sblue=0.0;
    float media;
    im1.loadPixels();
    im2.loadPixels();
  for (int i=0;i<im1.pixels.length;i++) {
    sred=sred+pow(red(im1.pixels[i])-red(im2.pixels[i]),2);
    sgreen=sgreen+pow(green(im1.pixels[i])-green(im2.pixels[i]),2);
    sblue=sblue+pow(blue(im1.pixels[i])-blue(im2.pixels[i]),2);
  }
  sred=sred/im1.width*im1.height;
  sgreen=sgreen/im1.width*im1.height;
  sblue=sblue/im1.width*im1.height;
  media=sred+sgreen+sblue/3;
  d[0]=sred;
  d[1]=sgreen;
  d[2]=sblue;
  d[3]=media;
  }else{
    d[0]=-99999;
  }
  return d;
}*/
void keyPressed () {
  if (key=='+'&&k+1<257) {
    k++;
  }
  if (key=='-'&&k-1>=2) {
    k--;
  }
  if (key=='q') {
    k=2;
  }
  if (key=='w') {
    k=256;
  }
}