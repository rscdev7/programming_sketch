PImage minimum(PImage IM, int N)
{
  PImage R=IM.copy();
  PImage tmp;
  float[] tmpF=new float[N*N];
  int off= N/2;
  int k=0;
  int rig=0;
  int col=0;
  float val=0.0;
  float min=0.0;
  for(int i=0; i< IM.width; i++)
  {
    for(int j=0; j< IM.height; j++)
    {
      tmp=IM.get(i-off,j-off,N,N);
      for (int t=0;t<N*N;t++) {
         tmpF[t]=-1;
      }
      k=0;
      col=i-off;
      rig=j-off;
      val=0.0;
      for (int t=0;t<tmp.width;t++) {
        for (int l=0;l<tmp.height;l++) {
          val=green(IM.get(col+t,rig+l));
          if (val==0) {
            if ((col+t)>0&&(col+t)<IM.width&&(rig+l)>0&&(rig+l)<IM.height) {
              tmpF[k]=val;
              k++;
            }
        }else{
          tmpF[k]=val;
          k++;
        }
      }
    }
    min=tmpF[0];
    for (int t=0;t<k;t++) {
     if (min>tmpF[t]) min=tmpF[t];
    }
    R.set(i,j,color(min));
    }
  }
  return R;
}