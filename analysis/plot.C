#define N 13

double DegPosZ = -32.5;//cm

void plot()
{ 
  double x[N],z[N], eff[N], err[N];
  int i=0;
  ifstream fpos("../data/pos.dat");
  while(1)
    {
      fpos>>x[i]>>z[i];
      if(!fpos.good()) break;
      ++i;
    }
  fpos.close();
  
  i=0;
  ifstream feff("../data/eff.dat");
  while(1)
    {
      feff>>eff[i]>>err[i];
      if(!feff.good()) break;
      ++i;
    }
  feff.close();

  for(int i=0; i<N; ++i)
    {
      cout<<i<<"\t"<<x[i]<<"\t"<<z[i]<<"\t"<<eff[i]<<"\t"<<err[i]<<endl;
    }

  int pnts=7;
  TGraphErrors* gX = new TGraphErrors(pnts);
  cout<<"----- X scan -----"<<endl;
  for(int i=0; i<pnts; ++i)
    {
      //      gX->SetPoint(i,x[i],eff[i]);
      gX->SetPoint(i,abs(x[i]),eff[i]);
      gX->SetPointError(i,0,err[i]);
      //      cout<<i<<"\t"<<x[i]<<"\t"<<eff[i]<<"\t"<<err[i]<<endl;
      cout<<i<<"\t"<<abs(x[i])<<"\t"<<eff[i]<<"\t"<<err[i]<<endl;
    }
  cout<<"------------------"<<endl;
  // gX->SetPoint(5,x[10],eff[10]);
  // gX->SetPointError(5,0,err[10]);
  gX->SetTitle("CT_PMT_OR Efficiency - Moving Pair @ ASACUSA side - Distance from Degrader = 57.5 cm;Distance from Beam Pipe [cm];#epsilon");
  gX->SetMarkerStyle(8);
  gX->SetMarkerColor(kBlack);
  gX->SetLineColor(kBlack);
  
  TGraphErrors* gZ = new TGraphErrors(pnts);
  cout<<"----- Z scan -----"<<endl;
  //  gZ->SetPoint(0,z[0],eff[0]);
  gZ->SetPoint(0,z[0]-DegPosZ,eff[0]);
  gZ->SetPointError(0,0,err[0]);
  //  cout<<"0\t"<<z[0]<<"\t"<<eff[0]<<"\t"<<err[0]<<endl;
  cout<<"0\t"<<z[0]-DegPosZ<<"\t"<<eff[0]<<"\t"<<err[0]<<endl;
  for(int i=pnts; i<N; ++i)
    {
      //      gZ->SetPoint(i-pnts+1,z[i],eff[i]);
      gZ->SetPoint(i-pnts+1,z[i]-DegPosZ,eff[i]);
      gZ->SetPointError(i-pnts+1,0,err[i]);
      //     cout<<i-pnts+1<<"\t"<<z[i]<<"\t"<<eff[i]<<"\t"<<err[i]<<endl;
      cout<<i-pnts+1<<"\t"<<z[i]-DegPosZ<<"\t"<<eff[i]<<"\t"<<err[i]<<endl;
    }
  cout<<"------------------"<<endl;
  gZ->SetTitle("CT_PMT_OR Efficiency - Moving Pair @ ASACUSA side - Distance from Beam Pipe = 100 cm;Distance from Degrader [cm];#epsilon");
  gZ->SetMarkerStyle(8);
  gZ->SetMarkerColor(kBlack);
  gZ->SetLineColor(kBlack);

  TCanvas* cSci = new TCanvas("cSci","cSci",1200,1800);
  cSci->Divide(1,2);
  cSci->cd(1);
  gX->Draw("AP");
  gPad->SetGridy();
  cSci->cd(2);
  gZ->Draw("AP");
  gPad->SetGridy();
}
