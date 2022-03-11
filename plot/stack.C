void minmass_mass(){
  
  gStyle->SetOptStat(0);
  gStyle->SetTitleAlign(33);
  gStyle->SetTitleX(.99);
  
  THStack *hs_jet_pt = new THStack("hs_jet_pt","hs_jet_pt");

  TFile* VBS_data = new TFile("../signal/output/2leading/VBS.root");
  TFile* lep_data = new TFile("../bkg/output/2leading/lep.root");
  TFile* ttbar_data = new TFile("../ttbar_nonallhad_bkg/output/2leading/ttbar.root");
  
  TH1D *h1_VBS = (TH1D*)VBS_data->Get("h1_mWboson_2leading");
  TH1D *h1_lep = (TH1D*)lep_data->Get("h1_mWboson_2leading");
  TH1D *h1_ttbar = (TH1D*)ttbar_data->Get("h1_mWboson_2leading");
  
  h1_VBS->Scale(139000000);
  h1_lep->Scale(139000000);
  h1_ttbar->Scale(139000000);
  h1_VBS->Scale(100);
  hs_jet_pt->Add(h1_ttbar);
  hs_jet_pt->Add(h1_lep);
  hs_jet_pt->Add(h1_VBS);
 
  TCanvas* c1 = new TCanvas("c1","c1",50,50,640,490);
  c1->SetTickx(1);
  c1->SetTicky(1);
  c1->SetLeftMargin(0.13);
  c1->SetLogy();
  hs_jet_pt->Draw("hist");
  hs_jet_pt->GetXaxis()->SetRangeUser(1, 4000);
  hs_jet_pt->GetXaxis()->SetTitle("m^{tag}_{jj}");
  hs_jet_pt->GetYaxis()->SetTitle("Event/20GeV");*


  TCanvas *c1 = new TCanvas("c1", "the canvas",50,50,600,600);
  gStyle->SetOptStat(0);
  c1->SetTopMargin(0.13);
  c1->SetTickx(1);
  c1->SetTicky(1);
  
  hs_jet_pt->Draw("hist");
  hs_jet_pt->GetXaxis()->SetRangeUser(1, 500);
  hs_jet_pt->GetXaxis()->SetTitle(0);
  hs_jet_pt->GetXaxis()->SetLabelSize(0);
  hs_jet_pt->GetYaxis()->SetLabelSize(0.035);
  hs_jet_pt->GetYaxis()->SetTitleSize(0.04);
  hs_jet_pt->GetYaxis()->SetTitleSize(0.04);
  hs_jet_pt->GetYaxis()->SetTitle("Event/15GeV");
  hs_jet_pt->GetXaxis()->SetTitle(0);
  hs_jet_pt->SetTitle(0);
}
