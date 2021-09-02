int sx=2;
int sy=2;
float x;
float y;
int attract;
void setup() {
  size (800,480);
  background (128);
  fill (0,0,255);
  noStroke();
  ellipse (300,120,30,30);
  fill (0,255,0);
  noStroke();
  ellipse (550,390,50,50);
  x=300;
  y=120;
  attract=1;
}

void draw () {
  background (127);
  float dis=dist(x,y,550,390);
  if (dis>20&&attract==1) {
    float sx=(550-x)/dist(x,y,550,390);
    float sy=(390-y)/dist(x,y,550,390);
   
    sx=attract*sx*2;
    sy=attract*sy*2;
    
    x=x+sx;
    y=y+sy;
    
  }else{
    attract=-1;

    float sx=(550-x)/dist(x,y,550,390);
    float sy=(390-y)/dist(x,y,550,390);
   
    sx=attract*sx*2;
    sy=attract*sy*2;
    
    x=x+sx;
    y=y+sy;
    
  }
  //Iron 
  fill (0,0,255);
  noStroke();
  ellipse (x,y,20,20);
  //Magnet
  fill (0,255,0);
  noStroke();
  ellipse (550,390,50,50);
  stroke(255,0,0);
  line (x,y,550,390);
}