#include "TMVA/Reader.h"
#include <iostream>
#include "TTree.h"

void test(){

  TMVA::Reader* reader = new TMVA::Reader( "!Color:!Silent" );

  float mtagjj;
  float detatagjj;
  float pttagj1;
  float pttagj2;
  float detajj;
  float ptj1;
  float ptj2;
  float widthj1;
  float widthj2;
  float ntrackj1;
  float ntrackj2;
  float widthtagj1;
  float widthtagj2;
  float ntracktagj1;
  float ntracktagj2;
  float num_trkj;
  float num_extraj;
  float met;
  float etal;
  float deltaRlnu;
  float centrality;
  float mVV;
  float mVVjj;
  float evtNum;

  reader->AddVariable("mtagjj", &mtagjj);
  reader->AddVariable("detatagjj", &detatagjj);
  reader->AddVariable("pttagj1", &pttagj1);
  reader->AddVariable("pttagj2", &pttagj2);
  reader->AddVariable("detajj", &detajj);
  reader->AddVariable("ptj1", &ptj1);
  reader->AddVariable("ptj2",  &ptj2);
  reader->AddVariable("widthj1", &widthj1);
  reader->AddVariable("widthj2", &widthj2);
  reader->AddVariable("ntrackj1", &ntrackj1);
  reader->AddVariable("ntrackj2", &ntrackj2);
  reader->AddVariable("widthtagj1", &widthtagj1);
  reader->AddVariable("widthtagj2", &widthtagj2);
  reader->AddVariable("ntracktagj1", &ntracktagj1);
  reader->AddVariable("ntracktagj2", &ntracktagj2);
  reader->AddVariable("num_trkj", &num_trkj);
  reader->AddVariable("num_extraj", &num_extraj);
  reader->AddVariable("met", &met);
  reader->AddVariable("etal", &etal);
  reader->AddVariable("deltaRlnu", &deltaRlnu);
  reader->AddVariable("centrality", &centrality);
  reader->AddVariable("mVV", &mVV);
  reader->AddVariable("mVVjj", &mVVjj);
  
  reader->AddSpectator("evtNum", &evtNum);

  // --- Book the MVA methods
  TString dir    = "Dataset/weights/";
  TString prefix = "TMVACrossValidation";
  
  // Book method(s)
  TString methodName("BDTG");
  TString weightfile = dir + prefix + TString("_BDT.weights.xml");
  reader->BookMVA(methodName, weightfile);

  TString VBS_string = "/home/chengyu/paper/VBS/signal/output/VBS.root";
  TString ttbar_string = "/home/chengyu/paper/VBS/ttbar_nonallhad_bkg/output/ttbar.root";
  TString lep_string = "/home/chengyu/paper/VBS/bkg/output/lep.root";
  TFile* input_data = new TFile(lep_string);
  TTree* theTree = (TTree*)input_data->Get("BDTinput_2leading");
  
  float m_mtagjj;
  float m_detatagjj;
  float m_pttagj1;
  float m_pttagj2;
  float m_detajj;
  float m_ptj1;
  float m_ptj2;
  float m_widthj1;
  float m_widthj2;
  float m_ntrackj1;
  float m_ntrackj2;
  float m_widthtagj1;
  float m_widthtagj2;
  float m_ntracktagj1;
  float m_ntracktagj2;
  float m_num_trkj;
  float m_num_extraj;
  float m_met;
  float m_etal;
  float m_deltaRlnu;
  float m_centrality;
  float m_mVV;
  float m_mVVjj;
  float m_evtNum;
  float m_weight;

  theTree->SetBranchAddress("weight", &m_weight);
  theTree->SetBranchAddress("mtagjj", &m_mtagjj);
  theTree->SetBranchAddress("detatagjj", &m_detatagjj);
  theTree->SetBranchAddress("pttagj1", &m_pttagj1);
  theTree->SetBranchAddress("pttagj2", &m_pttagj2);
  theTree->SetBranchAddress("detajj", &m_detajj);
  theTree->SetBranchAddress("ptj1", &m_ptj1);
  theTree->SetBranchAddress("ptj2",  &m_ptj2);
  theTree->SetBranchAddress("widthj1", &m_widthj1);
  theTree->SetBranchAddress("widthj2", &m_widthj2);
  theTree->SetBranchAddress("ntrackj1", &m_ntrackj1);
  theTree->SetBranchAddress("ntrackj2", &m_ntrackj2);
  theTree->SetBranchAddress("widthtagj1", &m_widthtagj1);
  theTree->SetBranchAddress("widthtagj2", &m_widthtagj2);
  theTree->SetBranchAddress("ntracktagj1", &m_ntracktagj1);
  theTree->SetBranchAddress("ntracktagj2", &m_ntracktagj2);
  theTree->SetBranchAddress("num_trkj", &m_num_trkj);
  theTree->SetBranchAddress("num_extraj", &m_num_extraj);
  theTree->SetBranchAddress("met", &m_met);
  theTree->SetBranchAddress("etal", &m_etal);
  theTree->SetBranchAddress("deltaRlnu", &m_deltaRlnu);
  theTree->SetBranchAddress("centrality", &m_centrality);
  theTree->SetBranchAddress("mVV", &m_mVV);
  theTree->SetBranchAddress("mVVjj", &m_mVVjj);

  theTree->SetBranchAddress("evtNum", &m_evtNum);

  float BDToutput = 0;
  float weight_save = 0;
  TFile* output_data = new TFile("output/lep.root", "RECREATE");
  TTree* BDToutput_tree = new TTree("BDToutput", "BDT output");
  BDToutput_tree->Branch("BDToutput", &BDToutput, "BDToutput/F");
  BDToutput_tree->Branch("weight", &weight_save, "weight/F");

  for (Long64_t ievt=0; ievt<theTree->GetEntries();ievt++){
     if (ievt%1000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;
     theTree->GetEntry(ievt);

     weight_save = m_weight;

     mtagjj = m_mtagjj;
     detatagjj = m_detatagjj;
     pttagj1 = m_pttagj1;
     pttagj2 = m_pttagj2;
     detajj = m_detajj;
     ptj1 = m_ptj1;
     ptj2 = m_ptj2;
     widthj1 = m_widthj1;
     widthj2 = m_widthj2;
     ntrackj1 = m_ntrackj1;
     ntrackj2 = m_ntrackj2;
     widthtagj1 = m_widthtagj1;
     widthtagj2 = m_widthtagj2;
     ntracktagj1 = m_ntracktagj1;
     ntracktagj2 = m_ntracktagj2;
     num_trkj = m_num_trkj;
     num_extraj = m_num_extraj;
     met = m_met;
     etal = m_etal;
     deltaRlnu = m_deltaRlnu;
     centrality = m_centrality;
     mVV = m_mVV;
     mVVjj = m_mVVjj;
     evtNum = m_evtNum;

     BDToutput = reader->EvaluateMVA("BDTG");

     BDToutput_tree->Fill();
     
  }

  BDToutput_tree->Write();

}
