//TNtuple("nt","nt","EVTN:PDG:PID:TID:EDEP:XPOS:YPOS:ZPOS:PAD:KE:GT");

#define PI0 111     // PDG particle codes
#define PIP 211
#define PIM -211
#define MUP -13
#define MUM 13
#define EP -11
#define EM 11

void analysis_mutlTHR(Int_t f=0)
{
	
  Float_t NofEvents = 100000.;
  Float_t threshold1 = 2.; // deposit energy MeV
  Float_t threshold2 = 3.;
  Float_t threshold3 = 4.;
  Float_t threshold4 = 5.;
	
  TString fin="../MCfiles/hit";
  if(f<10) fin+="0";
  fin+=f;
  fin+=".root";
  TFile* file = new TFile(fin,"READ");
  TNtuple* data = (TNtuple*) file->Get("nt");
  Int_t entries = data->GetEntries();
  cout<<"----------------------------------------------------"<<endl;
  cout<<fin<<endl;
	
  Float_t evtN,padN,pdgC,E,kin,t;
  const Int_t e=entries;
  data->SetBranchAddress("PDG",&pdgC);
  data->SetBranchAddress("EDEP",&E);
  data->SetBranchAddress("PAD",&padN);
  data->SetBranchAddress("KE",&kin);
  data->SetBranchAddress("GT",&t);
	
  Float_t n=0., t1=0.,t2=0.,t3=0.,t4=0.,
    p0_1=0.,p1_1=0.,p0_2=0.,p1_2=0.,
    p0_3=0.,p1_3=0.,p0_4=0.,p1_4=0.;
	
  TH1F *hEdep = new TH1F("Edep","Total Deposit Energy",200,0.,20.);
  hEdep->GetXaxis()->SetTitle("dE [MeV]");
  hEdep->GetYaxis()->SetTitle("dN/dE [MeV^{-1}]");
  TH1F *hEdepEl = new TH1F("EdepE","Deposit Energy e^{#pm}",200,0.,20.);
  hEdepEl->GetXaxis()->SetTitle("dE [MeV]");
  hEdepEl->GetYaxis()->SetTitle("dN/dE [MeV^{-1}]");
  TH1F *hEdepMu = new TH1F("EdepMU","Deposit Energy #mu^{#pm}",200,0.,20.);
  hEdepMu->GetXaxis()->SetTitle("dE [MeV]");
  hEdepMu->GetYaxis()->SetTitle("dN/dE [MeV^{-1}]");
  TH1F *hEdepPi = new TH1F("EdepPI","Deposit Energy #pi^{#pm}",200,0.,20.);
  hEdepPi->GetXaxis()->SetTitle("dE [MeV]");
  hEdepPi->GetYaxis()->SetTitle("dN/dE [MeV^{-1}]");
	
  char title[80];
	
  sprintf(title,"Hit Time: threshold = %.1f MeV",threshold1);
  TH1F *hTimeTHRS1 = new TH1F("T_THRS1",title,200,0.,20.);
  hTimeTHRS1->GetXaxis()->SetTitle("dt [ns]");
  hTimeTHRS1->GetYaxis()->SetTitle("dN/dt [ns^{-1}]");
  sprintf(title,"Hit Time: threshold = %.1f MeV",threshold2);
  TH1F *hTimeTHRS2 = new TH1F("T_THRS2",title,200,0.,20.);
  hTimeTHRS2->GetXaxis()->SetTitle("dt [ns]");
  hTimeTHRS2->GetYaxis()->SetTitle("dN/dt [ns^{-1}]");
  sprintf(title,"Hit Time: threshold = %.1f MeV",threshold3);
  TH1F *hTimeTHRS3 = new TH1F("T_THRS3",title,200,0.,20.);
  hTimeTHRS3->GetXaxis()->SetTitle("dt [ns]");
  hTimeTHRS3->GetYaxis()->SetTitle("dN/dt [ns^{-1}]");
  sprintf(title,"Hit Time: threshold = %.1f MeV",threshold4);
  TH1F *hTimeTHRS4 = new TH1F("T_THRS4",title,200,0.,20.);
  hTimeTHRS4->GetXaxis()->SetTitle("dt [ns]");
  hTimeTHRS4->GetYaxis()->SetTitle("dN/dt [ns^{-1}]");
	
  sprintf(title,"Kinetic Energy: threshold = %.1f MeV",threshold1);
  TH1F *hKinTHRS1 = new TH1F("K_THRS1",title,200,0.,810.);
  hKinTHRS1->GetXaxis()->SetTitle("K [MeV]");
  hKinTHRS1->GetYaxis()->SetTitle("dN/dK [MeV^{-1}]");
  sprintf(title,"Kinetic Energy: threshold = %.1f MeV",threshold2);
  TH1F *hKinTHRS2 = new TH1F("K_THRS2",title,200,0.,810.);
  hKinTHRS2->GetXaxis()->SetTitle("K [MeV]");
  hKinTHRS2->GetYaxis()->SetTitle("dN/dK [MeV^{-1}]");
  sprintf(title,"Kinetic Energy: threshold = %.1f MeV",threshold3);
  TH1F *hKinTHRS3 = new TH1F("K_THRS3",title,200,0.,800.);
  hKinTHRS3->GetXaxis()->SetTitle("K [MeV]");
  hKinTHRS3->GetYaxis()->SetTitle("dN/dK [MeV^{-1}]");
  sprintf(title,"Kinetic Energy: threshold = %.1f MeV",threshold4);
  TH1F *hKinTHRS4 = new TH1F("K_THRS4",title,200,20.,550.);
  hKinTHRS4->GetXaxis()->SetTitle("K [MeV]");
  hKinTHRS4->GetYaxis()->SetTitle("dN/dK [MeV^{-1}]");

  for(Int_t i=0; i<e; i++)
    {
      data->GetEntry(i);
      if(abs(pdgC) != PIP && abs(pdgC) != EM && abs(pdgC) != MUM) continue; ++n;
      if(E>=threshold1)
	{ 
	  ++t1;
	  if(padN==0.) ++p0_1;
	  else if(padN==1.) ++p1_1;
	  hKinTHRS1->Fill(kin);
	  hTimeTHRS1->Fill(t);
	}
      if(E>=threshold2)
	{ 
	  ++t2;
	  if(padN==0.) ++p0_2;
	  else if(padN==1.) ++p1_2;
	  hKinTHRS2->Fill(kin);
	  hTimeTHRS2->Fill(t);
	}
      if(E>=threshold3)
	{ 
	  ++t3;
	  if(padN==0.) ++p0_3;
	  else if(padN==1.) ++p1_3;
	  hKinTHRS3->Fill(kin);
	  hTimeTHRS3->Fill(t);
	}
      if(E>=threshold4)
	{ 
	  ++t4;
	  if(padN==0.) ++p0_4;
	  else if(padN==1.) ++p1_4;
	  hKinTHRS4->Fill(kin);
	  hTimeTHRS4->Fill(t);
	}
		
      hEdep->Fill(E);
      if(abs(pdgC) == EM) hEdepEl->Fill(E);
      if(abs(pdgC) == MUM)hEdepMu->Fill(E);
      if(abs(pdgC) == PIP) hEdepPi->Fill(E);		
    }
	
  TString fout="../data/anahit";
  if(f<10) fout+="0";
  fout+=f;
  fout+="out.root";
  TFile *histo = new TFile(fout,"RECREATE");
  hEdep->Write();
  hEdepEl->Write();
  hEdepMu->Write();
  hEdepPi->Write();
  hTimeTHRS1->Write();
  hTimeTHRS2->Write();
  hTimeTHRS3->Write();
  hTimeTHRS4->Write();
  hKinTHRS1->Write();
  hKinTHRS2->Write();
  hKinTHRS3->Write();
  hKinTHRS4->Write();
  histo->Close();
			
  cout<<"----------------------------------------------------"<<endl;
  cout<<"Number of Events: "<<NofEvents<<endl;
  cout<<"----------------------------------------------------"<<endl;
  cout<<"total number of hits: "<<e<<endl;
  cout<<"after cut on gamma: "<<n<<endl;
  cout<<"----------------------------------------------------"<<endl;
  cout<<"hits with cut in energy "<<threshold1<<" MeV: "<<t1<<endl;
  cout<<"\t on the LEFT PAD:\t"<<p0_1<<endl;
  cout<<"\t on the RIGHT PAD:\t"<<p1_1<<endl;
  cout<<"\t geometric scaling factor: "<<t1/NofEvents<<" +/- "<<sqrt(t1)/NofEvents<<endl;
  cout<<"----------------------------------------------------"<<endl;
  cout<<"hits with cut in energy "<<threshold2<<" MeV: "<<t2<<endl;
  cout<<"\t on the LEFT PAD:\t"<<p0_2<<endl;
  cout<<"\t on the RIGHT PAD:\t"<<p1_2<<endl;
  cout<<"\t geometric scaling factor: "<<t2/NofEvents<<" +/- "<<sqrt(t2)/NofEvents<<endl;
  cout<<"----------------------------------------------------"<<endl;
  cout<<"hits with cut in energy "<<threshold3<<" MeV: "<<t3<<endl;
  cout<<"\t on the LEFT PAD:\t"<<p0_3<<endl;
  cout<<"\t on the RIGHT PAD:\t"<<p1_3<<endl;
  cout<<"\t geometric scaling factor: "<<t3/NofEvents<<" +/- "<<sqrt(t3)/NofEvents<<endl;
  cout<<"----------------------------------------------------"<<endl;
  cout<<"hits with cut in energy "<<threshold4<<" MeV: "<<t4<<endl;
  cout<<"\t on the LEFT PAD:\t"<<p0_4<<endl;
  cout<<"\t on the RIGHT PAD:\t"<<p1_4<<endl;
  cout<<"\t geometric scaling factor: "<<t4/NofEvents<<" +/- "<<sqrt(t4)/NofEvents<<endl;
  cout<<"----------------------------------------------------"<<endl;
	
  if(f<10) sprintf(title,"../data/hit0%d.out",f);
  else sprintf(title,"../data/hit%d.out",f);
  ofstream outfile;
  outfile.open(title);
  outfile<<"----------------------------------------------------"<<endl;
  outfile<<"Number of Events: "<<NofEvents<<endl;
  outfile<<"----------------------------------------------------"<<endl;
  outfile<<"total number of hits: "<<e<<endl;
  outfile<<"cut on gamma: "<<n<<endl;
  outfile<<"----------------------------------------------------"<<endl;
  outfile<<"hits with cut in energy "<<threshold1<<" MeV: "<<t1<<endl;
  outfile<<"\t on the LEFT PAD:\t"<<p0_1<<endl;
  outfile<<"\t on the RIGHT PAD:\t"<<p1_1<<endl;
  outfile<<"\t geometric scaling factor: "<<t1/NofEvents<<" +/- "<<sqrt(t1)/NofEvents<<endl;
  outfile<<"----------------------------------------------------"<<endl;
  outfile<<"hits with cut in energy "<<threshold2<<" MeV: "<<t2<<endl;
  outfile<<"\t on the LEFT PAD:\t"<<p0_2<<endl;
  outfile<<"\t on the RIGHT PAD:\t"<<p1_2<<endl;
  outfile<<"\t geometric scaling factor: "<<t2/NofEvents<<" +/- "<<sqrt(t2)/NofEvents<<endl;
  outfile<<"----------------------------------------------------"<<endl;
  outfile<<"hits with cut in energy "<<threshold3<<" MeV: "<<t3<<endl;
  outfile<<"\t on the LEFT PAD:\t"<<p0_3<<endl;
  outfile<<"\t on the RIGHT PAD:\t"<<p1_3<<endl;
  outfile<<"\t geometric scaling factor: "<<t3/NofEvents<<" +/- "<<sqrt(t3)/NofEvents<<endl;
  outfile<<"----------------------------------------------------"<<endl;
  outfile<<"hits with cut in energy "<<threshold4<<" MeV: "<<t4<<endl;
  outfile<<"\t on the LEFT PAD:\t"<<p0_4<<endl;
  outfile<<"\t on the RIGHT PAD:\t"<<p1_4<<endl;
  outfile<<"\t geometric scaling factor: "<<t4/NofEvents<<" +/- "<<sqrt(t4)/NofEvents<<endl;
  outfile<<"----------------------------------------------------"<<endl;
  outfile.close();

}


