PImage l;
int S;
void setup() {
  size(512,512);
  l=loadImage ("lena.png");
  l.resize(256,256);
  l.filter(GRAY);
  S=3;
  background(128);
  image (l,0,0);
  image(bw(l,S),256,0);
}

void draw () {
  background(128);
  image (l,0,0);
  image(bw(l,128),256,0);
  image(dilate(bw(l,128),S),0,256);
  image(erode(bw(l,128),S),256,256);
  textSize(20);
  textAlign(LEFT);
  fill(255,0,255);
  text("Valore S: "+S+" ",0,20);
}

PImage bw (PImage in,int k) {
  PImage w=in.copy();
  w.loadPixels();
  float g=0.0;
  for (int i=0;i<w.pixels.length;i++) {
    g=green(w.pixels[i]);
    if (g<=k) {
      w.pixels[i]=color(0,0,0);  
    }else{
      w.pixels[i]=color(255,255,255);  
    }
  }
  w.updatePixels();
  return w;
}

/*PImage dilate(PImage I, int n)
{
  int off=n/2;
  PImage R=I.copy();
  PImage tmp;
  int size;
  boolean flag;
  
  for(int i=0; i <I.width;i++)
  {
    for(int j=0;j<I.height;j++)
    {
      
      //Seleziono sottoimmagine NxN gestendo il caso limite
      tmp=I.get( max(i-off,0) , max(j-off,0) , min(n,I.width-i) , min(n,I.height-j) );
      tmp.loadPixels();
      size=tmp.pixels.length;
      
      flag=false;
      for(int k=0;k<size;k++)
      {
        flag=flag || (tmp.pixels[k]==color(255));
      }
      
      R.set(i,j,flag?color(255):color(0));
      
    }
  }
  return R;
}*/

PImage dilate (PImage w,int n) {
  PImage R=w.copy();
  PImage crop;
  int off=n/2;
  int size;
  boolean flag;
  for (int i=0;i<R.width;i++) {
    for (int j=0;j<R.height;j++) {
      crop=w.get(max(i-off,0),max(j-off,0),min(n,w.width-i),min(n,w.height-j));  
      crop.loadPixels();
      size=crop.pixels.length;
      flag=false;
      for (int h=0;h<size&&flag==false;h++) {
        //flag=flag || (crop.pixels[h]==color(255));
        if (crop.pixels[h]==color(255,255,255)) flag=true;
      }
      if (flag==true) R.set(i,j,color(255,255,255));
      if (flag==false) R.set(i,j,color(0,0,0));
    }
  }
  return R;
}

PImage erode(PImage I, int n)
{
  int off=n/2;
  PImage R=I.copy();
  PImage tmp;
  int size;
  boolean flag;
  
  for(int i=0; i <I.width;i++)
  {
    for(int j=0;j<I.height;j++)
    {
      
      //Seleziono sottoimmagine NxN gestendo il caso limite
      tmp=I.get( max(i-off,0) , max(j-off,0) , min(n,I.width-i) , min(n,I.height-j) );
      tmp.loadPixels();
      size=tmp.pixels.length;
      
      flag=true;
      for(int k=0;k<size;k++)
      {
        flag=flag && (tmp.pixels[k]==color(255));
      }
      
      R.set(i,j,flag?color(255):color(0));
      
      
    }
  }
  return R;
}
void keyPressed () {
  if (key=='+'&&S+1<=21) {
    S++;  
  }
  if (key=='-'&&S-1>=3) {
    S--;  
  }
}