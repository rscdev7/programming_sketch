PImage s;
PImage d;
void setup () {
  s=loadImage ("lena.png");
  d=s.get(0-1,0-1,3,3);
  for (int i=0;i<d.height;i++) {
    for (int j=0;j<d.width;j++) {
        print (red(d.get(j,i))+" ");
    }
    println ("");
  }
  println ("jhjj");
  float [] v=new float [9];
  for (int i=0;i<9;i++) {
     v[i]=-1;
  }
  int k=0;
  int col=0-1;
  int rig=0-1;
  float val=0.0;
  for (int i=0;i<d.width;i++) {
    for (int j=0;j<d.height;j++) {
        val=red(s.get(col+i,rig+j));
        //println (val+" ");
        if (val==0) {
          if ((col+i)>0&&(col+i)<s.width&&(rig+j)>0&&(rig+j)>s.height) {
            v[k]=val;
            k++;
          }
      }else{
        v[k]=val;
        k++;
      }
    }
  }
  float min=v[0];
  for (int i=0;i<k;i++) {
     if (min>v[i]) min=v[i];
  }
  println ("MInimo "+min);
}

void draw () {
}