void analysis(Int_t f=0)
{	
  Float_t NofEvents = 100000.;
  Float_t threshold1 = 3.; // deposit energy MeV
  
	
  TString fin="../MCfiles/hit";
  //  TString fin="../MCfiles_LocOVC/hit";
  //  TString fin="../MCfiles_LocOVCandSwan/hit";
  //  TString fin="../MCfiles_NoB/hit";
  //  TString fin="../MCfiles_Glob/hit";
  if(f<10) fin+="0";
  fin+=f;
  fin+=".root";
  TFile* file = new TFile(fin,"READ");
  TNtuple* data = (TNtuple*) file->Get("nt");
  Int_t entries = data->GetEntries();
  cout<<"@ File "<<f<<" *** events: " <<entries<<endl;
  cout<<"----------------------------------------------------"<<endl;
  cout<<fin<<endl;
	
  Float_t evtN,padN,pdgC,E,kin,t;
  const Int_t e=entries;
  data->SetBranchAddress("PDG",&pdgC);
  data->SetBranchAddress("EDEP",&E);
  data->SetBranchAddress("PAD",&padN);
  data->SetBranchAddress("KE",&kin);
  data->SetBranchAddress("GT",&t);
	
  Float_t n=0., t1=0., p0_1=0., p1_1=0.;
	
  TH1F *hEdep = new TH1F("Edep","Total Deposit Energy",200,0.,20.);
  hEdep->GetXaxis()->SetTitle("dE [MeV]");
  hEdep->GetYaxis()->SetTitle("dN/dE [MeV^{-1}]");
  TH1F *hEdepEl = new TH1F("EdepE","Deposit Energy e^{#pm}",200,0.,20.);
  hEdepEl->GetXaxis()->SetTitle("dE [MeV]");
  hEdepEl->GetYaxis()->SetTitle("dN/dE [MeV^{-1}]");
  TH1F *hEdepMu = new TH1F("EdepMU","Deposit Energy #mu^{#pm}",200,0.,20.);
  hEdepMu->GetXaxis()->SetTitle("dE [MeV]");
  hEdepMu->GetYaxis()->SetTitle("dN/dE [MeV^{-1}]");
  TH1F *hEdepPi = new TH1F("EdepPI","Deposit Energy #pi^{#pm}",200,0.,20.);
  hEdepPi->GetXaxis()->SetTitle("dE [MeV]");
  hEdepPi->GetYaxis()->SetTitle("dN/dE [MeV^{-1}]");
	
  char title[80];	
  sprintf(title,"Hit Time: threshold = %.1f MeV",threshold1);
  TH1F *hTimeTHRS1 = new TH1F("T_THRS1",title,200,0.,20.);
  hTimeTHRS1->GetXaxis()->SetTitle("dt [ns]");
  hTimeTHRS1->GetYaxis()->SetTitle("dN/dt [ns^{-1}]");

  sprintf(title,"Kinetic Energy: threshold = %.1f MeV",threshold1);
  TH1F *hKinTHRS1 = new TH1F("K_THRS1",title,200,0.,810.);
  hKinTHRS1->GetXaxis()->SetTitle("K [MeV]");
  hKinTHRS1->GetYaxis()->SetTitle("dN/dK [MeV^{-1}]");

  for(Int_t i=0; i<e; i++)
    {
      data->GetEntry(i);
      if(abs(pdgC) != PIP && abs(pdgC) != EM && abs(pdgC) != MUM) continue; ++n;

      if(E>=threshold1)
	{ 
	  ++t1;
	  if(padN==0.) ++p0_1;
	  else if(padN==1.) ++p1_1;
	  hKinTHRS1->Fill(kin);
	  hTimeTHRS1->Fill(t);

	  hEdep->Fill(E);
	  if(abs(pdgC) == EM) hEdepEl->Fill(E);
	  if(abs(pdgC) == MUM)hEdepMu->Fill(E);
	  if(abs(pdgC) == PIP) hEdepPi->Fill(E);
	}
	       		
    }
	
  TString fout="../data/anahisto";
  if(f<10) fout+="0";
  fout+=f;
  fout+="out.root";
  TFile *histo = new TFile(fout,"RECREATE");
  hEdep->Write();
  hEdepEl->Write();
  hEdepMu->Write();
  hEdepPi->Write();
  hTimeTHRS1->Write();
  hKinTHRS1->Write();
  histo->Close();
			
  cout<<"----------------------------------------------------"<<endl;
  cout<<"Number of Events: "<<NofEvents<<endl;
  cout<<"----------------------------------------------------"<<endl;
  cout<<"total number of hits: "<<e<<endl;
  cout<<"after cut on gamma: "<<n<<endl;
  cout<<"----------------------------------------------------"<<endl;
  cout<<"hits with cut in energy "<<threshold1<<" MeV: "<<t1<<endl;
  cout<<"\t on the LEFT PAD:\t"<<p0_1<<endl;
  cout<<"\t on the RIGHT PAD:\t"<<p1_1<<endl;
  cout<<"\t geometric scaling factor: "<<t1/NofEvents<<" +/- "<<sqrt(t1)/NofEvents<<endl;
  cout<<"----------------------------------------------------"<<endl;
  cout<<"----------------------------------------------------"<<endl;
	
  if(f<10) sprintf(title,"../data/anahit0%d.out",f);
  else sprintf(title,"../data/anahit%d.out",f);
  ofstream outfile;
  outfile.open(title);
  outfile<<"----------------------------------------------------"<<endl;
  outfile<<"Number of Events: "<<NofEvents<<endl;
  outfile<<"----------------------------------------------------"<<endl;
  outfile<<"total number of hits: "<<e<<endl;
  outfile<<"after cut on gamma: "<<n<<endl;
  outfile<<"----------------------------------------------------"<<endl;
  outfile<<"hits with cut in energy "<<threshold1<<" MeV: "<<t1<<endl;
  outfile<<"\t on the LEFT PAD:\t"<<p0_1<<endl;
  outfile<<"\t on the RIGHT PAD:\t"<<p1_1<<endl;
  outfile<<"\t e: "<<t1/NofEvents<<" +/- "<<sqrt(t1)/NofEvents<<endl;
  outfile<<"----------------------------------------------------"<<endl;
  outfile<<"----------------------------------------------------"<<endl;
  outfile.close();

}

