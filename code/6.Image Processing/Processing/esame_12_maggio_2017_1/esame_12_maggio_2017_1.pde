PImage a;
float s;
void setup () {
  size (768,256);
  a=loadImage ("lena.png");
  a.resize (256,256);
  image (a,0,0);
  s=0;
}

void draw () {
  image (a,0,0);
  image (rotateF(a,s),256,0);
  image (rotatel(a,s),512,0);
}

PImage rotateF (PImage a,float theta) {
  PImage r=createImage (a.width,a.height,RGB);
  r.loadPixels();
  a.loadPixels();
  for (int i=0;i<a.width;i++) {
    for (int j=0;j<a.height;j++) {
      int vx=i-(a.width/2);
      int vy=j-(a.height/2);
      float x=vx*cos(radians(-theta))-vy*sin(radians(-theta));
      float y=vx*sin(radians(-theta))+vy*cos(radians(-theta));
      x=x+(a.width/2);
      y=y+(a.height/2);
      if (x>=0&&x<a.width&&y>=0&&y<a.height) {
         r.pixels[int(y)*r.width+int(x)]=a.pixels[j*a.width+i];
      }
    }
  }
  r.updatePixels();
  return r;
}

PImage rotatel (PImage a,float theta) {
  PImage r=createImage (a.width,a.height,RGB);
  r.loadPixels();
  a.loadPixels();
  for (int i=0;i<a.width;i++) {
    for (int j=0;j<a.height;j++) {
      int vx=i-(a.width/2);
      int vy=j-(a.height/2);
      float x=vx*cos(radians(-theta))+vy*sin(radians(-theta));
      float y=-vx*sin(radians(-theta))+vy*cos(radians(-theta));
      x=x+(a.width/2);
      y=y+(a.height/2);
      if (x>=0&&x<a.width&&y>=0&&y<a.height) {
         r.pixels[j*r.width+i]=a.pixels[int(y)*a.width+int(x)];
      }
    }
  }
  r.updatePixels();
  return r;
}

void keyPressed () {
  if (key=='+') {
    s+=5;  
  }
  if (key=='-') {
    s-=5;  
  }
}