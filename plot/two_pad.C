void minmass_mass(){
  
  gStyle->SetOptStat(0);
  gStyle->SetTitleAlign(33);
  gStyle->SetTitleX(.99);
  
  THStack *hs_jet_pt = new THStack("hs_jet_pt","hs_jet_pt");
  //hs_jet_pt->SetMaximum(1700000);

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

  TCanvas *c1 = new TCanvas("c1", "the canvas",50,50,600,600);
  gStyle->SetOptStat(0);
  c1->SetTopMargin(0.13);
  c1->SetTickx(1);
  c1->SetTicky(1);

  TPad* pad1 = new TPad("pad1","The pad with the function", 0.05,0.30,0.95,0.95,0);
  pad1->SetTopMargin(0.01);
  pad1->SetBottomMargin(0.02);
  pad1->SetLeftMargin(0.14); //make yasis left
  pad1->SetTickx(1);
  pad1->SetTicky(1);
  TPad* pad2 = new TPad("pad2","The pad with the histogram", 0.05,0.03,0.95,0.30,0);
  pad2->SetBottomMargin(0.15);
  pad2->SetTopMargin(0.02);
  pad2->SetLeftMargin(0.14); //make yasis left
  pad2->SetBottomMargin(0.2);
  pad2->SetTickx(1);
  pad2->SetTicky(1);
  pad1->Draw();
  pad2->Draw();
  pad1->cd();
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

  TLegend* leg = new TLegend(0.50,0.50,0.70,0.70);
  leg->SetTextSize(0.035);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);
  leg->AddEntry(h1_VBS, "VBS Sample x 100");
  leg->AddEntry(h1_lep, "W+jet Sample");
  leg->AddEntry(h1_ttbar, "t#bar{t} Sample");
  leg->AddEntry((TObject*)0,"minmass","");
  leg->Draw("same");

  TLatex latex_a;
  latex_a.SetTextSize(0.038);
  latex_a.SetTextAlign(13);  //align at top
  latex_a.DrawLatex(225, 395000,"#it{ATLAS} #bf{Simulation Work in progress}");
  latex_a.SetTextSize(0.03);
  latex_a.DrawLatex(225, 380000,"#bf{#sqrt{s} = 13 TeV}, 139 fb^{-1}");

  pad2->cd();
  TH1D* h1_significance;
  h1_significance->GetXaxis()->SetRangeUser(1, 500);
  h1_significance->GetYaxis()->SetLabelSize(0.08);
  h1_significance->GetYaxis()->SetTitleSize(0.08);
  h1_significance->GetXaxis()->SetLabelSize(0.08);
  h1_significance->GetXaxis()->SetTitleSize(0.08);
  h1_significance->Draw("hist");

}
