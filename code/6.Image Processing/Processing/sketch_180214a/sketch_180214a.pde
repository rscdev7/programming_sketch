PImage d;
PImage q;
int s;
color c;
boolean [][] matr;
int p;
int z;
void setup() {
   d=loadImage ("lena.png");
   d.resize(256,256);
   size(512,256);
   s=15;
   c=color(255,0,0);
   matr=new boolean [256][256];
   for (int i=0;i<256;i++) {
     for (int j=0;j<256;j++) {
       matr[i][j]=false;  
     }
   }
   background(0);
   image (d,0,0);
}

void draw() {
  image (d,0,0);
    if (mousePressed&&mouseButton==LEFT) {
      if (mouseX<256&&mouseX>=0&&mouseY>=0&&mouseY<256) {
        
        matr[mouseY][mouseX]=true;
        strokeWeight(3);
        stroke(c);
        ellipse (256+mouseX,mouseY,2,2);
      }
    }else{
      image (applyTrack(d,matr,s,c),0,0);
      for (int i=0;i<256;i++) {
        for (int j=0;j<256;j++) {
         matr[i][j]=false;  
       }
     }
    }
}

PImage applyTrack (PImage I,boolean [][] m,int n,color c) {
  PImage crop;
  for (int i=0;i<I.width;i++) {
    for (int j=0;j<I.height;j++) {
      if (m[j][i]==true) {
        crop=I.get(max(i-n/2,0),max(j-n/2,0),min(n,I.width-i),min(n,I.height-j)); 
        crop.loadPixels();
        for (int h=0;h<crop.pixels.length;h++) {
          crop.pixels[h]=c;    
        }
        I.set(max(i-n/2,0),max(j-n/2,0),crop);
      }
    }
  }
  return I;  
}
  
void keyPressed () {
  if (key=='+'||s+1<=21) {
    s++;    
  }
  if (key=='-'||s-1>=11) {
    s--;    
  }
  if (key=='R'||key=='r') {
     c=color(255,0,0);
  }
  if (key=='G'||key=='g') {
     c=color(0,255,0);
  }
  if (key=='B'||key=='b') {
     c=color(0,0,255);
  }
  if (key=='S'||key=='s') {
    d.save("done.png");
  }
  if (key=='C'||key=='c') {
     setup();
  }
}