/*
PMT 8 eff = 0.453344 +/- 0.0336813
		0.453956
PMT 7 eff = 1.14254 +/- 0.07212
		1.13915
PMT 6 eff = 0.580589 +/- 0.0365397
		0.58273
PMT 5 eff = 0.5987 +/- 0.034713
		0.602585
*/

double pmt5eff = 0.6;
double pmt6eff = 0.58;
double pmt7eff = 0.45;
double pmt8eff = 1.14;

void analysis_witheff(Int_t f=0)
{	
  Float_t NofEvents = 100000.;
  //  Float_t threshold1 = 3.; // deposit energy MeV
  Float_t threshold1 = 0.; // deposit energy MeV
  
  float lefteff = float(pmt5eff*pmt6eff);
  float righteff = float(pmt7eff*pmt8eff);

  TString fin="../MCfiles/hit";
  if(f<10) fin+="0";
  fin+=f;
  fin+=".root";
  TFile* file = new TFile(fin,"READ");
  TNtuple* data = (TNtuple*) file->Get("nt");
  Int_t entries = data->GetEntries();
  cout<<"@ File "<<f<<" *** events: " <<entries<<endl;
  cout<<"----------------------------------------------------"<<endl;
  cout<<fin<<endl;
	
  Float_t evtN,padN,pdgC,E,kin,t;
  const Int_t e=entries;
  data->SetBranchAddress("PDG",&pdgC);
  data->SetBranchAddress("EDEP",&E);
  data->SetBranchAddress("PAD",&padN);
  data->SetBranchAddress("KE",&kin);
  data->SetBranchAddress("GT",&t);
	
  Float_t n=0., t1=0., p0_1=0., p1_1=0.;
	
  TH1F *hEdep = new TH1F("Edep","Total Deposit Energy",200,0.,20.);
  hEdep->GetXaxis()->SetTitle("dE [MeV]");
  hEdep->GetYaxis()->SetTitle("dN/dE [MeV^{-1}]");
  TH1F *hEdepEl = new TH1F("EdepE","Deposit Energy e^{#pm}",200,0.,20.);
  hEdepEl->GetXaxis()->SetTitle("dE [MeV]");
  hEdepEl->GetYaxis()->SetTitle("dN/dE [MeV^{-1}]");
  TH1F *hEdepMu = new TH1F("EdepMU","Deposit Energy #mu^{#pm}",200,0.,20.);
  hEdepMu->GetXaxis()->SetTitle("dE [MeV]");
  hEdepMu->GetYaxis()->SetTitle("dN/dE [MeV^{-1}]");
  TH1F *hEdepPi = new TH1F("EdepPI","Deposit Energy #pi^{#pm}",200,0.,20.);
  hEdepPi->GetXaxis()->SetTitle("dE [MeV]");
  hEdepPi->GetYaxis()->SetTitle("dN/dE [MeV^{-1}]");
	
  char title[80];	
  sprintf(title,"Hit Time: threshold = %.1f MeV",threshold1);
  TH1F *hTimeTHRS1 = new TH1F("T_THRS1",title,200,0.,20.);
  hTimeTHRS1->GetXaxis()->SetTitle("dt [ns]");
  hTimeTHRS1->GetYaxis()->SetTitle("dN/dt [ns^{-1}]");

  sprintf(title,"Kinetic Energy: threshold = %.1f MeV",threshold1);
  TH1F *hKinTHRS1 = new TH1F("K_THRS1",title,200,0.,810.);
  hKinTHRS1->GetXaxis()->SetTitle("K [MeV]");
  hKinTHRS1->GetYaxis()->SetTitle("dN/dK [MeV^{-1}]");

  for(Int_t i=0; i<e; i++)
    {
      data->GetEntry(i);
      if(abs(pdgC) != PIP && abs(pdgC) != EM && abs(pdgC) != MUM) continue; 
      ++n;

      if( padN==0. && lefteff > gRandom->Uniform() )
	continue;
      
      if( padN==1. && righteff > gRandom->Uniform() )
	continue;	  

      if(E>=threshold1)
	{ 
	  ++t1;
	  if(padN==0.) ++p0_1; // left
	  else if(padN==1.) ++p1_1; // right
	  hKinTHRS1->Fill(kin);
	  hTimeTHRS1->Fill(t);

	  hEdep->Fill(E);
	  if(abs(pdgC) == EM) hEdepEl->Fill(E);
	  if(abs(pdgC) == MUM)hEdepMu->Fill(E);
	  if(abs(pdgC) == PIP) hEdepPi->Fill(E);
	}
	       		
    }
	
  TString fout="../data/anahisto";
  if(f<10) fout+="0";
  fout+=f;
  fout+="out.root";
  TFile *histo = new TFile(fout,"RECREATE");
  hEdep->Write();
  hEdepEl->Write();
  hEdepMu->Write();
  hEdepPi->Write();
  hTimeTHRS1->Write();
  hKinTHRS1->Write();
  histo->Close();
			
  cout<<"----------------------------------------------------"<<endl;
  cout<<"Number of Events: "<<NofEvents<<endl;
  cout<<"----------------------------------------------------"<<endl;
  cout<<"total number of hits: "<<e<<endl;
  cout<<"after cut on gamma: "<<n<<endl;
  cout<<"----------------------------------------------------"<<endl;
  cout<<"hits with cut in energy "<<threshold1<<" MeV: "<<t1<<endl;
  cout<<"\t on the LEFT PAD:\t"<<p0_1<<endl;
  cout<<"\t on the RIGHT PAD:\t"<<p1_1<<endl;
  cout<<"\t geometric scaling factor: "<<t1/NofEvents<<" +/- "<<sqrt(t1)/NofEvents<<endl;
  cout<<"----------------------------------------------------"<<endl;
  cout<<"----------------------------------------------------"<<endl;
	
  if(f<10) sprintf(title,"../data/anahit0%d.out",f);
  else sprintf(title,"../data/anahit%d.out",f);
  ofstream outfile;
  outfile.open(title);
  outfile<<"----------------------------------------------------"<<endl;
  outfile<<"Number of Events: "<<NofEvents<<endl;
  outfile<<"----------------------------------------------------"<<endl;
  outfile<<"total number of hits: "<<e<<endl;
  outfile<<"after cut on gamma: "<<n<<endl;
  outfile<<"----------------------------------------------------"<<endl;
  outfile<<"hits with cut in energy "<<threshold1<<" MeV: "<<t1<<endl;
  outfile<<"\t on the LEFT PAD:\t"<<p0_1<<endl;
  outfile<<"\t on the RIGHT PAD:\t"<<p1_1<<endl;
  outfile<<"\t e: "<<t1/NofEvents<<" +/- "<<sqrt(t1)/NofEvents<<endl;
  outfile<<"----------------------------------------------------"<<endl;
  outfile<<"----------------------------------------------------"<<endl;
  outfile.close();

}


void run_analysis(Int_t Nfile=13)
{
  for(Int_t i=0; i<Nfile; ++i)
    {
      //      analysis_mutlTHR(i);
      //  analysis(i);
      analysis_witheff(i);
    }
  gROOT->ProcessLine(".q");
	
}
