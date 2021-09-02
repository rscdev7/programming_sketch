ArrayList<Wastepaper> a;
boolean agg;
float p=0.02;
int index;
Basket b;
void setup() {
  size(512,512);
  background(103,185,175);
  a=new ArrayList<Wastepaper>();
  agg=false;
  index=0;
  b=new Basket (210,430,0);
}

void draw() {
   background(103,185,175);
   if (random(0,1)<p) {
     a.add(new Wastepaper(random(12,500),-20,random(2,7),random(20,50)));
   }
   if (a.size()>0) {
     for (int i=0;i<a.size();i++) {
       if(agg==false&&a.get(i).check(pmouseX,pmouseY)==true&&mousePressed) {           
           a.get(i).ch();
           agg=true;
           a.get(i).move(pmouseX,pmouseY);
           a.get(i).display();
           index=i;
       }
       if (a.get(i).getM()==false) {
           a.get(i).mov();
           a.get(i).display();
       }else{
         a.get(i).move(pmouseX,pmouseY);
         a.get(i).display();
       }
     }
   }
   b.display();
   for (int i=0;i<a.size();i++) {
     if (a.get(i).getM()==false&&b.check(a.get(i))) {
       a.remove(i);      
     }
   }
   textSize(50);
   fill(255,255,0);
   text(b.getC(),2,50);
}

void mouseReleased () {
  if (agg==true) {
    agg=false;
    a.get(index).ch();
  }
}