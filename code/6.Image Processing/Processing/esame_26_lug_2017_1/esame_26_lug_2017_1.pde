PImage l;
int s;
void setup () {
  size(768,300);
  background(0);
  l=loadImage ("lena.png");
  l.resize(256,256);
  l.filter(GRAY);
  s=11;
  image(l,0,0);
  image (convolutionNBox(l,s),256,0);
}

void draw () {
  background(0);
  image(l,0,0);
  image (convolutionNBox(l,s),256,0);
  image(absDiff(l,convolutionNBox(l,s)),511,0);
  textSize(20);
  textAlign (LEFT);
  fill(255,255,255);
  text("Original",2,290);
  text("Nbox: "+s+" ",270,290);
  text("Difference: ",540,290);
}

PImage convolutionNBox (PImage im,int s) {
  float [][] nbox=new float [s][s];
  float [][] R=new float [im.height][im.width];
  PImage z=createImage (R[0].length,R.length,RGB);
  PImage crop;
  float val=0.0;
  for (int i=0;i<s;i++) {
    for (int j=0;j<s;j++) {
      nbox[i][j]=1.0/(s*s);  
    }
  }
  for (int i=0;i<im.width;i++) {
    for (int j=0;j<im.height;j++) {
      crop=im.get(i-s/2,j-s/2,s,s);
      val=0.0;
      for (int w=0;w<s;w++) {
        for (int y=0;y<s;y++) {
           val=val+green(crop.get(w,y))*nbox[y][w];
        }
      }
      R[j][i]=val;
    }
  }
  for (int i=0;i<z.width;i++) {
    for (int j=0;j<z.height;j++) {
      z.set(i,j,color(constrain(abs(R[j][i]),0,255)));  
    }
  }
  return z;
}

PImage absDiff(PImage I,PImage J) {
  PImage H=createImage (I.width,I.height,RGB);
  I.loadPixels();
  J.loadPixels();
  H.loadPixels();
  for (int i=0;i<I.pixels.length;i++) {   
    H.pixels[i]=color(abs(red(I.pixels[i])-red(J.pixels[i])));
  }
  H.updatePixels();
  return H;
}

void keyPressed () {
  if (key=='+'&&s+1<=21) {
    s+=2;  
  }
  if (key=='-'&&s-1>=1) {
    s-=2;  
  }
}